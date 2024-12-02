#include "ql_type.h"
#include "rtos_pub.h"
#include "uart_pub.h"
#include "mem_pub.h"

#include "ql_debug.h"
#include "ql_osi.h"
#include "ql_spi_flash.h"

#define ql_spi_flash_log               os_printf

#define SPI_TEST_FLASH_LEN  1024
#define SPI_TEST_FLASH_ADDR  0



/***************spi_flash test******************/

void ql_spi_flash_demo_thread(void *param)
{
	int i,ret = 0;
    UINT8 *buf;
	ql_spi_flash_enable(1);//使能flash，避免误操作
	ql_rtos_task_sleep_ms(3000);

	ql_spi_flash_log("spi flash read id \r\n");
	ql_spi_flash_info_t f_info;
	ql_spi_flash_get_info(&f_info);
	ql_spi_flash_log("f_info:block_size :%d byte\r\n",f_info.block_size);
	ql_spi_flash_log("f_info:capacity   :%d MB\r\n",f_info.capacity);
	ql_spi_flash_log("f_info:driver_type:%d\r\n",f_info.driver_type);
	ql_spi_flash_log("f_info:id         :%06x \r\n",f_info.id);
	ql_spi_flash_log("f_info:page_size  :%d byte\r\n",f_info.page_size);
	ql_spi_flash_log("f_info:sector_size:%d byte\r\n",f_info.sector_size);
	ql_spi_flash_log("f_info:type_name  :%s \r\n",f_info.type_name);

	buf = os_malloc(SPI_TEST_FLASH_LEN * sizeof(UINT8));
	if(buf == 0)
	{
		ql_spi_flash_log("buf malloc failed\r\n");
		goto spi_flash_test_exit;
	}
	os_memset(buf,0,SPI_TEST_FLASH_LEN);

	for(i=0;i<SPI_TEST_FLASH_LEN;i++)
		buf[i] = i%255;

	ql_spi_flash_log("spi flash write start\r\n");
	for (int i = 0; i < SPI_TEST_FLASH_LEN; i++) {
	  ql_spi_flash_log("%02x,", buf[i]);
	  if ((i + 1) % 32 == 0)
		  ql_spi_flash_log("\r\n");
    }
	ret  = ql_spi_flash_write(SPI_TEST_FLASH_ADDR,buf, SPI_TEST_FLASH_LEN);
	if (ret == QL_SPI_FLASH_SUCCESS)
	  ql_spi_flash_log("\r\nspi flash write success\r\n");
	else
	  ql_spi_flash_log("\r\nspi flash write fail \r\n");


	os_memset(buf,0,SPI_TEST_FLASH_LEN);
	ql_spi_flash_log("spi flash read start\r\n");
	ret =  ql_spi_flash_read( SPI_TEST_FLASH_ADDR,buf, SPI_TEST_FLASH_LEN);
	if (ret == QL_SPI_FLASH_SUCCESS)
		{
		  for (int i = 0; i < SPI_TEST_FLASH_LEN; i++) {
			  ql_spi_flash_log("%02x,", buf[i]);
			  if ((i + 1) % 32 == 0)
				  ql_spi_flash_log("\r\n");
		   }
		  ql_spi_flash_log("\r\nspi flash read success\r\n");

		}
	else
	  ql_spi_flash_log("spi flash read fail \r\n");

	ql_spi_flash_log("spi flash erase start\r\n");
	ret = ql_spi_flash_erase(SPI_TEST_FLASH_ADDR,ERASE_SECTOR);
	if (ret == QL_SPI_FLASH_SUCCESS)
	  ql_spi_flash_log("spi flash erase success\r\n");
	else
	  ql_spi_flash_log("spi flash erase fail\r\n \r\n");
	os_memset(buf,0,SPI_TEST_FLASH_LEN);
	ret =  ql_spi_flash_read(SPI_TEST_FLASH_ADDR,buf,512);
		if (ret == QL_SPI_FLASH_SUCCESS)
			{
			  ql_spi_flash_log("spi flash read success\r\n");
			  for (int i = 0; i < 512; i++) {
				  ql_spi_flash_log("%02x,", buf[i]);
				  if ((i + 1) % 32 == 0)
					  ql_spi_flash_log("\r\n");
			   }

			}
		else
		  ql_spi_flash_log("spi flash read fail\r\n \r\n");

	ret = ql_spi_flash_erase(SPI_TEST_FLASH_ADDR,ERASE_BLOCK);
	if (ret == QL_SPI_FLASH_SUCCESS)
	  ql_spi_flash_log("spi flash erase success\r\n");
	else
	  ql_spi_flash_log("spi flash erase fail\r\n \r\n");
	ret =  ql_spi_flash_read( SPI_TEST_FLASH_ADDR,buf, SPI_TEST_FLASH_LEN);
		if (ret == QL_SPI_FLASH_SUCCESS)
			{
			  ql_spi_flash_log("spi flash read success\r\n");
			  for (int i = 0; i < SPI_TEST_FLASH_LEN; i++) {
				  ql_spi_flash_log("%02x,", buf[i]);
				  if ((i + 1) % 32 == 0)
					  ql_spi_flash_log("\r\n");
			   }

			}
		else
		  ql_spi_flash_log("spi flash read fail\r\n \r\n");
	ret = ql_spi_flash_erase(0,ERASE_ALL);
	if (ret == QL_SPI_FLASH_SUCCESS)
	  ql_spi_flash_log("spi flash erase success\r\n");
	else
	  ql_spi_flash_log("spi flash erase fail\r\n \r\n");

	os_memset(buf,0,SPI_TEST_FLASH_LEN);
	ret =  ql_spi_flash_read(SPI_TEST_FLASH_ADDR,buf, SPI_TEST_FLASH_LEN);
		if (ret == QL_SPI_FLASH_SUCCESS)
			{
			  ql_spi_flash_log("spi flash read success\r\n");
			  for (int i = 0; i < SPI_TEST_FLASH_LEN; i++) {
				  ql_spi_flash_log("%02x,", buf[i]);
				  if ((i + 1) % 32 == 0)
					  ql_spi_flash_log("\r\n");
			   }

			}
		else
		  ql_spi_flash_log("spi flash read fail\r\n \r\n");

	ql_spi_flash_log("\r\n spi flash test over \r\n");

spi_flash_test_exit:

	os_free(buf);
		ql_spi_flash_enable(0);	
	while(1)
	{
	  ql_rtos_task_sleep_ms(1000);
	}

}

ql_task_t	spi_flash_test_thread_handle = NULL;
void ql_spi_flash_demo_thread_creat(void)
{
    int ret;
	ret = ql_rtos_task_create(&spi_flash_test_thread_handle,
		               (unsigned short)4096,
					   THD_EXTENDED_APP_PRIORITY,
					   "spi_flash_test",
					   ql_spi_flash_demo_thread,
					   0);


	  if (ret != kNoErr) {
		os_printf("Error: Failed to create spi flash test thread: %d\r\n",ret);
		goto init_err;
	  }
   
	  return;
   
	  init_err:
	   if( spi_flash_test_thread_handle != NULL ) {
		   ql_rtos_task_delete(spi_flash_test_thread_handle);
	   }

}

