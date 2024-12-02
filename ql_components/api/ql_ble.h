/*================================================================
  Copyright (c) 2024, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef __QL_BLE_H__
#define __QL_BLE_H__
/**************************************************************************************************
* include
**************************************************************************************************/
#include "app_ble.h"
#include "common_bt_defines.h"
/**************************************************************************************************
* define
**************************************************************************************************/
#define QL_BLE_ADV_INTERVAL_MIN     32     //UNIT:0.625MS
#define QL_BLE_ADV_INTERVAL_MAX     16384  //UNIT:0.625MS
#define QL_BLE_SCAN_INTERVAL_MIN    18     //UNIT:0.625MS
#define QL_BLE_SCAN_INTERVAL_MAX    4096   //UNIT:0.625MS
#define QL_BLE_SCAN_WINDOW_MIN      17     //UNIT:0.625MS
#define QL_BLE_SCAN_WINDOW_MAX      4096   //UNIT:0.625MS
#define QL_BLE_CONNECT_INTERVAL_MIN 6      //UNIT:1.25MS
#define QL_BLE_CONNECT_INTERVAL_MAX 3200   //UNIT:1.25MS
#define QL_BLE_CONNECT_TIMEOUT_MIN  10     //UNIT:10MS
#define QL_BLE_CONNECT_TIMEOUT_MAX  3200   //UNIT:10MS
#define QL_BLE_DEVICE_NAME_MAX_LEN  18


#define QL_BLE_PROP(prop)           (GATT_PROP_##prop##_BIT) 
#define QL_BLE_OPT(opt)             (GATT_ATT_##opt##_BIT)
#define QL_PERM_SET(access, right)  (((QL_PERM_RIGHT_ ## right) << (access ## _POS)) & (access ## _MASK))
/**************************************************************************************************
* enum
**************************************************************************************************/
typedef enum
{
    QL_BLE_SUCCESS = 0,
	QL_BLE_ERR_PROFILE,
	QL_BLE_ERR_CREATE_DB,
	QL_BLE_ERR_CMD_NOT_SUPPORT,
	QL_BLE_ERR_UNKNOW_IDX,
	QL_BLE_ERR_BLE_STATUS,
	QL_BLE_ERR_BLE_PARAM,
	QL_BLE_ERR_ADV_DATA,
	QL_BLE_ERR_CMD_RUN,
	QL_BLE_ERR_NO_MEM,
	QL_BLE_ERR_INIT_CREATE,
	QL_BLE_ERR_INIT_STATE,
	QL_BLE_ERR_ATTC_WRITE,
	QL_BLE_ERR_ATTC_WRITE_UNREGISTER,
}ql_ble_errcode_e;
    
enum
{
    QL_PERM_RIGHT_UUID_16         = 0,
    QL_PERM_RIGHT_UUID_32         = 1,
    QL_PERM_RIGHT_UUID_128        = 2,
    QL_PERM_RIGHT_UUID_RFU        = 3,
};

typedef enum
{
    QL_BLE_STACK_OK = 0,
    QL_BLE_REPORT_ADV_EVENT,
    QL_BLE_MTU_CHANGE_EVENT,
    QL_BLE_CONNECT_EVENT,
    QL_BLE_DISCONNECT_EVENT,
    QL_BLE_INIT_CONNECT_EVENT,
    QL_BLE_ADV_STOP_EVENT,
    QL_BLE_SCAN_STOP_EVENT,
    QL_BLE_CONN_PARAM_UPDATE_EVENT,
    QL_BLE_LINK_RSSI_EVENT,
    QL_BLE_SEC_MASTER_AUTH_REQ,
    QL_BLE_SEC_MASTER_ENCRYPT,
    QL_BLE_SEC_SLAVE_ENCRYPT,
    QL_BLE_BOND_START_EVENT,
    QL_BLE_SEC_PEER_IDENTITY_ADDR,
    QL_BLE_BOND_FAIL_EVENT,  
}ql_ble_notify_e;

