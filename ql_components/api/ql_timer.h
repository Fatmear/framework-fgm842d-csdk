
/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef _QL_TIMER_H_
#define _QL_TIMER_H_

#include "ql_api_common.h"

typedef enum{
	QL_TIMER_0 =0,
	QL_TIMER_1,
	QL_TIMER_2,
	QL_TIMER_3,
	QL_TIMER_4,
	QL_TIMER_5,
}ql_timer_number_e;

typedef enum
{
	QL_TIMER_SUCCESS = 0,
	QL_TIMER_EXECUTE_ERR=1| (QL_COMPONENT_BSP_TIMER << 16),
	QL_TIMER_INVALID_PARAM_ERR,
	QL_TIMER_NOT_OPEN_ERR,
	QL_TIMER_NOT_SUPPORT_ERR
}ql_timer_errcode_e;




typedef void (*ql_timer_callback)(uint8_t arg);



extern ql_timer_errcode_e ql_TimerInit(ql_timer_number_e timer_id, uint32 time_ms, ql_timer_callback timer_cb);

extern ql_timer_errcode_e ql_TimerInit_us(ql_timer_number_e timer_id, uint32 time_us, ql_timer_callback timer_cb);

extern ql_timer_errcode_e ql_get_timer_cnt(ql_timer_number_e timer_id, uint32 *cont);

extern ql_timer_errcode_e ql_TimerStop(ql_timer_number_e timer_id);

extern ql_timer_errcode_e ql_TimerStart(ql_timer_number_e timer_id);

extern ql_timer_errcode_e ql_timer_delete(ql_timer_number_e timer_id);


#endif 


























