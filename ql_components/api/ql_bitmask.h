/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef QL_BITMASK_H
#define  QL_BITMASK_H


typedef struct
{
  UINT64  bits_1_64;
  UINT64  bits_65_128;
  UINT64  bits_129_192;
  UINT64  bits_193_256;
} bit_mask_256_t;

typedef struct
{
  UINT64  bits_1_64;
  UINT64  bits_65_128;
  UINT64  bits_129_192;
  UINT64  bits_193_256;
  UINT64  bits_257_320;
  UINT64  bits_321_384;
  UINT64  bits_385_448;
  UINT64  bits_449_512;
} bit_mask_512_t;

/*===========================================================================
FUNCTION bit_mask_256_bit_is_present

DESCRIPTION
  Check if the bit bit_num is set in the bitmask.

DEPENDENCIES
  None

RETURN VALUE
  TRUE is operation successful.

SIDE EFFECTS
  None

===========================================================================*/
extern bool  ql_bit_mask_256_bit_is_present(
  bit_mask_256_t      *bit_mask_ptr,
  size_t               bit_num
);
/*===========================================================================
FUNCTION bit_mask_256_set_bit

DESCRIPTION
  Set the bit bit_num in the bitmask.

DEPENDENCIES
  None

RETURN VALUE
  TRUE is operation successful.

SIDE EFFECTS
  None

===========================================================================*/
extern bool ql_bit_mask_256_set_bit(bit_mask_256_t      *bit_mask_ptr, size_t               bit_num);
/*===========================================================================
FUNCTION bit_mask_256_clear_bit

DESCRIPTION
  Reset the bit bit_num in the bitmask.

DEPENDENCIES
  None

RETURN VALUE
  TRUE is operation successful.

SIDE EFFECTS
  None

===========================================================================*/
extern bool  ql_bit_mask_256_clear_bit(
  bit_mask_256_t      *bit_mask_ptr,
  size_t               bit_num
);
/*===========================================================================
FUNCTION bit_mask_256_masks_are_equal

DESCRIPTION
  Check if the same bits are set in both the bitmasks.

DEPENDENCIES
  None

RETURN VALUE
  TRUE if bitmasks equal.

SIDE EFFECTS
  None

===========================================================================*/
extern bool ql_bit_mask_256_masks_are_equal(
  bit_mask_256_t  const    *bit_mask_ptr_A,
  bit_mask_256_t  const    *bit_mask_ptr_B
);
/*===========================================================================
FUNCTION bit_mask_256_mask_is_subset

DESCRIPTION
  Check if all the bits set in bit_mask_ptr_B are also set in bit_mask_ptr_A.

DEPENDENCIES
  None

RETURN VALUE
  TRUE if subset.

SIDE EFFECTS
  None

===========================================================================*/
extern bool ql_bit_mask_256_mask_is_subset(
  bit_mask_256_t  const   *bit_mask_ptr_A,
  bit_mask_256_t  const   *bit_mask_ptr_B
);

