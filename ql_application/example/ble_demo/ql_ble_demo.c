/*================================================================
  Copyright (c) 2024, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
/**************************************************************************************************
* include
**************************************************************************************************/
#include "string.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdbool.h>
#include "ql_ble.h"
#include "ql_osi.h"
#include "uart.h"
#include "app_task.h"
/**************************************************************************************************
* param
**************************************************************************************************/
#define CFG_ENABLE_QUECTEL_BLE_PERIPHERA  1
#define CFG_ENABLE_QUECTEL_BLE_CENTRAL    0
#define QL_BLE_DEMO_QUEUE_MAX_NB         10
#define QL_DEMO_ATT_DECL_PRIMARY_SERVICE_128     {0x00,0x28,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define QL_DEMO_ATT_DECL_CHARACTERISTIC_128      {0x03,0x28,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define QL_DEMO_ATT_DESC_CLIENT_CHAR_CFG_128     {0x02,0x29,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define QL_BLE_TEST_CHARACTERISTIC_128           {0x15,0xFF,0,0,0x34,0x56,0,0,0,0,0x28,0x37,0,0,0,0}

enum
{
	QL_BLE_DEMO_IDX_SVC,
	QL_BLE_DEMO_IDX_TEST_VAL_CHAR,
	QL_BLE_DEMO_IDX_TEST_VAL_VALUE,
	QL_BLE_DEMO_IDX_TEST_VAL_NTF_CFG,
	QL_BLE_DEMO_IDX_NB,
};

ql_ble_attm_desc_t ql_ble_demo_profile_db[QL_BLE_DEMO_IDX_NB] =
{
	//  Service Declaration
	[QL_BLE_DEMO_IDX_SVC]              = {QL_DEMO_ATT_DECL_PRIMARY_SERVICE_128, QL_BLE_PROP(RD), 0},

    [QL_BLE_DEMO_IDX_TEST_VAL_CHAR]    = {QL_DEMO_ATT_DECL_CHARACTERISTIC_128 , QL_BLE_PROP(RD), 0},
	[QL_BLE_DEMO_IDX_TEST_VAL_VALUE]   = {QL_BLE_TEST_CHARACTERISTIC_128      , QL_BLE_PROP(WR)|QL_BLE_PROP(N)|ATT_UUID(128), 512|QL_BLE_OPT(NO_OFFSET)},
	[QL_BLE_DEMO_IDX_TEST_VAL_NTF_CFG] = {QL_DEMO_ATT_DESC_CLIENT_CHAR_CFG_128, QL_BLE_PROP(RD)|QL_BLE_PROP(WR), QL_BLE_OPT(NO_OFFSET)},
};

typedef enum
{
	QL_BLE_DEMO_SET_ADV_DATA,
	QL_BLE_DEMO_SET_RSP_DATA,
	QL_BLE_DEMO_START_ADV,
    QL_BLE_DEMO_START_SCAN,
    QL_BLE_DEMO_STOP_SCAN,    
    QL_BLE_DEMO_CONN_PEER_DEVICE,
    QL_BLE_DEMO_CEN_GATT_DISV_ALL_SRV,
    QL_BLE_DEMO_CENTRAL_EXCHANGE_MTU,
    QL_BLE_DEMO_PER_GATT_SEND_NTF,
    QL_BLE_DEMO_CEN_GATT_NTFCFG,
    QL_BLE_DEMO_CEN_GATT_WRCMD,
    QL_BLE_DEMO_CEN_GATT_WRREQ,
} ql_ble_demo_msg_id;

typedef struct
{
    uint32_t msg_id;
    
    union
    {
        struct
        {       
            uint8_t con_idx;
            uint8_t svc_id;
            uint8_t att_idx; 
            uint8_t *data;
            uint16_t len;
        }send_ntf;
    }msg_param;
}ql_ble_demo_msg;

typedef struct 
{
    uint8_t  length;     
    uint8_t  adType;    
    uint8_t *aData;      
} gapAdStructure_t;