typedef enum
{
    QL_BLE_PHY_ANY    = 0,
    QL_BLE_PHY_1MBPS  = 1,
    QL_BLE_PHY_2MBPS  = 2,
    QL_BLE_PHY_CODED  = 3,
}ql_ble_phy_e;

typedef enum
{
  QL_BLE_ADV_MODE_UNDIRECT                        = 0x01, // scannalbe & connectable
  QL_BLE_ADV_MODE_DIRECT                          = 0x02, // non-scannalbe & connectable
  QL_BLE_ADV_MODE_NON_CONN_NON_SCAN               = 0x03, // non-scannalbe & non-connectable
  QL_BLE_ADV_MODE_NON_CONN_SCAN                   = 0x04, // scannalbe & non-connectable
  QL_BLE_ADV_MODE_HDC_DIRECT                      = 0x05, // non-scannalbe & connectable
  QL_BLE_ADV_MODE_BEACON                          = 0x06, // non-scannalbe & non-connectable
  QL_BLE_ADV_MODE_CUSTOM                          = 0x07, // scannalbe & connectable & custom adv type flags
  QL_BLE_ADV_MODE_EXTEND_CONN_UNDIRECT            = 0x11,
  QL_BLE_ADV_MODE_EXTEND_CONN_DIRECT              = 0x12,
  QL_BLE_ADV_MODE_EXTEND_NON_CONN_SCAN            = 0x13,
  QL_BLE_ADV_MODE_EXTEND_NON_CONN_SCAN_DIRECT     = 0x14,
  QL_BLE_ADV_MODE_EXTEND_NON_CONN_NON_SCAN        = 0x15,
  QL_BLE_ADV_MODE_EXTEND_NON_CONN_NON_SCAN_DIRECT = 0x16,
  QL_BLE_ADV_MODE_PER_ADV_UNDIRECT                = 0x21,
  QL_BLE_ADV_MODE_PER_ADV_DIRECT                  = 0x22,
}ql_ble_adv_mode_e;
    
typedef enum
{
    QL_BLE_ADDR_TYPE_PUBLIC = 0,
    QL_BLE_ADDR_TYPE_PRIVATE,
    QL_BLE_ADDR_TYPE_RANDOM_RESOVABLE,
    QL_BLE_ADDR_TYPE_RANDOM_NONE_RESOVABLE,
}ql_ble_addr_type_e;

typedef enum
{
    QL_BLE_ADV_CHAN_37  = 0x01,
    QL_BLE_ADV_CHAN_38  = 0x02,
    QL_BLE_ADV_CHAN_39  = 0x04,
    QL_BLE_ADV_CHAN_ALL = 0X07,
}ql_ble_adv_channel_e;

typedef enum
{
  QL_BLE_ADV_ALLOW_SCAN_ANY_CON_ANY   = 0x00,
  QL_BLE_ADV_ALLOW_SCAN_WLST_CON_ANY  = 0x01,
  QL_BLE_ADV_ALLOW_SCAN_ANY_CON_WLST  = 0x02,
  QL_BLE_ADV_ALLOW_SCAN_WLST_CON_WLST = 0x03,
}ql_ble_adv_filter_e;

typedef enum
{
  QL_BLE_ADV_DISC_MODE_GEN_DISC = 0, 
  QL_BLE_ADV_DISC_MODE_LIM_DISC = 1,
  QL_BLE_ADV_DISC_MODE_NON_DISC = 2,
  QL_BLE_ADV_DISC_MODE_MAX      = 3,
}ql_ble_adv_disc_mode_e;

typedef enum
{
    QL_BLE_IO_CAP_DISPLAY_ONLY        = 0x00,
    QL_BLE_IO_CAP_DISPLAY_YES_NO      = 0x01,
    QL_BLE_IO_CAP_KEYBOARD_ONLY       = 0x02,
    QL_BLE_IO_CAP_NO_INPUT_NO_OUTPUT  = 0x03, 
    QL_BLE_IO_CAP_KEYBOARD_DISPLAY    = 0x04,
}ql_ble_io_cap_e;

typedef enum
{
  QL_BLE_SCAN_MODE_GEN_DISC = 0,     /// General discoverable
  QL_BLE_SCAN_MODE_OBSERVER = 1,     /// Observer
  QL_BLE_SCAN_MODE_MAX      = 3,
}ql_ble_scan_mode_e;


