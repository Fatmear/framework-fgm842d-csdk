/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef  QL_UTILS_H
#define  QL_UTILS_H

#define MAX_ITOA_LEN 33 
#define  MIN( x, y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )
#define  UPCASE( c ) ( ((c) >= 'a' && (c) <= 'z') ? ((c) - 0x20) : (c) )

typedef enum{
	QL_IP_INVALID  = -1,
	QL_IP_V4           = 0,
	QL_IP_V6           = 1,
}ip_type_e;

extern INT32 ql_strcmp_ig_sp_case(const UINT8 *s1,   const UINT8 *s2);

extern INT32 ql_strncmp_ig_sp_case(const UINT8 *s1,   const UINT8 *s2, UINT32 n);

extern INT32 ql_atoi(UINT32 *val_arg_ptr,    const UINT8 *s, UINT32  r);

extern INT32  ql_itoa(UINT32 v,  UINT8 *s,   UINT16 r);

extern bool  ql_strip_quotes_out(const UINT8 * quoted_str, UINT8 * out_str, UINT16 str_len);

extern INT32 ql_trim_string(UINT8 **start);

extern bool  ql_string_to_hex(char *hex_data, INT32 length);

extern void *ql_memccpy(void *dest, const void *src, INT32 c, size_t n);

extern char   *ql_strdup(const char *src);

extern ip_type_e    ql_check_ip_type(char *IP);

extern int ql_hexstr2bin(const char *hex, unsigned char *buf, size_t len);

#endif//QL_UTILS_H