uint16_t conn_hdl = 0;
uint16_t cen_chara_hdl = 0;
ql_ble_adv_mac_addr_t peer_addr = {0};
static ql_task_t  ql_ble_demo_task = NULL;
static ql_queue_t ql_ble_demo_q    = NULL;
static ql_sem_t   ql_ble_demo_sem  = NULL;
/**************************************************************************************************
* Function
**************************************************************************************************/
/**************************************************************************************************
* Description:
*	send message.
* 
* Parameters:
*	ble_msg
*	
* Return:
*	none
*	
**************************************************************************************************/
void ql_ble_demo_msg_send(ql_ble_demo_msg *ble_msg)
{
    if(ql_rtos_queue_release(ql_ble_demo_q, sizeof(ql_ble_demo_msg), (uint8_t *)ble_msg, QL_NO_WAIT) != 0)
    {
        os_printf("BLE: %s, error \r\n", __func__);
    }
}

/**************************************************************************************************
* Description:
*	Process reported broadcast data.
* 
* Parameters:
*	p_adv_report
*	
* Return:
*	none
*	
**************************************************************************************************/
void ql_ble_demo_report_adv_deal(ql_ble_recv_adv_t *p_adv_report)
{    
    uint8_t index = 0;
  
    while(index < p_adv_report->data_len)
    {
        gapAdStructure_t adElement;
       
        adElement.length = p_adv_report->data[index];
        adElement.adType = p_adv_report->data[index + 1];
        adElement.aData = (uint8_t *)&p_adv_report->data[index + 2];

        if((adElement.adType = 0x08) || (adElement.adType = 0x09))
        {
            if(!memcmp(adElement.aData , "phone_server" , strlen("phone_server")))  //check adv name
            {            
                os_printf("Found Device NAME, RSSI:%ddBm, mac:", p_adv_report->rssi);
                
                for(uint8_t i = 0; i < 6; i++)
                {
                    os_printf("%02X ", p_adv_report->adv_addr[i]);
                }
                os_printf("\r\n");

                memcpy(&peer_addr.addr[0], p_adv_report->adv_addr, 6);
                peer_addr.addr_type = p_adv_report->adv_addr_type;

                ql_ble_demo_msg ble_demo_msg = {0};
                    
                ble_demo_msg.msg_id = QL_BLE_DEMO_STOP_SCAN;
                ql_ble_demo_msg_send(&ble_demo_msg);
                
                return;
            }
        }
        
        /* Move on to the next AD elemnt type */
        index += adElement.length + sizeof(uint8_t);
    }  
}

