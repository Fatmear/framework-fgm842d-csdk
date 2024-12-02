/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef QL_CRC_H
#define  QL_CRC_H

extern unsigned int ql_crc_32_calc
(
	/* Pointer to data over which to compute CRC */
	unsigned char *buf_ptr,

	/* Number of bits over which to compute CRC */
	unsigned int  len,

	/* Seed for CRC computation */
	unsigned int  seed
);

#endif//QL_CRC_H

