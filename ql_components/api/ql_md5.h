/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef  QL_MD5_H
#define   QL_MD5_H


typedef UINT8    md5_byte_t; /* 8-bit byte */
typedef UINT32  md5_word_t; /* 32-bit word */

typedef struct md5_context{
		md5_word_t total[2];          /*!< number of bytes processed  */
		md5_word_t state[4];          /*!< intermediate digest state  */
		md5_byte_t buffer[64];   /*!< data block being processed */
}md5_context;

extern void   ql_md5_init( md5_context *ctx );

extern INT32  ql_md5_starts( md5_context *ctx );

extern INT32  ql_md5_update( md5_context *ctx, const UINT8 *input, size_t ilen );

extern INT32  ql_md5_finish( md5_context *ctx, UINT8 output[16] );

extern INT32  ql_md5_string( const UINT8 *input, size_t ilen, UINT8 output[16] );

#endif//QL_MD5_H