typedef enum
{
    QL_BLE_GATT_MSG_READ_REQ,             //!< GATT read request
    QL_BLE_GATT_MSG_WRITE_REQ,            //!< GATT write request
    QL_BLE_GATT_MSG_ATT_INFO_REQ,         //!< GATT att information request
    QL_BLE_GATT_MSG_NTF_REQ,              //!< GATT notification received
    QL_BLE_GATT_MSG_IND_REQ,              //!< GATT indication received
    QL_BLE_GATT_MSG_READ_IND,             //!< GATT read response received
    QL_BLE_GATT_MSG_CMP_EVT,              //!< GATT message complete event
    QL_BLE_GATT_MSG_LINK_CREATE,          //!< A Link is established
    QL_BLE_GATT_MSG_LINK_LOST,            //!< A Link is lost
    QL_BLE_GATT_MSG_DISC_SVC,             //!< Discovery All Service
    QL_BLE_GATT_MSG_DISC_SVC_INC,         //!< Discovery Included Service
    QL_BLE_GATT_MSG_DISC_CHAR,            //!< Discovery Specific Characteristic
    QL_BLE_GATT_MSG_DISC_CHAR_DESC,       //!< Discovery Specific Descriptorsr

    QL_BLE_GATT_MSG_HANDLE_ERROR = 0x80,  //!< Application cannot deal message correctly, error code is stored in gatt_msg_t->op->status
}ql_ble_gatt_msg_evt_t;

typedef enum
{
    QL_BLE_GATT_OP_NONE,
    QL_BLE_GATT_OP_NOTIFY,                 //!< GATT notification operation
    QL_BLE_GATT_OP_INDICATION,             //!< GATT indication operation
    QL_BLE_GATT_OP_WRITE_REQ,              //!< GATT write request operation
    QL_BLE_GATT_OP_WRITE_CMD,              //!< GATT write command operation
    QL_BLE_GATT_OP_READ,                   //!< GATT read operation
    QL_BLE_GATT_OP_PEER_SVC_DISC_END,      //!< GATT peer device service discovery is ended
}ql_ble_gatt_operation;

typedef enum 
{
    QL_BLE_GATT_PROP_BROADCAST    = 0x01, 
    QL_BLE_GATT_PROP_READ         = 0x02,
    QL_BLE_GATT_PROP_WRITE_CMD    = 0x04, 
    QL_BLE_GATT_PROP_WRITE        = 0x08, 
    QL_BLE_GATT_PROP_NOTIFY       = 0x10, 
    QL_BLE_GATT_PROP_INDICATE     = 0x20, 
    QL_BLE_GATT_PROP_WRITE_SIGNED = 0x40, 
    QL_BLE_GATT_PROP_EXTENDED     = 0x80, 
}ql_ble_gatt_prop_e;

typedef enum
{
  QL_BLE_PAIRING_MODE_NO_PAIRING    = 0x00,  //!< Pairing is not allowed
  QL_BLE_PAIRING_MODE_WAIT_FOR_REQ  = 0x01,  //!< Wait for a pairing request or slave security request
  QL_BLE_PAIRING_MODE_INITIATE      = 0x02,  //!< Don't wait, initiate a pairing request or slave security request
}ql_ble_pair_mode_e;
/**************************************************************************************************
* struct
**************************************************************************************************/
typedef struct
{
    uint8_t adv_type;/* 0x00   Connectable scannable undirected advertising
                        0x04   Scan Response 
                      */
    uint8_t adv_addr_type;
    uint8_t adv_addr[6];
    uint8_t data_len;
    uint8_t data[256];
    int8_t  rssi;
}ql_ble_recv_adv_t; /* QL_BLE_REPORT_ADV_EVENT */

typedef struct
{
    uint8_t  conn_idx;
    uint16_t mtu;
}ql_ble_mtu_change_t; /* QL_BLE_MTU_CHANGE_EVENT */

