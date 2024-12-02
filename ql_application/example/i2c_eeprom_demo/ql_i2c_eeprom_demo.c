#include "ql_type.h"
#include "rtos_pub.h"
#include "uart_pub.h"


#include "ql_debug.h"
#include "ql_osi.h"
#include "ql_i2c.h"

#define I2C2_TEST_LEGNTH         200
#define I2C2_TEST_SALVE_ID       0x50
#define I2C2_TEST_ADDR           0x00

#define ql_i2c_log     os_printf

/***************i2c test******************/
ql_task_t	i2c_test_thread_handle = NULL;
void ql_i2c2_eeprom_demo_thread(void *param)
{
   uint8 i;
   unsigned char writebuf[I2C2_TEST_LEGNTH] = {0};
   unsigned char readbuf[I2C2_TEST_LEGNTH] = {0};
   uint8 page = 0;
   uint8 remian_bytes = 0;
   uint8 page_i = 0;
   ql_rtos_task_sleep_ms(3000);

   ql_i2c_log("i2c2 write eeprom start \r\n");
   if(I2C2_TEST_LEGNTH > 255)
   {
		ql_i2c_log("I2C2_TEST_LEGNTH is error \r\n");
		ql_rtos_task_delete(i2c_test_thread_handle);
		return;
   }
   for (i = 0; i < I2C2_TEST_LEGNTH; i++)
	{
		writebuf[i] = i ;
		ql_i2c_log("0x%x  ", writebuf[i]);
	}
	remian_bytes = I2C2_TEST_LEGNTH;

	ql_i2c_init(QL_I2C2,QL_I2C_SPEED_FAST,QL_I2C_ADDR_SIZE_7BIT,0x53);

	if(I2C2_TEST_LEGNTH < 8 || I2C2_TEST_LEGNTH == 8)
	{
		ql_i2c_master_mem_write(QL_I2C2,I2C2_TEST_SALVE_ID,I2C2_TEST_ADDR + page_i *8,QL_I2C_MEM_ADDR_SIZE_8BIT,writebuf + 8 * page_i,I2C2_TEST_LEGNTH);
	}
	else if(I2C2_TEST_LEGNTH > 8)
	{

		page = I2C2_TEST_LEGNTH / 8 + 1;
		while(page--)
		{
			if(remian_bytes >8 || remian_bytes == 8)
			{
				ql_i2c_master_mem_write(QL_I2C2,I2C2_TEST_SALVE_ID,I2C2_TEST_ADDR + page_i *8,QL_I2C_MEM_ADDR_SIZE_8BIT,writebuf + 8 * page_i,8);
				page_i++;
				remian_bytes = remian_bytes - 8;
				 ql_rtos_task_sleep_ms(100);
			}
			else
			{
				ql_i2c_master_mem_write(QL_I2C2,I2C2_TEST_SALVE_ID,I2C2_TEST_ADDR + page_i *8,QL_I2C_MEM_ADDR_SIZE_8BIT,writebuf + 8 * page_i,remian_bytes);
			}
		}
	}

   ql_i2c_log("\r\ni2c2 read eeprom start \r\n");
   ql_rtos_task_sleep_ms(100);

   ql_i2c_master_mem_read(QL_I2C2,I2C2_TEST_SALVE_ID,I2C2_TEST_ADDR,QL_I2C_MEM_ADDR_SIZE_8BIT,readbuf,200);

   for (i = 0; i < I2C2_TEST_LEGNTH; i++)
	 ql_i2c_log("0x%x  ", readbuf[i]);

   ql_i2c_log("\r\ni2c2 eeprom test over \r\n");

   ql_i2c_deinit(QL_I2C2);

	while(1)
  	{
      ql_rtos_task_sleep_ms(1000);
	}

}

void ql_i2c_demo_thread_creat(void)
{
    int ret;
	ret = ql_rtos_task_create(&i2c_test_thread_handle,
	            	(unsigned short)2048,
					 THD_EXTENDED_APP_PRIORITY,
					 "i2c2_test",
					 ql_i2c2_eeprom_demo_thread,
					 0);



	 if (ret != kNoErr) {
	   os_printf("Error: Failed to create i2c test thread: %d\r\n",ret);
	   goto init_err;
	 }

     return;

	 init_err:
	  if( i2c_test_thread_handle != NULL ) {
		  ql_rtos_task_delete(i2c_test_thread_handle);
	  }

}

