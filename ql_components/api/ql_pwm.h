/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef _QL_PWM_H_
#define _QL_PWM_H_

#include "ql_api_common.h"

typedef enum
{
	 QL_PWM_SUCCESS = 0,
	 QL_PWM_EXECUTE_ERR=1| (QL_COMPONENT_BSP_PWM << 16),
	 QL_PWM_INVALID_PARAM_ERR,
} ql_pwm_errcode_e;

typedef enum
{
    QL_PWM_0        = 0,
    QL_PWM_1,
    QL_PWM_2,
    QL_PWM_3,
    QL_PWM_4,
    QL_PWM_5
}ql_pwm_channel_e;

typedef enum
{
    QL_PWM_INIT_LEVEL_LOW   = 0,
    QL_PWM_INIT_LEVEL_HIGH,
}ql_pwm_init_level_e;


extern ql_pwm_errcode_e ql_pwm_init(ql_pwm_channel_e chan, uint32 period, uint32 duty, ql_pwm_init_level_e level);


extern ql_pwm_errcode_e ql_pwm_deinit(ql_pwm_channel_e pwm_channel);

extern ql_pwm_errcode_e ql_pwm_enable(ql_pwm_channel_e pwm_channel);


extern ql_pwm_errcode_e ql_pwm_disable(ql_pwm_channel_e pwm_channel);


extern ql_pwm_errcode_e ql_pwm_update_param(ql_pwm_channel_e pwm_channel, uint32 period, uint32 duty_cycle);

#endif


