/**************************************************************************************************
* Description:
*	ble demo notice cb.
* 
* Parameters:
*	ble_msg
*	
* Return:
*	none
*	
**************************************************************************************************/
static void ql_ble_demo_gap_cb(ql_ble_notify_e notice, void *param)
{
    os_printf("%s, notice: [%d] \r\n", __func__, notice);

    switch (notice)
    {
        case QL_BLE_STACK_OK:
        {
            os_printf("QL_BLE_STACK_OK \r\n");
            break;
        }
        
        case QL_BLE_REPORT_ADV_EVENT:
        {
            ql_ble_recv_adv_t *recv_adv = (ql_ble_recv_adv_t *)param;
            
            os_printf("adv_type: [%d], adv_addr_type: [%d], adv_addr:[%02x:%02x:%02x:%02x:%02x:%02x], rssi: [%d] \r\n",
                      recv_adv->adv_type, recv_adv->adv_addr_type, recv_adv->adv_addr[0], recv_adv->adv_addr[1], recv_adv->adv_addr[2],
                      recv_adv->adv_addr[3], recv_adv->adv_addr[4], recv_adv->adv_addr[5], recv_adv->rssi);
            
            #if CFG_ENABLE_QUECTEL_BLE_CENTRAL
            ql_ble_demo_report_adv_deal(recv_adv);
            #endif

            break;
        }
        
        case QL_BLE_MTU_CHANGE_EVENT:
        {
            ql_ble_mtu_change_t *mtu_change = (ql_ble_mtu_change_t *)param;
            
            os_printf("conn_idx: [%d], mtu_size: [%d] \r\n", mtu_change->conn_idx, mtu_change->mtu);
            
            #if CFG_ENABLE_QUECTEL_BLE_CENTRAL            
            ql_ble_demo_msg ble_demo_msg = {0};
            ble_demo_msg.msg_id = QL_BLE_DEMO_CEN_GATT_DISV_ALL_SRV;
            ql_ble_demo_msg_send(&ble_demo_msg);
            #endif
            break;

            break;
        }
        
        case QL_BLE_CONNECT_EVENT:
        {
            ql_ble_conn_ind_t *conn_ind = (ql_ble_conn_ind_t *)param;
            
            os_printf("conn_idx: [%d], addr_type: [%d], peer_addr: [%02x:%02x:%02x:%02x:%02x:%02x] \r\n",
                      conn_ind->conn_idx, conn_ind->peer_addr_type, conn_ind->peer_addr[0], conn_ind->peer_addr[1],
                      conn_ind->peer_addr[2], conn_ind->peer_addr[3], conn_ind->peer_addr[4], conn_ind->peer_addr[5]);

            break;
        }

        case QL_BLE_DISCONNECT_EVENT:
        {
            ql_ble_discon_ind_t *discon_ind = (ql_ble_discon_ind_t *)param;
            
            os_printf("conn_idx: [%d], reason: [%d] \r\n", discon_ind->conn_idx, discon_ind->reason);
            #if CFG_ENABLE_QUECTEL_BLE_PERIPHERA
            ql_ble_demo_msg ble_demo_msg = {0};
            ble_demo_msg.msg_id = QL_BLE_DEMO_START_ADV;
            ql_ble_demo_msg_send(&ble_demo_msg);
            #endif
            
            break;
        }
        
        case QL_BLE_INIT_CONNECT_EVENT:
        {
            ql_ble_conn_ind_t *conn_ind = (ql_ble_conn_ind_t *)param;
            
            os_printf("conn_idx: [%d], addr_type: [%d], peer_addr: [%02x:%02x:%02x:%02x:%02x:%02x] \r\n",
                      conn_ind->conn_idx, conn_ind->peer_addr_type, conn_ind->peer_addr[0], conn_ind->peer_addr[1],
                      conn_ind->peer_addr[2], conn_ind->peer_addr[3], conn_ind->peer_addr[4], conn_ind->peer_addr[5]);

            conn_hdl = conn_ind->conn_idx;   

            #if CFG_ENABLE_QUECTEL_BLE_CENTRAL
            ql_ble_demo_msg ble_demo_msg = {0};
            ble_demo_msg.msg_id = QL_BLE_DEMO_CENTRAL_EXCHANGE_MTU;
            ql_ble_demo_msg_send(&ble_demo_msg);
            #endif
        }

        case QL_BLE_ADV_STOP_EVENT:
        {
            os_printf("QL_BLE_ADV_STOP_EVENT \r\n");
            break;
        }
        
        case QL_BLE_SCAN_STOP_EVENT:
        {
            os_printf("QL_BLE_SCAN_STOP_EVENT \r\n");
            
            if(ql_ble_demo_sem)
            {
                ql_rtos_semaphore_release(ql_ble_demo_sem);
            }
            break;
        }
        
        case QL_BLE_CONN_PARAM_UPDATE_EVENT:
        {
            ql_ble_conn_param_update_ind_t *conn_param_update = (ql_ble_conn_param_update_ind_t *)param;
            
            os_printf("conn_idx:%d, con_interval:%d, con_latency:%d, sup_to:%d \r\n",
                conn_param_update->conn_idx, conn_param_update->con_interval, conn_param_update->con_latency, conn_param_update->sup_to);
            
            break;
        }

        case QL_BLE_BOND_START_EVENT:
        {
            os_printf("QL_BLE_BOND_START_EVENT \r\n");
            break;
        }

        case QL_BLE_BOND_FAIL_EVENT:
        {
            os_printf("QL_BLE_BOND_FAIL_EVENT \r\n");
            break;
        }
               
        default:
            break;
    }

}

