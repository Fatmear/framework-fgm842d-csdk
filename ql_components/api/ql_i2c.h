/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef _QL_I2C_H_
#define _QL_I2C_H_

#include "ql_api_common.h"

typedef enum
{
    QL_I2C_SUCCESS          = 0,
    QL_I2C_INIT_ERR=1| (QL_COMPONENT_BSP_I2C << 16),
    QL_I2C_ID_INIT_ERR,
    QL_I2C_SM_BUS_ERR,
    QL_I2C_ACK_TIMEOUT_ERR,
    QL_I2C_WRITE_ERR,
    QL_I2C_READ_ERR,
}ql_i2c_errcode_e;


typedef enum
{
    QL_I2C_MEM_ADDR_SIZE_8BIT   = 0,
    QL_I2C_MEM_ADDR_SIZE_16BIT,
}ql_i2c_mem_addr_size_e;

typedef enum
{
    QL_I2C2 ,
}ql_i2c_id_e;


typedef enum
{
    QL_I2C_ADDR_SIZE_7BIT   = 0,
    QL_I2C_ADDR_SIZE_10BIT,
}ql_i2c_addr_mode_e;

typedef enum
{
    QL_I2C_SPEED_STANDARD   = 0,
    QL_I2C_SPEED_FAST,
}ql_i2c_speed_mode_e;

extern ql_i2c_errcode_e ql_i2c_init(ql_i2c_id_e iic_id,
                            ql_i2c_speed_mode_e speed_mode,
                            ql_i2c_addr_mode_e addr_mode,
                            uint16 slave_addr);


extern ql_i2c_errcode_e ql_i2c_deinit(ql_i2c_id_e iic_id);


extern ql_i2c_errcode_e ql_i2c_master_write(ql_i2c_id_e iic_id,
                                    uint32 dev_addr,
                                    const uint8* data,
                                    uint32 size);


extern ql_i2c_errcode_e ql_i2c_master_read(ql_i2c_id_e iic_id,
                                    uint32 dev_addr,
                                    uint8 *data,
                                    uint32 size);


extern ql_i2c_errcode_e ql_i2c_master_mem_write(ql_i2c_id_e iic_id,
                                    uint32 dev_addr,
                                    uint32 mem_addr,
                                    ql_i2c_mem_addr_size_e mem_size,                                    
                                    uint8* data,
                                    uint32 size);


extern ql_i2c_errcode_e ql_i2c_master_mem_read(ql_i2c_id_e iic_id,
                                    uint32 dev_addr,
                                    uint32 mem_addr,
                                    ql_i2c_mem_addr_size_e mem_size,                                    
                                    uint8* data,
                                    uint32 size);



extern ql_i2c_errcode_e ql_i2c_slave_write(ql_i2c_id_e iic_id, const uint8 *data, uint32 size);   


extern ql_i2c_errcode_e ql_i2c_slave_read(ql_i2c_id_e iic_id, uint8 *data, uint32 size);

extern void ql_i2c_demo_thread_creat(void);

#endif




