typedef struct
{
    uint8_t  conn_idx;
    uint8_t  peer_addr_type;
    uint8_t  peer_addr[6];
    uint16_t con_interval;   //!< Connection interval Not supported yet.
    uint16_t con_latency;    //!< Slave latency  Not supported yet.
    uint16_t sup_to;         //!< Supervision timeout  Not supported yet.
}ql_ble_conn_ind_t; /* QL_BLE_CONNECT_EVENT / QL_BLE_INIT_CONNECT_EVENT */

typedef struct
{
    uint8_t conn_idx;
    uint8_t reason;
}ql_ble_discon_ind_t; /* QL_BLE_DISCONNECT_EVENT */

typedef struct
{
    uint8_t  conn_idx;
    uint16_t con_interval;   //!< Connection interval
    uint16_t con_latency;    //!< Slave latency
    uint16_t sup_to;         //!< Supervision timeout
}ql_ble_conn_param_update_ind_t; /* QL_BLE_CONN_PARAM_UPDATE_EVENT */

typedef struct
{
    uint8_t  addr[6];
    uint8_t  addr_type;
}ql_ble_adv_mac_addr_t;

typedef struct
{
    ql_ble_adv_mode_e       mode;      //Not supported yet.
    ql_ble_addr_type_e      addr_type; //Not supported yet.
    ql_ble_adv_mac_addr_t   peer_addr; //Not supported yet.
    ql_ble_phy_e            phy;       //Not supported yet.
    uint16_t                adv_intv_min; 
    uint16_t                adv_intv_max;
    ql_ble_adv_channel_e    channel;
    ql_ble_adv_filter_e     filter;    //Not supported yet.
    uint8_t                 adv_sid;   //Not supported yet.             
    uint16_t                per_adv_intv_min; //Not supported yet.     
    uint16_t                per_adv_intv_max; //Not supported yet.      
  	ql_ble_adv_disc_mode_e  disc_mode; //Not supported yet.
}ql_ble_adv_param_t;

typedef struct
{
  ql_ble_scan_mode_e scan_mode;    //scan mode  Not supported yet. 
  ql_ble_phy_e       phy;          //physical select  Not supported yet. 
  uint8_t            dup_filt;     //scan duplicated packet filter enable.0:do not filter,1:filter duplicated packet  Not supported yet. 
  uint16_t           scan_intv;    //scan interval.unit:625us
  uint16_t           scan_wd;      //scan windows.unit:625us
}ql_ble_scan_param_t;

typedef struct
{
	uint8_t  uuid[16];
	uint16_t info;
	uint16_t ext_info;
}ql_ble_attm_desc_t;

typedef struct 
{
	uint16_t prf_task_id;       //Service idx
	uint8_t  uuid[16];          //Service uuid
	uint8_t  att_db_nb;         //Number of db
	uint16_t start_hdl;         //Start handler, 0 means autoalloc
	ql_ble_attm_desc_t* att_db; //Attribute database
	uint8_t svc_perm;           //Service config
}ql_ble_gatt_service_t;

typedef struct
{
    bool     mitm;              //!< Man In The Middle mode enalbe/disable  //Not supported yet. 
    bool     ble_secure_conn;   //!< BLE Secure Simple Pairing, also called Secure Connection mode.
    ql_ble_io_cap_e  io_cap;    //!< IO capbilities
    ql_ble_pair_mode_e  pair_init_mode;   //!< If initialize pairing procesure or not  //Not supported yet. 
    bool     bond_auth;         //!< Bond_auth enable/disable,if true, then will distribute encryption key,and will check this key_req when bonding.
    uint32_t password;          //!< Password.range:[000,000 , 999,999]. The keboard device shall ensure that all 6 digits are inputed 锟斤拷C including zeros.
}ql_ble_security_param_t;

typedef struct 
{
    uint8_t  uuid_len;     //Service UUID Length
    uint8_t  uuid[16];     //Service UUID 
    uint16_t start_hdl;    //Service start handle
    uint16_t end_hdl;      //Service end handle
}ql_ble_gatt_svc_disc_s; /* QL_BLE_GATT_MSG_DISC_SVC */

