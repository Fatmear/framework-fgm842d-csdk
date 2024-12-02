#include "ql_type.h"
#include "rtos_pub.h"
#include "uart_pub.h"


#include "ql_debug.h"
#include "ql_osi.h"
#include "ql_pwm.h"

#define ql_pwm_log     os_printf

#define  PWM_TEST_CHANNEL   QL_PWM_0
#define  PWM_TEST_PERIOD    26000
#define  PWM_TEST_DUTY      13000

/***************pwm test******************/

void ql_pwm_demo_thread(void *param)
{
	int ret;

	ql_rtos_task_sleep_ms(3000);

	ret = ql_pwm_init(PWM_TEST_CHANNEL,PWM_TEST_PERIOD,PWM_TEST_DUTY,QL_PWM_INIT_LEVEL_LOW);
	if(ret == QL_PWM_SUCCESS)
		ql_pwm_log("pwm init success\r\n");
	else
	{
	 ql_pwm_log("pwm init fail\r\n");
	 goto pwm_test_exit;
	}

	ql_pwm_enable(PWM_TEST_CHANNEL);

	ql_rtos_task_sleep_ms(3000);

	ql_pwm_update_param(PWM_TEST_CHANNEL, PWM_TEST_PERIOD/2, PWM_TEST_DUTY/2);

	ql_rtos_task_sleep_ms(3000);

	ql_pwm_disable(PWM_TEST_CHANNEL);

	ql_pwm_log("pwm  test over \r\n");

pwm_test_exit:

	while(1)
	{
	 ql_rtos_task_sleep_ms(1000);
	}
	
}

ql_task_t	pwm_test_thread_handle = NULL;
void ql_pwm_demo_thread_creat(void)
{
    int ret;
	ret = ql_rtos_task_create(&pwm_test_thread_handle,
	                	(unsigned short)2048,
					   THD_EXTENDED_APP_PRIORITY,
					   "pwm_test",
					   ql_pwm_demo_thread,  
					   0);


	  if (ret != kNoErr) {
		ql_pwm_log("Error: Failed to create pwm test thread: %d\r\n",ret);
		goto init_err;
	  }
   
	  return;
   
	  init_err:
	   if( pwm_test_thread_handle != NULL ) {
		   ql_rtos_task_delete(pwm_test_thread_handle);
	   }

}