uint16_t ql_ble_demo_gatt_cb(ql_ble_gatt_msg_t *p_msg)
{
    os_printf("%s, msg_evt: [%d], conn_idx: [%d] \r\n", __func__, p_msg->msg_evt, p_msg->conn_idx);
        
    uint8_t idx = 0;
    
    switch(p_msg->msg_evt)
    {
        case QL_BLE_GATT_MSG_WRITE_REQ:
        {
            os_printf("conn_idx: [%d], svc_id: [%d], att_idx: [%d], handle: [%d], len: [%d], data: [%s] \r\n",
                p_msg->conn_idx, p_msg->param.report.svc_id, p_msg->param.report.att_idx, p_msg->param.report.char_handle, 
                p_msg->param.report.data.len, p_msg->param.report.data.data);
                      
            ql_ble_demo_msg ble_demo_msg = {0};
            ble_demo_msg.msg_id = QL_BLE_DEMO_PER_GATT_SEND_NTF;
            ble_demo_msg.msg_param.send_ntf.con_idx = p_msg->conn_idx;
            ble_demo_msg.msg_param.send_ntf.svc_id  = p_msg->param.report.svc_id;
            ble_demo_msg.msg_param.send_ntf.att_idx = p_msg->param.report.att_idx;
            ble_demo_msg.msg_param.send_ntf.len     = p_msg->param.report.data.len;
            ble_demo_msg.msg_param.send_ntf.data = malloc(p_msg->param.report.data.len); 
            memset((void *)ble_demo_msg.msg_param.send_ntf.data, 0x00, p_msg->param.report.data.len);
            memcpy((void *)ble_demo_msg.msg_param.send_ntf.data, (const void *)p_msg->param.report.data.data, p_msg->param.report.data.len);
            ql_ble_demo_msg_send(&ble_demo_msg);
            break;
        }

        case QL_BLE_GATT_MSG_NTF_REQ:
        {
            os_printf("conn_idx: [%d], svc_id: [%d], att_idx: [%d], handle: [%d], len: [%d], data: [%s] \r\n",
                p_msg->conn_idx, p_msg->param.report.svc_id, p_msg->param.report.att_idx, p_msg->param.report.char_handle, 
                p_msg->param.report.data.len, p_msg->param.report.data.data);

            #if CFG_ENABLE_QUECTEL_BLE_CENTRAL
            ql_ble_demo_msg ble_demo_msg = {0};
            ble_demo_msg.msg_id = QL_BLE_DEMO_CEN_GATT_WRREQ;
            ql_ble_demo_msg_send(&ble_demo_msg);
            #endif
                
            break;
        }

        case QL_BLE_GATT_MSG_DISC_SVC:
        {
            os_printf("start_hdl: [%d], end_hdl: [%d], uuid_len: [%d], uuid:[", 
                p_msg->param.svc_disc.start_hdl,
                p_msg->param.svc_disc.end_hdl,
                p_msg->param.svc_disc.uuid_len);
            for(idx = 0; idx < p_msg->param.svc_disc.uuid_len; idx++)
            {
                os_printf("%02x", p_msg->param.svc_disc.uuid[idx]);
            }
            os_printf("]\r\n");
            break;
        }
        
        case QL_BLE_GATT_MSG_DISC_CHAR:
        {
            os_printf("DISC_TYPE_CHAR, handle: [%d], pro: [%d], uuid_len: [%d], puuid:[", 
                p_msg->param.char_disc.handle,
                p_msg->param.char_disc.prop,
                p_msg->param.char_disc.uuid_len);
            for(idx = 0; idx < p_msg->param.char_disc.uuid_len; idx++)
            {
                os_printf("%02x", p_msg->param.char_disc.uuid[idx]);
            }
            os_printf("]\r\n");

            if((p_msg->param.char_disc.uuid[0] == 0x01) && (p_msg->param.char_disc.uuid[1] == 0xFF))
            {
                cen_chara_hdl = p_msg->param.char_disc.handle;
                
                os_printf("cen_chara_hdl: %d \r\n", cen_chara_hdl);
            }
            
            break;
        }
        
        case QL_BLE_GATT_MSG_DISC_CHAR_DESC:
        {
            os_printf("DISC_TYPE_CHAR_DESC, handle: [%d], uuid_len: [%d], uuid:[", 
                p_msg->param.desc_disc.handle,
                p_msg->param.desc_disc.uuid_len);
            for(idx = 0; idx < p_msg->param.desc_disc.uuid_len; idx++)
            {
                os_printf("%02x", p_msg->param.desc_disc.uuid[idx]);
            }
            os_printf("]\r\n");
            
            break;
       }

       case QL_BLE_GATT_MSG_CMP_EVT:
       {
           os_printf("QL_BLE_GATT_MSG_CMP_EVT, operation: [%d], status: [%d] \r\n", 
               p_msg->param.op.operation, p_msg->param.op.status);

           if((p_msg->param.op.operation == QL_BLE_GATT_OP_PEER_SVC_DISC_END) && (cen_chara_hdl != 0))
           {
               #if CFG_ENABLE_QUECTEL_BLE_CENTRAL
               ql_ble_demo_msg ble_demo_msg = {0};
               ble_demo_msg.msg_id = QL_BLE_DEMO_CEN_GATT_NTFCFG;
               ql_ble_demo_msg_send(&ble_demo_msg);
               #endif
           }

           break;
       }


        default:
            break;

    }

    return 0;
}