typedef struct 
{
    uint8_t  uuid_len;     //Include service UUID Length
    uint8_t  uuid[16];     //Include service UUID
    uint16_t start_hdl;    //Include service start handle
    uint16_t end_hdl;      //Include service end handle
}ql_ble_gatt_svc_inc_s;  /* QL_BLE_GATT_MSG_DISC_SVC_INC */

typedef struct
{
    uint8_t  uuid_len;      //Charcateristic UUID length
    uint8_t  uuid[16];      //Charcateristic UUID 
    uint16_t handle;        //Value handle
    ql_ble_gatt_prop_e  prop; 
}ql_ble_gatt_char_disc_s; /* QL_BLE_GATT_MSG_DISC_CHAR */   

typedef struct
{
    uint8_t  uuid_len;     
    uint8_t  uuid[16];    
    uint16_t handle;     
}ql_ble_gatt_desc_disc_s; /* QL_BLE_GATT_MSG_DISC_CHAR_DESC */    

typedef struct
{
    uint16_t len;  //! Ble Data Len 
    uint8_t *data; //! Ble Data Pointer
} ql_ble_data_t;

typedef struct
{
    uint8_t         svc_id;     //!< service id of this message
    uint16_t        att_idx;    //!< Attribute index of in the service table
    uint16_t        char_handle;//!< Specify one characteristic handle  
    ql_ble_data_t   data;       //!< Report Data
} ql_ble_gatt_data_report;

typedef struct
{
    ql_ble_gatt_operation operation; //!< GATT request type
    uint8_t status;                  //!< Status of the request
    void * arg;                      //!< Parameter pointer
}ql_ble_gatt_op_cmp_t;

typedef struct
{
    ql_ble_gatt_msg_evt_t msg_evt;  //!< The event that message come with
    uint8_t               conn_idx; //!< Connection index
    union
    {
        ql_ble_gatt_data_report report;    //!< GATT message, length, data pointer
        ql_ble_gatt_op_cmp_t    op;        //!< GATT operation, read, write, notification, indication
        ql_ble_gatt_svc_disc_s  svc_disc;  //valid when msg_evt == QL_BLE_GATT_MSG_DISC_SVC
        ql_ble_gatt_svc_inc_s   svc_inc;   //valid when msg_evt == QL_BLE_GATT_MSG_DISC_SVC_INC
        ql_ble_gatt_char_disc_s char_disc; //valid when msg_evt == QL_BLE_GATT_MSG_DISC_CHAR
        ql_ble_gatt_desc_disc_s desc_disc; //valid when msg_evt == QL_BLE_GATT_MSG_DISC_CHAR_DESC
    } param;
}ql_ble_gatt_msg_t;


