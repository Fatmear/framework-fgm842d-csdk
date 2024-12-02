
/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef     _QL_WATCHDOG_H_
#define     _QL_WATCHDOG_H_

#include "ql_api_common.h"

typedef enum
{
    QL_WDG_SUCCESS      = 0,
    QL_WDG_EXECUTE_ERR=1| (QL_COMPONENT_BSP_WATCHDOG << 16),
    QL_WDG_INVALID_PARAM_ERR,
}ql_wdg_errcode_e;

extern ql_wdg_errcode_e ql_wdg_init(uint32 timeout);

extern ql_wdg_errcode_e ql_wdg_reload(void);

extern ql_wdg_errcode_e ql_wdg_finalize(void);

extern void ql_wdg_demo_thread_create(void);

#endif





















































