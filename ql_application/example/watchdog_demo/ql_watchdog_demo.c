#include "ql_type.h"
#include "rtos_pub.h"
#include "uart_pub.h"

#include "ql_debug.h"
#include "ql_osi.h"
#include "ql_watchdog.h"

#define ql_watchdog_log os_printf

/***************wdg test******************/
void ql_wdg_demo_thread(void *param)
{

	ql_wdg_init(2000);


	while(1)
	{
	    ql_wdg_reload();
		ql_watchdog_log("wdg feed\r\n");
		ql_rtos_task_sleep_ms(1000);
	}

}

ql_task_t	wdg_test_thread_handle = NULL;
void ql_wdg_demo_thread_create(void)
{
    int ret;
	ret = ql_rtos_task_create(&wdg_test_thread_handle,
		               (unsigned short)1024,
					   THD_EXTENDED_APP_PRIORITY,
					   "wdg_test",
					   ql_wdg_demo_thread,
					   0);


	  if (ret != kNoErr) {
		ql_watchdog_log("Error: Failed to create wdg test thread: %d\r\n",ret);
		goto init_err;
	  }
   
	  return;
   
	  init_err:
	   if( wdg_test_thread_handle != NULL ) {
		   ql_rtos_task_delete(wdg_test_thread_handle);
	   }

}