#if CFG_ENABLE_QUECTEL_BLE_PERIPHERA
/**************************************************************************************************
* Description:
*	ble create profile.
* 
* Parameters:
*	none
*	
* Return:
*	none
*	
**************************************************************************************************/
static void ql_ble_demo_set_profile_db_and_adv_param(void)
{
    uint8_t ret = 0;
    uint8_t svc_uuid[16] = {0x36,0xF5,0,0,0x34,0x56,0,0,0,0,0x28,0x37,0,0,0,0};
    ql_ble_gatt_service_t service = {0};

    service.prf_task_id = 0;
    service.att_db_nb   = QL_BLE_DEMO_IDX_NB;
    service.start_hdl   = 0;
    service.att_db      = ql_ble_demo_profile_db;
    service.svc_perm    = QL_PERM_SET(SVC_UUID_LEN, UUID_128);
    memcpy((void *)&service.uuid[0], (const void *)&svc_uuid[0], 16);
    ret = ql_ble_create_db(&service, 0);
    
    os_printf("ql_ble_create_db, ret: [%d] \r\n", ret);
    
    ql_ble_adv_param_t adv_param = {0};

    adv_param.adv_intv_min = 160;
    adv_param.adv_intv_max = 160;
    adv_param.channel =  QL_BLE_ADV_CHAN_ALL;
    ql_ble_set_adv_param(adv_param);

    ql_ble_demo_msg ble_demo_msg = {0};
    ble_demo_msg.msg_id = QL_BLE_DEMO_SET_ADV_DATA;
    ql_ble_demo_msg_send(&ble_demo_msg);
}
#endif

#if CFG_ENABLE_QUECTEL_BLE_CENTRAL
/**************************************************************************************************
* Description:
*	ble start scan.
* 
* Parameters:
*	none
*	
* Return:
*	none
*	
**************************************************************************************************/
static void ql_ble_demo_start_scan(void)
{
    ql_ble_scan_param_t scan_param = {0};
    
    scan_param.scan_intv = 0x50;
    scan_param.scan_wd = 0x20;

    ql_ble_start_scaning(scan_param);
}
#endif

