/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef QL_SHA256_H
#define  QL_SHA256_H

typedef struct {
    UINT32  total[2];          /*!< number of bytes processed  */
    UINT32  state[8];          /*!< intermediate digest state  */
    UINT8    buffer[64];   /*!< data block being processed */
    UINT8    is224;              /*!< 0 => SHA-256, else SHA-224 */
} sha256_context_t;

/**
 * \brief          Initialize SHA-256 context
 *
 * \param ctx      SHA-256 context to be initialized
 */
extern void   ql_sha256_init(sha256_context_t *ctx);

/**
 * \brief          Clear SHA-256 context
 *
 * \param ctx      SHA-256 context to be cleared
 */
extern void   ql_sha256_free(sha256_context_t *ctx);


/**
 * \brief          SHA-256 context setup
 *
 * \param ctx      context to be initialized
 */
extern void   ql_sha256_starts(sha256_context_t *ctx);

/**
 * \brief          SHA-256 process buffer
 *
 * \param ctx      SHA-256 context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 */
extern void   ql_sha256_update(sha256_context_t *ctx, const UINT8 *input, UINT32 ilen);

/**
 * \brief          SHA-256 final digest
 *
 * \param ctx      SHA-256 context
 * \param output   SHA-256 checksum result
 */
extern void   ql_sha256_finish(sha256_context_t *ctx, UINT8 output[32]);


/* Internal use */
extern void   ql_sha256_process(sha256_context_t *ctx, const UINT8 data[64]);

/**
 * \brief          Output = SHA-256( input buffer )
 *
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   SHA-256 checksum result
 */
extern void   ql_sha256(const UINT8 *input, UINT32 ilen, UINT8 output[32]);


extern void   ql_hmac_sha256(const UINT8 *msg, UINT32 msg_len, const UINT8 *key, UINT32 key_len, UINT8 output[32]);


#endif//QL_SHA256_H
