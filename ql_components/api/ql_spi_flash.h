/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef _QL_SPI_FLASH_H
#define _QL_SPI_FLASH_H

#include "ql_api_common.h"

typedef enum {
  ERASE_ALL = 0,  // erase all flash
  ERASE_SECTOR,   // erase the sector
  ERASE_BLOCK,    // erase the block
} ql_spi_flash_erase_e;

typedef enum
{
	 QL_SPI_FLASH_SUCCESS = 0,
	 QL_SPI_FLASH_EXECUTE_ERR,
	 QL_SPI_FLASH_PARAM_ERROR,
} ql_spi_flash_errcode_e;

typedef enum _flash_driver_e {
  DRIVER_SPI = 0,
  DRIVER_QSPI,
} ql_spi_flash_driver_e;


typedef struct _ql_spi_flash_info_t {
  char *type_name;  // flash型号名字
  enum _flash_driver_e driver_type;
  uint32 id;
  uint32 page_size;//256 Byte
  uint32 sector_size;//4096 Byte
  uint32 block_size;//65535 Byte
  uint32 capacity;  // flash capacity:byte
} ql_spi_flash_info_t;



ql_spi_flash_errcode_e ql_spi_flash_get_info(ql_spi_flash_info_t *flash_info);

ql_spi_flash_errcode_e ql_spi_flash_enable(bool status);

ql_spi_flash_errcode_e ql_spi_flash_read( uint32 addr, uint8_t *buf, uint32 len);
ql_spi_flash_errcode_e ql_spi_flash_write(uint32 addr,uint8_t *buf, uint32 len);

ql_spi_flash_errcode_e ql_spi_flash_erase(uint32 addr,
                                          ql_spi_flash_erase_e type);

UINT32 ql_spi_flash_read_id(void);										  

void ql_spi_flash_demo_thread_creat(void);

#endif 