/**************************************************************************************************
* Description:
*	ble message processing.
* 
* Parameters:
*	none
*	
* Return:
*	none
*	
**************************************************************************************************/
static void ql_ble_demo_msg_process(ql_ble_demo_msg *ble_msg)
{
    os_printf("msg_id: %d \r\n", ble_msg->msg_id);

    switch (ble_msg->msg_id)
    {       
        case QL_BLE_DEMO_SET_ADV_DATA:
        {
            uint8_t ret = 0;
            uint8_t adv_data[31] = {0};

            adv_data[0] = 0x03;
            adv_data[1] = 0xFF;
            adv_data[2] = 0x31;
            adv_data[3] = 0x32;
            ret = ql_ble_set_adv_data(&adv_data[0], 4);
            
            os_printf("ql_ble_set_adv_data, ret: [%d] \r\n", ret);
            
            ql_ble_demo_msg ble_demo_msg = {0};
            ble_demo_msg.msg_id = QL_BLE_DEMO_SET_RSP_DATA;
            ql_ble_demo_msg_send(&ble_demo_msg);

            break;
        }

        case QL_BLE_DEMO_SET_RSP_DATA:
        {
            uint8_t ret = 0;
            uint8_t scan_rsp_data[31] = {0};
            uint8_t len = 0;

            len = snprintf((char *)&scan_rsp_data[2], sizeof(scan_rsp_data)-1, "FGM842D");
            scan_rsp_data[0] = len+1;
            scan_rsp_data[1] = 0x09;
            ret = ql_ble_set_scan_rsp_data(&scan_rsp_data[0], len+2); 
            
            os_printf("ql_ble_set_scan_rsp_data, ret: [%d] \r\n", ret);

            ql_ble_demo_msg ble_demo_msg = {0};
            ble_demo_msg.msg_id = QL_BLE_DEMO_START_ADV;
            ql_ble_demo_msg_send(&ble_demo_msg);

            break;
        }

        case QL_BLE_DEMO_START_ADV:
        {
            uint8_t ret = 0;
            
            ret = ql_ble_start_advertising(0);

            os_printf("ql_ble_start_advertising, ret: [%d] \r\n", ret);

            break;
        }

        case QL_BLE_DEMO_PER_GATT_SEND_NTF:
        {
            ql_ble_gatts_send_ntf_value(ble_msg->msg_param.send_ntf.con_idx, 
                                        ble_msg->msg_param.send_ntf.svc_id, 
                                        ble_msg->msg_param.send_ntf.att_idx, 
                                        ble_msg->msg_param.send_ntf.data, 
                                        ble_msg->msg_param.send_ntf.len);
            
            if(ble_msg->msg_param.send_ntf.data != NULL)
            {
                free(ble_msg->msg_param.send_ntf.data);
                ble_msg->msg_param.send_ntf.data = NULL;
            }
            break;
        }

        case QL_BLE_DEMO_START_SCAN:
        {
            ql_ble_scan_param_t scan_param = {0};
            
            scan_param.scan_intv = 0x50;
            scan_param.scan_wd = 0x20;
            
            ql_ble_start_scaning(scan_param);
            break;
        }
        
        case QL_BLE_DEMO_STOP_SCAN:
        {
            ql_ble_stop_scaning();
            
            ql_ble_demo_msg ble_demo_msg = {0};
            ble_demo_msg.msg_id = QL_BLE_DEMO_CONN_PEER_DEVICE;
            ql_ble_demo_msg_send(&ble_demo_msg);
            break;
        }


        case QL_BLE_DEMO_CONN_PEER_DEVICE:
        {       
            ql_ble_errcode_e ret = 0;
            
            if(ql_ble_demo_sem)
            {
                ql_rtos_semaphore_wait(ql_ble_demo_sem, QL_WAIT_FOREVER);
            }

            ret = ql_ble_set_connect_dev_addr(&peer_addr); 
            
            os_printf("set connect address, ret: %d \r\n", ret);
            
            ret = ql_ble_start_conn(0x30, 0x30, 0, 500);
            
            os_printf("start connect .... ret: %d \r\n", ret);

            break;
        }

        case QL_BLE_DEMO_CEN_GATT_DISV_ALL_SRV:
        {
            ql_ble_gattc_all_service_discovery(conn_hdl);
            break;
        }

        case QL_BLE_DEMO_CENTRAL_EXCHANGE_MTU:
        {            
            ql_ble_gatt_mtu_changes(conn_hdl, 512);
            break;
        }

        case QL_BLE_DEMO_CEN_GATT_NTFCFG:
        {      
            os_printf("QL_BLE_DEMO_CEN_GATT_NTFCFG, conn_hdl: %d, cen_chara_hdl: %d \r\n", conn_hdl, cen_chara_hdl);
            ql_ble_gattc_ntf_ind_enable(conn_hdl, cen_chara_hdl, true, false);
            break;
        }
        
        case QL_BLE_DEMO_CEN_GATT_WRREQ:
        {
            uint16_t wr_demo_data_len = 6;
            uint8_t  wr_demo_data[7] = "123456";

            ql_ble_gattc_write_data_req_with_handle(conn_hdl, cen_chara_hdl, wr_demo_data, wr_demo_data_len);

            break;
        }
                
        default:
            break;
    }
}

