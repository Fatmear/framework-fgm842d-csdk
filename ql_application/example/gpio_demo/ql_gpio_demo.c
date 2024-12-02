
#include "ql_type.h"
#include "rtos_pub.h"
#include "uart_pub.h"


#include "ql_debug.h"
#include "ql_osi.h"
#include "ql_gpio.h"
#define ql_gpio_log     os_printf

/***************gpio test******************/
static void gpio_init_test_callback( void *arg)
{
	ql_gpio_errcode_e ret;
	ql_gpio_log("gpio int test\r\n");
	ret = ql_gpio_set_level_reverse(QL_GPIO21);
	   if(ret == QL_GPIO_SUCCESS)
	  ql_gpio_log("gpio reverse success\r\n");
	else
	  ql_gpio_log("gpio reverse fail\r\n");
}

void ql_gpio_demo_thread(void *param)
{
	ql_gpio_errcode_e ret;
	ql_rtos_task_sleep_ms(2000);
	ql_gpio_log("gpio  test start \r\n");
	ret = ql_gpio_init(QL_GPIO21,QL_GMODE_OUTPUT,QL_GPIO_LEVEL_LOW);
    if(ret == QL_GPIO_SUCCESS)
	  ql_gpio_log("gpio init success\r\n");
	else
	  ql_gpio_log("gpio init fail\r\n");
	ql_gpio_set_level(QL_GPIO21,QL_GPIO_LEVEL_HIGH);
	ql_rtos_task_sleep_ms(2000);
	ql_gpio_set_level(QL_GPIO21,QL_GPIO_LEVEL_LOW);

	ql_gpio_int_init(QL_GPIO22,QL_IRQ_TRIGGER_RISING_EDGE,gpio_init_test_callback);
	while(1)
	{
	  ql_rtos_task_sleep_ms(1000);
	}
	
}

ql_task_t	gpio_test_thread_handle = NULL;
void ql_gpio_demo_thread_creat(void)
{
    int ret;
	ret = ql_rtos_task_create(&gpio_test_thread_handle,
		               (unsigned short)2048,
					   THD_EXTENDED_APP_PRIORITY,
					   "gpio_test",
					   ql_gpio_demo_thread,	   
					   0);


	  if (ret != kNoErr) {
		os_printf("Error: Failed to create gpio test thread: %d\r\n",ret);
		goto init_err;
	  }
   
	  return;
   
	  init_err:
	   if( gpio_test_thread_handle != NULL ) {
		   ql_rtos_task_delete(gpio_test_thread_handle);
	   }

}

