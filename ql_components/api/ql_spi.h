/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef _QL_SPI_H
#define _QL_SPI_H

#include "ql_api_common.h"

#define SPI_TEST_LEN  100

#define spi_test_speed 10000000

typedef enum
{
    QL_SPI_ID0         = 0,
    QL_SPI_ID_MAX,
}ql_spi_id_e;



typedef enum
{
    QL_SPI_ROLE_SLAVE    = 0,       /**< SPI as Master */ 
    QL_SPI_ROLE_MASTER,             /**< SPI ad SLAVE */
}ql_spi_role_e;

typedef enum
{
    QL_SPI_POL_PHA_MODE0    = 0,    /**< CPOL_L, CPHA_L */
    QL_SPI_POL_PHA_MODE1,           /**< CPOL_L, CPHA_H */
    QL_SPI_POL_PHA_MODE2,           /**< CPOL_H, CPHA_L */
    QL_SPI_POL_PHA_MODE3,           /**< CPOL_H, CPHA_H */
}ql_spi_pol_pha_mode_e;

typedef enum
{
    QL_SPI_MSB_FIRST      = 0,
    QL_SPI_LSB_FIRST,
}ql_spi_bit_order_e;


typedef enum
{
    QL_SPI_BIT_WIDTH_8BITS  = 0,
    QL_SPI_BIT_WIDTH_16BITS,
}ql_spi_bit_width_e;


typedef struct 
{
    uint32                    clk; 
    uint8_t                     dma;
    ql_spi_role_e               role;
    ql_spi_pol_pha_mode_e       pol_pha_mode;
    ql_spi_bit_order_e          bit_order;
    ql_spi_bit_width_e          bit_width;
}ql_spi_config_s;

typedef struct 
{
   const void *send_buf;    /**< the data need to send */
   uint32 send_len;       /**< the data length to send */

   void *recv_buf;          /**< the data need to receive */
   uint32 recv_len;       /**< the data length need to receive */
}ql_spi_message_s;

typedef enum
{
    QL_SPI_SUCCESS              = 0,
    QL_SPI_EXECUTE_ERR,
    QL_SPI_INVALID_PARAM_ERR,
    QL_SPI_NOT_INIT_ERR,
}ql_spi_errcode_e;


ql_spi_errcode_e ql_spi_init(ql_spi_id_e spi_id, ql_spi_config_s *spi_cfg);


ql_spi_errcode_e ql_spi_transfer(ql_spi_id_e spi_id, ql_spi_message_s *spi_msg);

ql_spi_errcode_e ql_spi_deinit(ql_spi_id_e spi_id);

ql_spi_errcode_e ql_spi_write_bytes(ql_spi_id_e spi_id, void *data, uint32 size);


ql_spi_errcode_e ql_spi_read_bytes(ql_spi_id_e spi_id, void *data, uint32 size);


void ql_spi_demo_thread_creat(void);

#endif 