typedef void (*ql_ble_notice_cb)(ql_ble_notify_e notice, void *param);
typedef uint16_t (*ql_ble_gatt_msg_handler_t)(ql_ble_gatt_msg_t *p_msg);
/**************************************************************************************************
* API
**************************************************************************************************/
/**************************************************************************************************
* Function: ql_ble_address_get
*
* Description:
*	This function is used to obtain the MAC address of BLE.
* 
* Parameters:
*	mac_addr				[out]		BLE MAC address
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_address_get(uint8_t *mac_addr);

/**************************************************************************************************
* Function: ql_ble_set_notice_cb
*
* Description:
*	This function is used to register the BLE event callback function.
* 
* Parameters:
*	callback				[in]		BLE event callback function
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_set_notice_cb(ql_ble_notice_cb callback);

/**************************************************************************************************
* Function: ql_ble_set_adv_param
*
* Description:
*	This function is used to set broadcast parameters.
* 
* Parameters:
*	adv_param				[in]		Broadcast parameters
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_set_adv_param(ql_ble_adv_param_t adv_param);

/**************************************************************************************************
* Function: ql_ble_set_adv_data
*
* Description:
*	This function is used to set broadcast data.
* 
* Parameters:
*	adv_buff				[in]		Broadcast data 
*	adv_len				    [in]		Broadcast data length
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_set_adv_data(uint8_t *adv_buff, uint16_t adv_len);

/**************************************************************************************************
* Function: ql_ble_set_scan_rsp_data
*
* Description:
*	This function is used to set the scan response data.
* 
* Parameters:
*	scan_rsp				[in]		Scan response data 
*	scan_rsp_len			[in]		Scan response data length
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_set_scan_rsp_data(uint8_t *scan_rsp, uint16_t scan_rsp_len);

/**************************************************************************************************
* Function: ql_ble_start_advertising
*
* Description:
*	This function is used to enable BLE broadcast.
* 
* Parameters:
*	duration				[in]		broadcast duration 
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_start_advertising(uint16_t duration);

/**************************************************************************************************
* Function: ql_ble_stop_advertising
*
* Description:
*	This function is used to stop BLE broadcast.
* 
* Parameters:
*	none
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_stop_advertising(void);

/**************************************************************************************************
* Function: ql_ble_update_param
*
* Description:
*	This function is used to update connection parameters.
* 
* Parameters:
*	conn_idx				[in]		Connection handle
*   intv_min      			[in]	    Minimum connection interval
*   intv_max 				[in]		Maximum connection interval
*   latency      			[in]		The number of connection intervals that peripheral devices can ignore
*   sup_to      			[in]		Connection timeout
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_update_param(uint8_t conn_idx, uint16_t intv_min, uint16_t intv_max, 
                                    uint16_t latency, uint16_t sup_to);

/**************************************************************************************************
* Function: ql_ble_set_dev_name
*
* Description:
*	This function is used to set the local name.
* 
* Parameters:
*	name				    [in]		device name
*   name_len      			[in]	    device name length
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_set_dev_name(uint8_t *name , uint8_t name_len);

/**************************************************************************************************
* Function: ql_ble_start_scaning
*
* Description:
*	This function is used to enable BLE scanning.
* 
* Parameters:
*   scan_param 				[in]		Scan parameters
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_start_scaning(ql_ble_scan_param_t scan_param);

/**************************************************************************************************
* Function: ql_ble_stop_scaning
*
* Description:
*	This function is used to stop BLE scanning
* 
* Parameters:
*	none
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_stop_scaning(void);

/**************************************************************************************************
* Function: ql_ble_set_connect_dev_addr
*
* Description:
*	Set the address of the BLE device to be connected.
* 
* Parameters:
*   addr      			    [in]		peer device address parameters
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_set_connect_dev_addr(ql_ble_adv_mac_addr_t *addr);

/**************************************************************************************************
* Function: ql_ble_start_conn
*
* Description:
*	This function is used to initiate a connection.
* 
* Parameters:
*   intv_min      			[in]		Minimum connection interval
*   intv_max          		[in]		Maximum connection interval
*   latency           		[in]		The number of connection intervals that peripheral devices can ignore
*   sup_to      			[in]		Connection timeout
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_start_conn(uint16_t intv_min,uint16_t intv_max,uint16_t latency, uint16_t sup_to);

/**************************************************************************************************
* Function: ql_ble_stop_conn
*
* Description:
*	This function is used to cancel the connection program.
* 
* Parameters:
*	none 				
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_stop_conn(void);

/**************************************************************************************************
* Function: ql_ble_disconnect
*
* Description:
*	This function is used for the module to actively disconnect.
* 
* Parameters:
*	conn_idx				[in]		Connection handle
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_disconnect(uint8_t conidx);

/**************************************************************************************************
* Function: ql_ble_create_db
*
* Description:
*	This function is used to customize the BLE service.
* 
* Parameters:
*	service 				[in]		BLE service list
*	svc_id  				[in]		BLE service ID(Not supported yet)
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_create_db(ql_ble_gatt_service_t *service, uint8_t *svc_id);

/**************************************************************************************************
* Function: ql_ble_gatt_init
*
* Description:
*	This function is used to register the BLE gatt event callback function.
* 
* Parameters:
*	p_client				[in]		BLE gatt event callback function
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_gatt_init(ql_ble_gatt_msg_handler_t gatt_evt);

/**************************************************************************************************
* Function: ql_ble_gatts_send_ntf_value
*
* Description:
*	This function is used by the module as a peripheral device to send data to the central device through notification.
* 
* Parameters:
*	con_idx				    [in]		Connection handle
*   svc_id      			[in]	    Service ID 
*   att_idx 				[in]		Characteristic index
*   data      			    [in]		data
*   len      			    [in]		data len
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_gatts_send_ntf_value(uint8_t con_idx, uint8_t svc_id, uint8_t att_idx, uint8_t *data, uint16_t len);

/**************************************************************************************************
* Function: ql_ble_gatts_send_ind_value
*
* Description:
*	This function is used by the module as a peripheral device to send data to the central device through instructions.
* 
* Parameters:
*	con_idx				    [in]		Connection handle
*   svc_id      			[in]	    Service ID 
*   att_idx 				[in]		Characteristic index
*   data      			    [in]		data
*   len      			    [in]		data len
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_gatts_send_ind_value(uint8_t con_idx, uint8_t svc_id, uint8_t att_idx, uint8_t *data, uint16_t len);

/**************************************************************************************************
* Function: ql_ble_gattc_all_service_discovery
*
* Description:
*	The module acts as a central device to discover all services of peripheral devices.
* 
* Parameters:
*	conidx				[in]		Connection handle
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_gattc_all_service_discovery(uint8_t conidx);

/**************************************************************************************************
* Function: ql_ble_gattc_ntf_ind_enable
*
* Description:
*	The module acts as a central device to enable notification or indication of peripheral devices. 
* 
* Parameters:
*	conidx				    [in]		Connection handle
*   handle      			[in]	    characteristic handle.
*   ntf 				    [in]		Whether to enable notifications. 
*   ind 				    [in]		Whether to enable instructions. 
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_gattc_ntf_ind_enable(uint8_t conidx , uint8_t handle , bool ntf , bool ind);

/**************************************************************************************************
* Function: ql_ble_gattc_write_data_req_with_handle
*
* Description:
*	This function is used by the module as a central device to write data in a requested manner 
*        to the characteristic value handle specified by the peripheral device.
* 
* Parameters:
*	conidx				    [in]		Connection handle
*   handle      			[in]	    characteristic handle
*   data 				    [in]		data
*   data_len 				[in]		data len
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_gattc_write_data_req_with_handle(uint8_t conidx, uint16_t handle, uint8_t *data, uint16_t data_len);

/**************************************************************************************************
* Function: ql_ble_gattc_write_data_cmd_with_handle
*
* Description:
*	The function is used by the module as a central device to specify a handle to the peripheral
*       device and write data in the form of commands.
* 
* Parameters:
*	conidx				    [in]		Connection handle
*   handle      			[in]	    characteristic handle
*   data 				    [in]		data
*   data_len 				[in]		data len 
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_gattc_write_data_cmd_with_handle(uint8_t conidx, uint16_t handle, uint8_t *data, uint16_t data_len);

/**************************************************************************************************
* Function: ql_ble_gattc_read_data
*
* Description:
*	This function is used by modules as central devices to read data.s
* 
* Parameters:
*	conidx				    [in]		Connection handle
*   handle      			[in]	    characteristic handle
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_gattc_read_data(uint8_t conidx, uint16_t handle);

/**************************************************************************************************
* Function: ql_ble_gatt_mtu_changes
*
* Description:
*	This function is used to update the MTU value.
* 
* Parameters:
*	conn_idx				[in]		Connection handle
*	mtu_size				[in]		MTU value
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_gatt_mtu_changes(uint8_t conn_idx, uint16_t mtu_size);

/**************************************************************************************************
* Function: ql_ble_security_param_init
*
* Description:
*	This function is used to set security feature parameters.
* 
* Parameters:
*	param				    [in]		Safety feature parameters
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_security_param_init(ql_ble_security_param_t *param);

/**************************************************************************************************
* Function: ql_ble_security_req
*
* Description:
*	This function is used to send a secure connection request.
* 
* Parameters:
*	conidx				    [in]		Connection handle
*	
* Return:
*	result code
*	
**************************************************************************************************/
ql_ble_errcode_e ql_ble_security_req(uint8_t conidx);

#endif