/**************************************************************************************************
* Description:
*	ble demo task.
* 
* Parameters:
*	arg
*	
* Return:
*	none
*	
**************************************************************************************************/
static void ql_ble_demo_entry(void *arg)
{    
    ql_ble_demo_msg ble_demo_msg;
    uint8_t ble_mac[6] = {0};

    /* Wait BLE stack initialization complete */
     while (kernel_state_get(TASK_BLE_APP) != APPM_READY)
     {
         ql_rtos_task_sleep_ms(200);
     }
     
     ql_ble_address_get(ble_mac);
     os_printf("ble_mac: [%02x:%02x:%02x:%02x:%02x:%02x] \r\n", 
        ble_mac[0], ble_mac[1], ble_mac[2], ble_mac[3], ble_mac[4], ble_mac[5]);

     /* Set ble event callback */
     ql_ble_set_notice_cb(ql_ble_demo_gap_cb);
     ql_ble_gatt_init(ql_ble_demo_gatt_cb);

     #if CFG_ENABLE_QUECTEL_BLE_PERIPHERA
     ql_ble_demo_set_profile_db_and_adv_param();
     #elif CFG_ENABLE_QUECTEL_BLE_CENTRAL
     ql_ble_demo_start_scan();
     #endif
             
    while (1)
    {
        os_memset((void *)&ble_demo_msg, 0x00, sizeof(ql_ble_demo_msg));
        
        if (ql_rtos_queue_wait(ql_ble_demo_q, (uint8 *)&ble_demo_msg, sizeof(ble_demo_msg), QL_WAIT_FOREVER) == 0)
        {
            ql_ble_demo_msg_process(&ble_demo_msg);
        }
    }
}


/**************************************************************************************************
* Description:
*	Create ble demo task.
* 
* Parameters:
*	none
*	
* Return:
*	none
*	
**************************************************************************************************/
void ql_ble_demo_thread_creat(void)
{
    ql_rtos_status ret = 0;

    ret = ql_rtos_semaphore_create(&ql_ble_demo_sem, 1);
    
	if(ret != 0)
    {
		os_printf("Failed to Create BLE semaphore \r\n");
		return;
	}

    ret = ql_rtos_queue_create(&ql_ble_demo_q, sizeof(ql_ble_demo_msg),  QL_BLE_DEMO_QUEUE_MAX_NB);
	
	if(ret != 0)
    {
		os_printf("Failed to Create BLE msg queue \r\n");
		return;
	}
    
    ret = ql_rtos_task_create(&ql_ble_demo_task,
                              2*1024,
                              THD_EXTENDED_APP_PRIORITY,
                              "ble_demo",
                              ql_ble_demo_entry,
                              0);

    if (ret != 0)
    {
        os_printf("Error: Failed to create ble task, ret: [%d] \r\n", ret);
        
        if (ql_ble_demo_q != NULL)
        {
            ql_rtos_queue_delete(ql_ble_demo_q);
            ql_ble_demo_q = NULL;
        }
        
        if (ql_ble_demo_task != NULL)
        {
            ql_rtos_task_delete(ql_ble_demo_task);
            ql_ble_demo_task = NULL;
        }
        return ;
    }

    return;
}

