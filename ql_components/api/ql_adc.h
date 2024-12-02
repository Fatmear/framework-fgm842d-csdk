/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef _QL_ADC_H
#define _QL_ADC_H

#include "ql_api_common.h"


typedef void (*ql_adc_obj_callback)(int new_mv, void *user_data);

#define QL_ADC_MAX_CHANNEL   4

typedef enum
{
	 QL_ADC_SUCCESS = 0,
	 QL_ADC_EXECUTE_ERR=1| (QL_COMPONENT_BSP_ADC << 16),
	 QL_ADC_INVALID_PARAM_ERR,
} ql_adc_errcode_e;


typedef enum
{
	QL_ADC_CHANNEL_1=1,
	QL_ADC_CHANNEL_2,
	QL_ADC_CHANNEL_3,
	QL_ADC_CHANNEL_4,
}ql_adc_channel_e;



typedef struct adc_obj_ {
	void *user_data;
    ql_adc_channel_e channel;
	ql_adc_obj_callback cb;
	struct adc_obj_ *next;
}ql_adc_obj_s;



extern ql_adc_errcode_e ql_adc_init(void);

extern ql_adc_errcode_e ql_adc_deinit(void);

extern ql_adc_errcode_e ql_adc_start(ql_adc_channel_e chan);

extern ql_adc_errcode_e ql_adc_stop(ql_adc_channel_e chan);

extern ql_adc_errcode_e ql_adc_read(ql_adc_channel_e chan, uint16_t *data, uint32_t timeout);


#endif 

