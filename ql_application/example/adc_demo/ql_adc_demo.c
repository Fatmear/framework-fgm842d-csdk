
/**  @file
  ql_adc_demo.c

  @brief
  TODO

*/

/*================================================================
  Copyright (c) 2022 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
=================================================================*/
/*=================================================================

						EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

WHEN              WHO         WHAT, WHERE, WHY
------------     -------     -------------------------------------------------------------------------------

=================================================================*/
#include "ql_type.h"
#include "rtos_pub.h"
#include "uart_pub.h"

#include "ql_debug.h"
#include "ql_osi.h"
#include "ql_adc.h"

#define ADC_TEST_DEBUG

#ifdef ADC_TEST_DEBUG
#define ql_adc_log               os_printf
#else
#define ql_adc_log               
#endif

/***************adc test******************/
ql_task_t	adc_test_thread_handle = NULL;

void ql_adc_demo_thread(void *param)
{
	uint16_t data = 0;
	int ret = 0;
	
	ql_rtos_task_sleep_ms(3000);
    ql_adc_log("adc test start\r\n");
	ql_adc_init();
	
	ql_rtos_task_sleep_ms(10);
	ql_adc_start(QL_ADC_CHANNEL_3);
	ql_adc_start(QL_ADC_CHANNEL_4);

	while (1)
	{
		ret = ql_adc_read(QL_ADC_CHANNEL_3, &data, 1000);

		if(ret == 0)
			ql_adc_log("channel3 voltage is %d mV\r\n",data);
		else
			ql_adc_log("channel3 read err\r\n");
		ql_adc_read(QL_ADC_CHANNEL_4, &data, 1000);
		
		ql_adc_log("channel4 voltage is %d mV\r\n",data);
		ql_rtos_task_sleep_ms(1000);
	}

}


void ql_adc_demo_thread_creat(void)
{
	int ret = 0;
	
	ret = ql_rtos_task_create(&adc_test_thread_handle,
				   (unsigned short)2048,
				   THD_EXTENDED_APP_PRIORITY,
				   "adc_test",
				   ql_adc_demo_thread,   
				   0);


	if (ret != kNoErr) {
		ql_adc_log("Error: Failed to create adc test thread: %d\r\n",ret);
	}
}

