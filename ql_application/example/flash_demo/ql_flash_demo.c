#include "ql_type.h"
#include "rtos_pub.h"
#include "mem_pub.h"
#include "uart_pub.h"

#include "ql_debug.h"
#include "ql_osi.h"
#include "ql_flash.h"
#include "BkDriverFlash.h"


#define FLASH_TEST_DEBUG

#ifdef FLASH_TEST_DEBUG
#define ql_flash_log               os_printf
#else
#define ql_flash_log               
#endif

#define TEST_FLASH_LEN   256
#define TEST_FLASH_ADDR  0x1f8000

/***************flash test******************/
#if 0
void ql_flash_demo_thread(void *param)
{
	int i = 0,ret = 0;
    UINT8 *buf = NULL;
	
	ql_rtos_task_sleep_ms(3000);
		
	buf = os_malloc(TEST_FLASH_LEN);
	if(buf == NULL){
		ql_flash_log("buf malloc failed\r\n");
		goto flash_test_exit;
	}
	os_memset(buf,0,TEST_FLASH_LEN);
	
	for(i = 0; i < TEST_FLASH_LEN; i++){
		buf[i] = i%255;
	}
	
	ql_flash_log(" flash write start\r\n");
	for (i = 0; i < TEST_FLASH_LEN; i++){
		ql_flash_log("%02x,", buf[i]);
		if ((i + 1) % 32 == 0){
			ql_flash_log("\r\n");
		}
    }
	
	ql_flash_security(QL_FLASH_PROTECT_NONE);
	ret  = ql_flash_write_bytes(buf, TEST_FLASH_ADDR, TEST_FLASH_LEN);
	if (ret == QL_FLASH_SUCCESS){
		ql_flash_log("\r\nflash write success\r\n");
	}else{
		ql_flash_log("\r\nflash write fail \r\n");
	}
	ql_flash_security(QL_FLASH_UNPROTECT_LAST_BLOCK);

	os_memset(buf,0,TEST_FLASH_LEN);
	ql_flash_log("spi flash read start\r\n");
	ret =  ql_flash_read_bytes( buf, TEST_FLASH_ADDR, TEST_FLASH_LEN);
	
	if (ret == QL_FLASH_SUCCESS){
		for (i = 0; i < TEST_FLASH_LEN; i++){
			ql_flash_log("%02x,", buf[i]);
			if ((i + 1) % 32 == 0){
				ql_flash_log("\r\n");
			}
		}
		ql_flash_log("\r\nflash read success\r\n");
	}else{
		ql_flash_log("flash read fail \r\n");
	}
	
	ql_flash_log("flash erase start\r\n");
	ql_flash_security(QL_FLASH_PROTECT_NONE);
	ret = ql_flash_erase(TEST_FLASH_ADDR,TEST_FLASH_LEN);
	if (ret == QL_FLASH_SUCCESS){
		ql_flash_log("flash erase success\r\n");
	}else{
		ql_flash_log("flash erase fail\r\n \r\n");
	}

	ql_flash_security(QL_FLASH_UNPROTECT_LAST_BLOCK);

	os_memset(buf,0,TEST_FLASH_LEN);
	ret =  ql_flash_read_bytes(buf, TEST_FLASH_ADDR, TEST_FLASH_LEN);
	if (ret == QL_FLASH_SUCCESS){
		ql_flash_log("flash read success\r\n");
		for (int i = 0; i < TEST_FLASH_LEN; i++){
			ql_flash_log("%02x,", buf[i]);
			if ((i + 1) % 32 == 0){
				ql_flash_log("\r\n");
			}
		}
	}else{
		ql_flash_log("flash read fail\r\n \r\n");
	}
	
	ql_flash_log("\r\nflash test over \r\n");
	
flash_test_exit:

	os_free(buf);	
	
	while(1){
		ql_rtos_task_sleep_ms(1000);
	}
	
}
#else

/***************flash_parttion test******************/

