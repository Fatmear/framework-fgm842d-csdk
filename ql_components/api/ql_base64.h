/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef QL_BASE64_H
#define  QL_BASE64_H


extern  UINT32  ql_base64_calc_encode_length( const char *in, UINT32 in_len );
typedef UINT32 (*_api_ql_base64_calc_encode_length_cb_t)( const char *in, UINT32 in_len );

extern UINT32  ql_base64_encode(const UINT8 *indata, INT32  inlen, INT32 *outlen, UINT8 *outdata);
typedef UINT32 (*_api_ql_base64_encode_cb_t)(const UINT8 *indata, INT32  inlen, INT32 *outlen, UINT8 *outdata);

extern UINT32  ql_base64_calc_decode_length(const UINT8 *src,  UINT32 src_Len);
typedef UINT32 (*_api_ql_base64_calc_decode_length_cb_t)(const UINT8 *src,  UINT32 src_Len);

extern  UINT32  ql_base64_decode(const UINT8 *indata, INT32  inlen, INT32 *outlen, UINT8 *outdata);
typedef UINT32  (*_api_ql_base64_decode_cb_t)(const UINT8 *indata, INT32  inlen, INT32 *outlen, UINT8 *outdata);
 
#endif//QL_BASE64_H