/*===========================================================================
FUNCTION bit_mask_256_mask_is_empty

DESCRIPTION
  Check if all the bits in the bitmask are reset.

DEPENDENCIES
  None

RETURN VALUE
  TRUE if mask empty.

SIDE EFFECTS
  None

===========================================================================*/
extern bool ql_bit_mask_256_mask_is_empty(
  bit_mask_256_t  const    *bit_mask_ptr
);
/*===========================================================================
FUNCTION bit_mask_256_set_all

DESCRIPTION
  Set all the bits in the bitmask .

DEPENDENCIES
  None

RETURN VALUE
  None.

SIDE EFFECTS
  None

===========================================================================*/
extern void ql_bit_mask_256_set_all(
  bit_mask_256_t      *bit_mask_ptr
);
/*===========================================================================
FUNCTION bit_mask_256_clear_all

DESCRIPTION
  Reset all the bits in the bitmask .

DEPENDENCIES
  None

RETURN VALUE
  None.

SIDE EFFECTS
  None

===========================================================================*/
extern void ql_bit_mask_256_clear_all(
  bit_mask_256_t      *bit_mask_ptr
);
/*===========================================================================
FUNCTION bit_mask_256_masks_common

DESCRIPTION
  Find the bits set in both the input bitmasks .

DEPENDENCIES
  None

RETURN VALUE
  bit_mask_256_t.

SIDE EFFECTS
  None

===========================================================================*/
extern bit_mask_256_t ql_bit_mask_256_masks_common(
  bit_mask_256_t  const    *bit_mask_ptr_A,
  bit_mask_256_t  const    *bit_mask_ptr_B
);
/*===========================================================================
FUNCTION bit_mask_256_masks_overlap

DESCRIPTION
  Check if any of the same bits are set in both the bitmasks.

DEPENDENCIES
  None

RETURN VALUE
  TRUE if bitmasks overlap

SIDE EFFECTS
  None

===========================================================================*/
extern bool ql_bit_mask_256_masks_overlap(
  bit_mask_256_t const *bit_mask_ptr_A,
  bit_mask_256_t const *bit_mask_ptr_B
);
/*===========================================================================
FUNCTION bit_mask_256_add_mask

DESCRIPTION
  Set all the bits set in bit_mask_ptr_B in bit_mask_ptr_A as well.

DEPENDENCIES
  None

RETURN VALUE
  None.

SIDE EFFECTS
  None

===========================================================================*/
extern void ql_bit_mask_256_add_mask(
  bit_mask_256_t       *bit_mask_ptr_A,
  bit_mask_256_t const *bit_mask_ptr_B
);
/*===========================================================================
FUNCTION bit_mask_256_remove_mask

DESCRIPTION
  Reset all the bits set in bit_mask_ptr_B in bit_mask_ptr_A.

DEPENDENCIES
  None

RETURN VALUE
  None.

SIDE EFFECTS
  None

===========================================================================*/
extern void  ql_bit_mask_256_remove_mask(
  bit_mask_256_t       *bit_mask_ptr_A,
  bit_mask_256_t const *bit_mask_ptr_B
);
/*===========================================================================
FUNCTION bit_mask_256_mask_xor_masks

DESCRIPTION
  Perform the bitwise XOR operation on the 2 input bitmasks and return the
  result.

DEPENDENCIES
  None

RETURN VALUE
  bit_mask_256_t.

SIDE EFFECTS
  None

===========================================================================*/
extern bit_mask_256_t ql_bit_mask_256_mask_xor_masks(
  bit_mask_256_t  const   *bit_mask_ptr_A,
  bit_mask_256_t  const   *bit_mask_ptr_B
);
/*===========================================================================
FUNCTION bit_mask_256_inv_all

DESCRIPTION
  Toggle all the bits in the bitmask .

DEPENDENCIES
  None

RETURN VALUE
  bit_mask_256_t.

SIDE EFFECTS
  None

===========================================================================*/
extern bit_mask_256_t ql_bit_mask_256_inv_all(
  bit_mask_256_t      *bit_mask_ptr
);
/*===========================================================================
FUNCTION bit_mask_512_bit_operation

DESCRIPTION
  Perform the selected operation on the bitmask.
  - BIT_MASK_OP_IS
  - BIT_MASK_OP_SET
  - BIT_MASK_OP_CLEAR

DEPENDENCIES
  None

RETURN VALUE
  TRUE is operation successful.

SIDE EFFECTS
  None

===========================================================================*/
extern bool ql_bit_mask_512_bit_operation(
  bit_mask_512_t      *bit_mask_ptr,
  size_t               bit_num,
  int                  op
);
/*===========================================================================
FUNCTION bit_mask_512_bit_is_present

DESCRIPTION
  Check if the bit bit_num is set in the bitmask.

DEPENDENCIES
  None

RETURN VALUE
  TRUE is operation successful.

SIDE EFFECTS
  None

===========================================================================*/

