/**  
  @file
  ql_api_common.h

  @brief
  quectel common definition.

*/
/*================================================================
  Copyright (c) 2020 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
=================================================================*/
/*=================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN              WHO         WHAT, WHERE, WHY
------------     -------     -------------------------------------------------------------------------------

=================================================================*/

#ifndef QL_API_COMMON_H
#define QL_API_COMMON_H
#include "ql_type.h"

#ifdef __cplusplus
extern "C" {
#endif


/*========================================================================
 *  Macro Definition
 *========================================================================*/

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef CHAR
typedef char     CHAR;
#endif

/*========================================================================
 *	Enumeration Definition
 *========================================================================*/
typedef enum
{
	QL_COMPONENT_NONE		                 = 0,
	    
	QL_COMPONENT_OSI			         = 0x8100,
	
	QL_COMPONENT_BSP			         = 0x8200,
	QL_COMPONENT_BSP_GPIO		                 = 0x8201,
	QL_COMPONENT_BSP_PWM		                 = 0x8202,
	QL_COMPONENT_BSP_SPI		                 = 0x8203,
	QL_COMPONENT_BSP_I2C		                 = 0x8204,
	//QL_COMPONENT_BSP_KEY		                 = 0x8205,
	QL_COMPONENT_BSP_UART		                 = 0x8206,
	QL_COMPONENT_BSP_USB		                 = 0x8207,
	QL_COMPONENT_BSP_CMUX		                 = 0x8208,
	QL_COMPONENT_BSP_LCD		                 = 0x8209,
	QL_COMPONENT_BSP_CAMERA 	                 = 0x820A,
	QL_COMPONENT_BSP_BT 		                 = 0x820B,
	QL_COMPONENT_BSP_GNSS		                 = 0x820C,
	QL_COMPONENT_BSP_WIFISCAN	                 = 0x820D,
	QL_COMPONENT_BSP_ADC		                 = 0x820E,
	QL_COMPONENT_BSP_LED		                 = 0x820F,
	QL_COMPONENT_BSP_DECODER	                 = 0x8210,
	QL_COMPONENT_BSP_KEYPAD 	                 = 0x8211,
	QL_COMPONENT_BSP_RTC		                 = 0x8212,
	QL_COMPONENT_BSP_LVGL		                 = 0x8213,
	QL_COMPONENT_BSP_CHARGE 	                 = 0x8214,
	QL_COMPONENT_BSP_VIRT_AT	                 = 0x8215,
	QL_COMPONENT_BSP_TIMER	                     = 0x8216,	
	QL_COMPONENT_BSP_WATCHDOG	                     = 0x8217,
	QL_COMPONENT_BSP_OTHER	                         = 0x82FF,
	
	QL_COMPONENT_STORAGE				 = 0x8300,
	QL_COMPONENT_STORAGE_FLASH			 = 0x8301,
	QL_COMPONENT_STORAGE_SDEMMC 		         = 0x8302,
	QL_COMPONENT_STORAGE_FILE			 = 0x8303,
	QL_COMPONENT_STORAGE_EXTFLASH		         = 0x8304,  //for nor flash
	QL_COMPONENT_STORAGE_EXT_NANDFLASH	         = 0x8305,  //for nand flash
	QL_COMPONENT_STORAGE_ZIP			 = 0x8306,
	QL_COMPONENT_STORAGE_FATFS			 = 0x8307,  //for fatfs
	QL_COMPONENT_STORAGE_EMBED_NOR_FLASH             = 0x8308,  //for embed flash
	QL_COMPONENT_STORAGE_QCFG			 = 0x8309,  //quec_cfg
	
	QL_COMPONENT_AUDIO			         = 0x8400,
	QL_COMPONENT_AUDIO_CODEC	                 = 0x8401,
	QL_COMPONENT_AUDIO_REC_PLAY                      = 0x8402,
	QL_COMPONENT_AUDIO_TTS		                 = 0x8403,
	QL_COMPONENT_AUDIO_DTMF 	                 = 0x8404,
	QL_COMPONENT_AUDIO_SETTING	                 = 0x8405,
	QL_COMPONENT_AUDIO_HEADSET	                 = 0x8406,
	
	QL_COMPONENT_LWIP			         = 0x8500,
	QL_COMPONENT_LWIP_SOCKET	                 = 0x8501, // tcp/udp/ping/dns
	QL_COMPONENT_LWIP_HTTP		                 = 0x8502,
	QL_COMPONENT_LWIP_MQTT		                 = 0x8503,
	QL_COMPONENT_LWIP_FTP		                 = 0x8504,
	QL_COMPONENT_LWIP_SSL		                 = 0x8505,
	QL_COMPONENT_LWIP_MMS		                 = 0x8506,
	QL_COMPONENT_LWIP_LBS		                 = 0x8507, // queclocator
	QL_COMPONENT_LWIP_QUECTHING                      = 0x8508,
	QL_COMPONENT_LWIP_QNTP		                 = 0x8509,
	QL_COMPONENT_LWIP_SMTP		                 = 0x8510,
	
	QL_COMPONENT_NETWORK		                 = 0x8600,
	QL_COMPONENT_NETWORK_MANAGE                      = 0x8601,
	QL_COMPONENT_NETWORK_PPP	                 = 0x8602,
	QL_COMPONENT_NETWORK_USBNET                      = 0x8603,	
	QL_COMPONENT_STATE_INFO 	                 = 0x8700, // basic info and state for quectel product itself
	
	QL_COMPONENT_LOG			         = 0x8800,
	


	//
	//next is reserved for app to add component
	//
	QL_COMPONENT_APP_START		                 = 0x9F00,// app component start
	
	QL_COMPONENT_MAX			         = 0x9FFF,//component end
}ql_component_e;


/*
*						errcode definition
*
* 4 bytes, little endian, signed type, as below:
*
*		----------------------------------------------------------------------------------------------------
*		|			 4				|			  3 		   |		  2 		  | 		1		   |
*		----------------------------------------------------------------------------------------------------
*		| High byte of component ID | low byte of component ID | High byte of errcode | low byte of errcode|
*		----------------------------------------------------------------------------------------------------
*
* component ID defined at enum type <ql_errcode_component_e>.
* detail errcode defined by each component.
*
*/
//common detail errcode, 2 bytes
typedef enum
{
    QL_NO_ERROR = 0,
    QL_SUCCESS = 0,
    QL_INVALID_PARAM_ERR,
    QL_READ_NVM_ERR,
    QL_STORAGE_NVM_ERR,
	
	
    QL_GENERAL_ERROR  = 0xFFFF,
} ql_errcode_e;

/*========================================================================
 *  Variable Definition
 *========================================================================*/
#define CHIP_SECTOR_SIZE 		  (0x1000)    	//erase 4k each times
#define CHIP_BLOCK_SIZE 		  (0x10000)    	//erase 64k each times


/*========================================================================
 *  function Definition
 *========================================================================*/
typedef void (*ql_callback)(void *ctx);

/*
uint32_t ql_get_free_heap_size(void);
uint32_t ql_get_total_heap_size(void);
uint32_t ql_flash_erase(uint32_t SectorAddress, uint32_t size);
uint32_t ql_flash_read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size);
uint32_t ql_flash_write(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
*/
#ifdef __cplusplus
} /*"C" */
#endif

#endif /* QL_API_COMMON_H */