void ql_flash_demo_thread(void *param)
{
	int i = 0,ret = 0;
	UINT8 *buf = NULL;
	
	ql_rtos_task_sleep_ms(3000);

	ql_logic_partition_info_t *info;
	info = ql_flash_partition_get_info(QL_PARTITION_USR_RESERVE);
	ql_flash_log("flash_info:partition_owner      :   %d   \r\n",info->partition_owner);
	ql_flash_log("flash_info:partition_description:   %s \r\n",info->partition_description);
	ql_flash_log("flash_info:partition_start_addr :   0x%x \r\n",info->partition_start_addr);
	ql_flash_log("flash_info:partition_length     :   0x%x  \r\n",info->partition_length);
	ql_flash_log("flash_info:partition_options    :   0x%x  \r\n",info->partition_options);
		
	buf = os_malloc(TEST_FLASH_LEN);
	
	if(buf == NULL){
		ql_flash_log("buf malloc failed\r\n");
		goto flash_test_exit;
	}
	os_memset(buf,0,TEST_FLASH_LEN);

	for(i = 0; i < TEST_FLASH_LEN; i++){
		buf[i] = i%255;
	}
	
	for (i = 0; i < TEST_FLASH_LEN; i++) {
		ql_flash_log("%02x,", buf[i]);
		if ((i + 1) % 32 == 0){
			ql_flash_log("\r\n");
		}
	}

	ql_flash_security(QL_FLASH_PROTECT_NONE);
		
	ql_flash_log(" flash write start\r\n");
	ret  = ql_flash_partition_write(QL_PARTITION_USR_RESERVE,0,buf,TEST_FLASH_LEN);
	
	if (ret == QL_FLASH_SUCCESS){
		ql_flash_log("\r\nflash write success\r\n");
	}else{
		ql_flash_log("\r\nflash write fail \r\n");
	}
	
	ql_flash_security(QL_FLASH_UNPROTECT_LAST_BLOCK);

	os_memset(buf,0,TEST_FLASH_LEN);
	ql_flash_log("spi flash read start\r\n");
	ret =  ql_flash_partition_read(QL_PARTITION_USR_RESERVE,0,buf,TEST_FLASH_LEN);

	if (ret == QL_FLASH_SUCCESS){
		for (i = 0; i < TEST_FLASH_LEN; i++){
			ql_flash_log("%02x,", buf[i]);
			if ((i + 1) % 32 == 0){
				ql_flash_log("\r\n");
			}
		}
		ql_flash_log("\r\nflash read success\r\n");
	}else{
		ql_flash_log("flash read fail \r\n");
	}

	ql_flash_log("flash erase start\r\n");
	ql_flash_security(QL_FLASH_PROTECT_NONE);
	ret = ql_flash_partition_erase(QL_PARTITION_USR_RESERVE,0,TEST_FLASH_LEN);

	if (ret == QL_FLASH_SUCCESS){
		ql_flash_log("flash erase success\r\n");
	}else{
		ql_flash_log("flash erase fail\r\n \r\n");
	}
	
	ql_flash_security(QL_FLASH_UNPROTECT_LAST_BLOCK);

	os_memset(buf,0,TEST_FLASH_LEN);
	ret = ql_flash_partition_read(QL_PARTITION_USR_RESERVE,0,buf,TEST_FLASH_LEN);
	
	if (ret == QL_FLASH_SUCCESS){
		ql_flash_log("flash read success\r\n");
		for (int i = 0; i < TEST_FLASH_LEN; i++){
			ql_flash_log("%02x,", buf[i]);
			if ((i + 1) % 32 == 0){
				ql_flash_log("\r\n");
			}
		}
	}else{
		ql_flash_log("flash read fail\r\n \r\n");
	}
	ql_flash_log("\r\nflash test over \r\n");
	
flash_test_exit:

	os_free(buf);	
	
	while(1){
		ql_rtos_task_sleep_ms(1000);
	}

}

#endif

ql_task_t	flash_test_thread_handle = NULL;
void ql_flash_demo_thread_creat(void)
{
	int ret = 0;
	ret = ql_rtos_task_create(&flash_test_thread_handle,
	               (unsigned short)4096,
				   THD_EXTENDED_APP_PRIORITY,
				   "flash_test",
				   ql_flash_demo_thread,	   
				   0);


	if (ret != kNoErr) {
		ql_flash_log("Error: Failed to create flash test thread: %d\r\n",ret);
	}

}