extern bool ql_bit_mask_512_bit_is_present(
  bit_mask_512_t      *bit_mask_ptr,
  size_t               bit_num
);
/*===========================================================================
FUNCTION bit_mask_512_set_bit

DESCRIPTION
  Set the bit bit_num in the bitmask.

DEPENDENCIES
  None

RETURN VALUE
  TRUE is operation successful.

SIDE EFFECTS
  None

===========================================================================*/
extern bool ql_bit_mask_512_set_bit(
  bit_mask_512_t      *bit_mask_ptr,
  size_t               bit_num
);
/*===========================================================================
FUNCTION bit_mask_512_clear_bit

DESCRIPTION
  Reset the bit bit_num in the bitmask.

DEPENDENCIES
  None

RETURN VALUE
  TRUE is operation successful.

SIDE EFFECTS
  None

===========================================================================*/
extern bool ql_bit_mask_512_clear_bit(
  bit_mask_512_t      *bit_mask_ptr,
  size_t               bit_num
);
/*===========================================================================
FUNCTION bit_mask_512_masks_are_equal

DESCRIPTION
  Check if the same bits are set in both the bitmasks.

DEPENDENCIES
  None

RETURN VALUE
  TRUE if bitmasks equal.

SIDE EFFECTS
  None

===========================================================================*/
extern bool ql_bit_mask_512_masks_are_equal(
  bit_mask_512_t const *bit_mask_ptr_A,
  bit_mask_512_t const *bit_mask_ptr_B
);
/*===========================================================================
FUNCTION bit_mask_512_masks_overlap

DESCRIPTION
  Check if any of the same bits are set in both the bitmasks.

DEPENDENCIES
  None

RETURN VALUE
  TRUE if bitmasks overlap

SIDE EFFECTS
  None

===========================================================================*/
extern bool ql_bit_mask_512_masks_overlap(
  bit_mask_512_t const *bit_mask_ptr_A,
  bit_mask_512_t const *bit_mask_ptr_B
);
/*===========================================================================
FUNCTION bit_mask_512_mask_is_subset

DESCRIPTION
  Check if all the bits set in bit_mask_ptr_B are also set in bit_mask_ptr_A.

DEPENDENCIES
  None

RETURN VALUE
  TRUE if subset.

SIDE EFFECTS
  None

===========================================================================*/
extern bool ql_bit_mask_512_mask_is_subset(
  bit_mask_512_t const  *bit_mask_ptr_A,
  bit_mask_512_t const  *bit_mask_ptr_B
);
/*===========================================================================
FUNCTION bit_mask_512_mask_is_empty

DESCRIPTION
  Check if all the bits in the bitmask are reset.

DEPENDENCIES
  None

RETURN VALUE
  TRUE if mask empty.

SIDE EFFECTS
  None

===========================================================================*/
extern bool ql_bit_mask_512_mask_is_empty(
  bit_mask_512_t const *bit_mask_ptr
);
/*===========================================================================
FUNCTION bit_mask_512_set_all

DESCRIPTION
  Set all the bits in the bitmask .

DEPENDENCIES
  None

RETURN VALUE
  None.

SIDE EFFECTS
  None

===========================================================================*/
extern void ql_bit_mask_512_set_all(
  bit_mask_512_t  *bit_mask_ptr
);
/*===========================================================================
FUNCTION bit_mask_512_clear_all

DESCRIPTION
  Reset all the bits in the bitmask .

DEPENDENCIES
  None

RETURN VALUE
  None.

SIDE EFFECTS
  None

===========================================================================*/
extern void ql_bit_mask_512_clear_all(
  bit_mask_512_t  *bit_mask_ptr
);
/*===========================================================================
FUNCTION bit_mask_512_masks_common

DESCRIPTION
  Find the bits set in both the input bitmasks .

DEPENDENCIES
  None

RETURN VALUE
  bit_mask_512_t.

SIDE EFFECTS
  None

===========================================================================*/
extern bit_mask_512_t ql_bit_mask_512_masks_common(
  bit_mask_512_t const     *bit_mask_ptr_A,
  bit_mask_512_t const     *bit_mask_ptr_B
);
/*===========================================================================
FUNCTION bit_mask_512_add_mask

DESCRIPTION
  Set all the bits set in bit_mask_ptr_B in bit_mask_ptr_A as well.

DEPENDENCIES
  None

RETURN VALUE
  None.

SIDE EFFECTS
  None

===========================================================================*/
extern void ql_bit_mask_512_add_mask(
  bit_mask_512_t       *bit_mask_ptr_A,
  bit_mask_512_t const *bit_mask_ptr_B
);
/*===========================================================================
FUNCTION bit_mask_512_remove_mask

DESCRIPTION
  Reset all the bits set in bit_mask_ptr_B in bit_mask_ptr_A.

DEPENDENCIES
  None

RETURN VALUE
  None.

SIDE EFFECTS
  None

===========================================================================*/
extern void  ql_bit_mask_512_remove_mask(
  bit_mask_512_t       *bit_mask_ptr_A,
  bit_mask_512_t const *bit_mask_ptr_B
);
/*===========================================================================
FUNCTION bit_mask_512_mask_xor_masks

DESCRIPTION
  Perform the bitwise XOR operation on the 2 input bitmasks and return the
  result.

DEPENDENCIES
  None

RETURN VALUE
  bit_mask_256_t.

SIDE EFFECTS
  None

===========================================================================*/
extern bit_mask_512_t ql_bit_mask_512_mask_xor_masks(
  bit_mask_512_t const     *bit_mask_ptr_A,
  bit_mask_512_t const     *bit_mask_ptr_B
);
/*===========================================================================
FUNCTION bit_mask_512_inv_all

DESCRIPTION
  Toggle all the bits in the bitmask .

DEPENDENCIES
  None

RETURN VALUE
  bit_mask_512_t.

SIDE EFFECTS
  None

===========================================================================*/
extern bit_mask_512_t ql_bit_mask_512_inv_all(
  bit_mask_512_t      *bit_mask_ptr
);
#endif//QL_BITMASK_H

