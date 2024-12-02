/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef QL_EF_H
#define QL_EF_H

#include "ql_type.h"
#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
	QL_EF_OK = 0,
	QL_EF_ERASE_ERR,
	QL_EF_READ_ERR,
	QL_EF_WRITE_ERR,
	QL_EF_ENV_NAME_ERR,
	QL_EF_ENV_NAME_EXIST,
	QL_EF_ENV_FULL,
	QL_EF_ENV_INIT_FAILED,
	QL_EF_ERROR_MAX,
}ql_ef_errcode_e;

ql_ef_errcode_e ql_ef_init(void);

size_t ql_get_env(const char *key, void *value_buf, size_t buf_len, size_t *saved_value_len);

ql_ef_errcode_e ql_set_env(const char *key, const void *value_buf, size_t buf_len);

ql_ef_errcode_e ql_del_env(const char *key);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
