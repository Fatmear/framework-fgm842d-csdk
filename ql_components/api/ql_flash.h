/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef _QL_FLASH_H
#define _QL_FLASH_H

#include "ql_api_common.h"

typedef enum
{
	 QL_FLASH_SUCCESS = 0,
	 QL_FLASH_EXECUTE_ERR=1| (QL_COMPONENT_STORAGE_EXTFLASH << 16),
	 QL_FLASH_PARAM_ERROR,
} ql_flash_errcode_e;

typedef enum
{
    QL_FLASH_PROTECT_NONE = 0,
    QL_FLASH_PROTECT_ALL,
    QL_FLASH_PROTECT_HALF,
    QL_FLASH_UNPROTECT_LAST_BLOCK,
} ql_flash_protect_type_e;

typedef enum
{
    QL_PARTITION_BOOTLOADER = 0,
    QL_PARTITION_APPLICATION,
    QL_PARTITION_OTA,
    QL_PARTITION_RF_FIRMWARE,
    QL_PARTITION_NET_PARAM,
    QL_PARTITION_FAST_CONNECT,
    QL_PARTITION_SN_CONFIG,
#ifdef QL_CSDK_SUPPORT
#if (QL_CSDK_MODE == 2)
    QL_PARTITION_CUSTOM_APP,
    QL_PARTITION_FS,
#else
    QL_PARTITION_FS,
	QL_PARTITION_EASY_FLASH,
	QL_PARTITION_BLE_BONDING_FLASH,
#endif
#endif
    QL_PARTITION_USR_RESERVE,
    QL_PARTITION_MAX,
} ql_partition_e;


typedef enum{
    QL_FLASH_EMBEDDED = 0,
    QL_FLASH_SPI,
    QL_FLASH_MAX,
    QL_FLASH_NONE
}ql_flash_type_e;

typedef struct{
    ql_flash_type_e partition_owner;
    const char* partition_description;
    uint32_t partition_start_addr;
    uint32_t partition_length;
    uint32_t partition_options;
}ql_logic_partition_info_t;


extern ql_flash_errcode_e ql_flash_security(ql_flash_protect_type_e type);

extern ql_flash_errcode_e ql_flash_write_bytes(const uint8_t *data, uint32_t addr, uint32_t size);

extern ql_flash_errcode_e ql_flash_read_bytes(uint8_t *data, uint32_t addr, uint32_t size);

extern ql_flash_errcode_e ql_flash_erase(uint32_t addr, uint32_t size);

extern ql_flash_errcode_e ql_flash_partition_erase(ql_partition_e inPartition, uint32_t off_set, uint32_t size);

extern ql_flash_errcode_e ql_flash_partition_write( ql_partition_e inPartition, volatile uint32_t off_set, uint8_t *inBuffer , uint32_t inBufferLength);

extern ql_flash_errcode_e ql_flash_partition_read( ql_partition_e inPartition, volatile uint32_t off_set, uint8_t *outBuffer, uint32_t inBufferLength);


extern ql_logic_partition_info_t *ql_flash_partition_get_info(ql_partition_e partition);


#endif 


