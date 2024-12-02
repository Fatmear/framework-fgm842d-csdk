/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef  QL_ERROR_H
#define   QL_ERROR_H


typedef enum
{
	QL_NO_ERROR = 0,
	QL_SUCCESS = 0,
	QL_INVALID_PARAM_ERR,
	QL_READ_NVM_ERR,
	QL_STORAGE_NVM_ERR,
	
	
	QL_GENERAL_ERROR  = 0xFFFF,
} ql_errcode_e;

#endif//QL_ERROR_H
