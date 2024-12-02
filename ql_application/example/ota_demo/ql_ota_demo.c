#include "ql_type.h"
#include "rtos_pub.h"
#include "uart_pub.h"
#include "mem_pub.h"

#include "ql_debug.h"
#include "ql_osi.h"
#include "ql_wlan.h"

#define OTA_URI "http://192.168.1.100/fcm242d.rbl"

#define ql_ota_log     os_printf



/***************ota test******************/
ql_task_t	ota_test_thread_handle = NULL;	
void ql_ota_demo_thread(void *param)
{
    ql_ota_log("ota test start!\r\n");
	int ret=-1;
	//wait for connect wifi
	ql_ota_log("!!!!!!!!!!!wait wifi connect \r\n");
	while (!ql_sta_ip_is_start())
	{
		ql_rtos_task_sleep_ms(1000);
		ql_ota_log("connecting \r\n");
	}
    ret = ql_wlan_ota_download(OTA_URI);//PORT 80	
	if(ret!=0)
	{
		ql_ota_log("ota failed ret:%d \r\n",ret);
	}
	
}


void ql_ota_demo_thread_creat(void)
{
    int ret;
	ret = ql_rtos_task_create(&ota_test_thread_handle,
	                   (unsigned short)1024*5,
					   THD_EXTENDED_APP_PRIORITY,
					   "ota_test",
					   ql_ota_demo_thread,
					   0);


	  if (ret != kNoErr) {
		os_printf("Error: Failed to create ota test thread: %d\r\n",ret);
		goto init_err;
	  }
   
	  return;
   
	  init_err:
	   if( ota_test_thread_handle!= NULL ) {
		   ql_rtos_task_delete(ota_test_thread_handle);
	   }

}
