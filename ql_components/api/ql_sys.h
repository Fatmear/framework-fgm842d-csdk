
/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef _QL_SYS_H_
#define _QL_SYS_H_

#include "ql_api_common.h"

typedef enum {
    QL_SYS_SUCCESS = 0,
    QL_SYS_EXECUTE_ERR=100| (QL_COMPONENT_OSI << 16),
    QL_SYS_INVALID_PARAM_ERR,
} ql_sys_errcode_e;

extern ql_sys_errcode_e ql_sys_reboot(void);


extern uint32 ql_sys_show_mem(void);

#endif









































