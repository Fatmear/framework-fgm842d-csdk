/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef _QL_GPIO_H
#define _QL_GPIO_H

#include "ql_api_common.h"

typedef void (*ql_gpio_irq_callback)( void *arg );


typedef enum
{
         QL_GPIO_SUCCESS = 0,
         QL_GPIO_EXECUTE_ERR,
         QL_GPIO_INVALID_PARAM_ERR,
} ql_gpio_errcode_e;

typedef enum 
{
    QL_GPIO0 = 0,
    QL_GPIO1,
    QL_GPIO6 = 6,
    QL_GPIO7,
    QL_GPIO8,
    QL_GPIO9,
    QL_GPIO10,
    QL_GPIO11,
    QL_GPIO14 = 14,
    QL_GPIO15,
    QL_GPIO16,
    QL_GPIO17,
    QL_GPIO20 = 20,
    QL_GPIO21,
    QL_GPIO22,
    QL_GPIO23,
    QL_GPIO24,
    QL_GPIO26 = 26,
    QL_GPIO28 = 28,   
} ql_gpio_num_e ;

typedef enum{  
    QL_GMODE_HIGH_IMPENDANCE = 0,
    QL_GMODE_INPUT,
    QL_GMODE_IN_PD,
    QL_GMODE_IN_PU,
    QL_GMODE_OUTPUT,
}ql_gpio_mode_e;

typedef enum{
    QL_GPIO_LEVEL_LOW = 0,
    QL_GPIO_LEVEL_HIGH,
}ql_gpio_level_e;

typedef enum
{
    QL_IRQ_TRIGGER_LOW_LEVEL = 0x0,
    QL_IRQ_TRIGGER_HGIH_LEVEL,  
    QL_IRQ_TRIGGER_RISING_EDGE, 
    QL_IRQ_TRIGGER_FALLING_EDGE, 
} ql_gpio_irq_trigger_e;

typedef void (*ql_gpio_irq_callback)( void *arg );

ql_gpio_errcode_e ql_gpio_init(ql_gpio_num_e gpio_num, ql_gpio_mode_e mode, ql_gpio_level_e level);



ql_gpio_errcode_e ql_gpio_deinit(ql_gpio_num_e gpio_num);




ql_gpio_errcode_e ql_gpio_int_init(ql_gpio_num_e gpio_num, ql_gpio_irq_trigger_e irq_trigger, ql_gpio_irq_callback cb);



ql_gpio_errcode_e ql_gpio_int_disable(ql_gpio_num_e gpio_num);



ql_gpio_errcode_e ql_gpio_get_level(ql_gpio_num_e gpio_num,uint32 *input_level);


ql_gpio_errcode_e ql_gpio_set_level_reverse(ql_gpio_num_e gpio_num);


ql_gpio_errcode_e ql_gpio_set_level(ql_gpio_num_e gpio_num, ql_gpio_level_e level);


void ql_gpio_demo_thread_creat(void);

#endif
