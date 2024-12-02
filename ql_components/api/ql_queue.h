/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/
#ifndef QL_QUEUE_H
#define  QL_QUEUE_H

#include "ql_osi.h"
/* -------------------------------------------------------------------------
** Queue Link Structure
**
** The following link structure is really the heart of the Queue Services. 
** It is used as a link field with variables which allows them to be moved
** on and off queues. It is also used in the definition of queues themselves.
**
** Do NOT directly access the fields of a link! Only the Queue Services should
** do this.
** ------------------------------------------------------------------------- */
typedef struct q_list_struct
{
  struct q_list_struct  *next_ptr;
    /* Ptr to next link in list. If NULL, there is no next link. */
  struct q_list_struct  *prev_ptr;
} q_list_type;

  /*These are HTORPCMETA comments, Do not delete this.*/
  /*~ FIELD q_link_struct.next_ptr VOID */
  /*~ FIELD q_link_struct.prev_ptr VOID */


/* ------------------------------------------------------------------------
** Queue Head Link Structure
**
** When queue items are linked in a singly link list, q_head_link_type is
** used instead of q_link_type. This avoids the overhead of traversing 
** the whole of link list when queueing at the end of the link list.
** This structure should be accessed only by Queue services.
** ------------------------------------------------------------------------ */
typedef q_list_type q_head_list_type;

/* ------------------------------------------------------------------------
** Queue Structure
**
** The following structure format is used by the Queue Services to represent
** a queue.
** 
** Do NOT access the fields of a queue directly. Only the Queue Services should
** do this.
** ------------------------------------------------------------------------ */
typedef struct q_struct
{
  q_head_list_type  link;

    /* Used for linking items into queue. */

  INT32          cnt;
    /* Keeps track of number of items enqueued. Though not necessary, having
       this field is tremendously helpful for debugging. */

   ql_mutex_t        mutex;            /* Mutex                    */
} q_type;

/* ------------------------------------------------------------------------
** Queue Generic Item
**   Generic items must have q_link_type as the first element.  This allows
**   the linear search function to traverse the list without knowing
**   anything about the elements
** ------------------------------------------------------------------------ */
typedef struct {
   q_list_type link;
} q_item_type;

/* ------------------------------------------------------------------------
** Queue Compare Function
**    Used by the searching functions to determine if an item is in
**       the queue.
**    Returns non zero if the element should be operated upon, 0 otherwise
**    For linear searching, the operation is to return a pointer to the
**       item and terminate the search
**    For linear deleting, the operation is to remove the item from the
**       queue and continue the traversal
** ------------------------------------------------------------------------ */
typedef INT32  (*q_compare_func_type)( void* item_ptr, void* compare_val );

/* ------------------------------------------------------------------------
** Queue Action Function
**    Used by q_linear_delete to perform an action on an item which is 
**    being deleted from the list AFTER the item is deleted.  To perform
**    an action BEFORE the item is deleted, the user can call the action
**    function directly in the compare function call back.
** ------------------------------------------------------------------------ */
typedef void (*q_action_func_type)( void *item_ptr, void* param );

/*===========================================================================

                             Macro Definitions

===========================================================================*/

  #define Q_XCEPT_Q_INIT( q_ptr )
  #define Q_XCEPT_Q_LINK( q_ptr, link_ptr )
  #define Q_XCEPT_Q_PUT( q_ptr, link_ptr )
  #define Q_XCEPT_Q_GET( q_ptr )
  #define Q_XCEPT_Q_LAST_GET( q_ptr )
  #define Q_XCEPT_Q_CNT( q_ptr )
  #define Q_XCEPT_Q_CHECK( q_ptr )
  #define Q_XCEPT_Q_LAST_CHECK( q_ptr )
  #define Q_XCEPT_Q_NEXT( q_ptr, link_ptr )
  #define Q_XCEPT_Q_INSERT( q_ptr, q_insert_ptr, q_item_ptr )
  
  #define Q_XCEPT_Q_DELETE( q_ptr, q_delete_ptr )
  

/* ========================================================================
MACRO Q_ALREADY_QUEUED
DESCRIPTION
   Evaluates to true if the item passed in is already in a queue and to
   false otherwise.
=========================================================================== */
#define Q_ALREADY_QUEUED( q_link_ptr ) \
   ((q_link_ptr)->next_ptr != NULL)

/*===========================================================================

                            Function Declarations

===========================================================================*/
/*==========================================================================

FUNCTION Q_INIT

DESCRIPTION
  This function initializes a specified queue. It should be called for each
  queue prior to using the queue with the other Queue Services.

DEPENDENCIES
  None.

RETURN VALUE
  A pointer to the initialized queue.

SIDE EFFECTS
  The specified queue is initialized for use with Queue Services.

===========================================================================*/
extern q_type* q_init(q_type *q_ptr );

/*===========================================================================

FUNCTION Q_LINK

DESCRIPTION
  This function initializes a specified link. It should be called for each
  link prior to using the link with the other Queue Services.

DEPENDENCIES
  None.

RETURN VALUE
  A pointer to the initialized link.

SIDE EFFECTS
  The specified link is initialized for use with the Queue Services.

===========================================================================*/
extern q_list_type* q_link
 ( 
 void *item_ptr,
 q_list_type *link_ptr
 );

/*===========================================================================

FUNCTION Q_PUT

DESCRIPTION
  This function enqueues an item onto a specified queue using a specified
  link.

DEPENDENCIES
  The specified queue should have been previously initialized via a call
  to q_init. The specified link field of the item should have been prev-
  iously initialized via a call to q_init_link.

RETURN VALUE
  None.

SIDE EFFECTS
  The specified item is placed at the tail of the specified queue.

===========================================================================*/
extern void  q_put(q_type *q_ptr, q_list_type *link_ptr );
/*===========================================================================
FUNCTION Q_M_PUT

DESCRIPTION
  This function enqueues all items from a specified (source) queue into a 
  specified (target) queue.

DEPENDENCIES
  The specified queues should have been previously initialized via a call
  to q_init.

RETURN VALUE
  None.

SIDE EFFECTS
  The items in the specified (source) queue are placed at the tail of the 
  specified (target) queue.
===========================================================================*/
extern void q_m_put(q_type  *target_q_ptr, q_type       *source_q_ptr);
/*===========================================================================

FUNCTION Q_GET

DESCRIPTION
  This function removes an item from the head of a specified queue.

DEPENDENCIES
  The specified queue should have been initialized previously via a call
  to q_init.

RETURN VALUE
  A pointer to the dequeued item. If the specified queue is empty, then
  NULL is returned.

SIDE EFFECTS
  The head item, if any, is removed from the specified queue.

===========================================================================*/
extern void* q_get( q_type *q_ptr );
/*===========================================================================

FUNCTION Q_LAST_GET

DESCRIPTION
  This function removes an item from the tail of a specified queue.

DEPENDENCIES
  The specified queue should have been initialized previously via a call
  to q_init.

RETURN VALUE
  A pointer to the dequeued item. If the specified queue is empty, then
  NULL is returned.

SIDE EFFECTS
  The head item, if any, is removed from the specified queue.

===========================================================================*/
extern void* q_last_get(q_type *q_ptr );
/*===========================================================================

FUNCTION Q_CNT

DESCRIPTION
  This function returns the number of items currently queued on a specified
  queue.

DEPENDENCIES
  The specified queue should have been initialized previously via a call
  to q_init.

RETURN VALUE
  The number of items currently queued on the specified queue.

SIDE EFFECTS
  None.

===========================================================================*/
extern INT32  q_cnt(q_type *q_ptr);
/*===========================================================================

FUNCTION Q_CHECK

DESCRIPTION
  This function returns a pointer to the data block at the head of the queue.
  The data block is not removed from the queue.

DEPENDENCIES
  The specified queue should have been initialized previously via a call
  to q_init.

RETURN VALUE
  A pointer to the queue item. If the specified queue is empty, then
  NULL is returned.

SIDE EFFECTS
  None

===========================================================================*/
extern void* q_check(q_type  *q_ptr);
/*===========================================================================

FUNCTION Q_LAST_CHECK

DESCRIPTION
  This function returns a pointer to the data block at the tail of the queue.
  The data block is not removed from the queue.

DEPENDENCIES
  The specified queue should have been initialized previously via a call
  to q_init.

RETURN VALUE
  A pointer to the queue item. If the specified queue is empty, then
  NULL is returned.

SIDE EFFECTS
  The head item, if any, is removed from the specified queue.

===========================================================================*/
extern void* q_last_check(q_type *q_ptr );
/*===========================================================================

FUNCTION Q_NEXT

DESCRIPTION
  This function returns a pointer to the next item on the queue.

DEPENDENCIES
  The specified queue should have been initialized previously via a call
  to q_init.

RETURN VALUE
  A pointer to the next item on the queue. If the end of the queue is reached, 
  then NULL is returned.

SIDE EFFECTS
  None.

===========================================================================*/
extern void* q_next(q_type *q_ptr, q_list_type *link_ptr );
/*===========================================================================

FUNCTION Q_INSERT

DESCRIPTION
  This function inserts an item before a specified item on a queue.

DEPENDENCIES
  The specified queue should have been initialized previously via a call
  to q_init.

RETURN VALUE
  None.

SIDE EFFECTS
  Input item is inserted before input item.

===========================================================================*/
extern void q_insert(q_type *q_ptr, q_list_type *q_insert_ptr, q_list_type *q_item_ptr );
/*===========================================================================

FUNCTION Q_DELETE

DESCRIPTION
  This function removes an item from a specified queue.

DEPENDENCIES
  The specified queue should have been initialized previously via a call
  to q_init.

RETURN VALUE
  None.

SIDE EFFECTS
  Input item is delete from the queue.

===========================================================================*/
extern void q_delete(q_type *q_ptr, q_list_type *q_delete_ptr );
/*===========================================================================

FUNCTION Q_LINEAR_SEARCH

DESCRIPTION
  Given a comparison function, this function traverses the elements in
  a queue, calls the compare function, and returns a pointer to the
  current element being compared if the user passed compare function
  returns non zero.

  The user compare function should return 0 if the current element is
  not the element in which the compare function is interested.

DEPENDENCIES
  The specified queue should have been initialized previously via a call
  to q_init.

  The user's queue elements must have q_link_type as the first element
  of the queued structure.

RETURN VALUE
  A pointer to the found element

SIDE EFFECTS
  None.

===========================================================================*/
extern void* q_linear_search(
 q_type  *q_ptr, 
 q_compare_func_type compare_func, 
 void  *compare_val
);
/*===========================================================================

FUNCTION Q_LINEAR_DELETE_NEW

DESCRIPTION
  Given a comparison function, this function traverses the elements in
  a queue, calls the compare function, and returns a pointer to the
  current element being compared if the user passed compare function
  returns non zero.  In addition, the item will be removed from the queue.

  The user compare function should return 0 if the current element is
  not the element in which the compare function is interested.

DEPENDENCIES
  The specified queue should have been initialized previously via a call
  to q_init.

  The user's queue elements must have q_link_type as the first element
  of the queued structure.

 RETURN VALUE
  A pointer to the found element or NULL otherwise

SIDE EFFECTS
  None.

===========================================================================*/
extern void *q_linear_delete_new(
  q_type  *q_ptr, 
  q_compare_func_type compare_func,
  void  *compare_val, 
  q_action_func_type  action_func, 
  void  *param
);
/*===========================================================================

FUNCTION Q_LINEAR_DELETE

DESCRIPTION
  Given a comparison function, this function traverses the elements in
  a queue, calls the compare function, and returns a pointer to the
  current element being compared if the user passed compare function
  returns non zero.  In addition, the item will be removed from the queue.

  The user compare function should return 0 if the current element is
  not the element in which the compare function is interested.

DEPENDENCIES
  The specified queue should have been initialized previously via a call
  to q_init.

  The user's queue elements must have q_link_type as the first element
  of the queued structure.

  The user's compare function will be passed NULL for the compare value.

RETURN VALUE
  None

SIDE EFFECTS
  None.

===========================================================================*/
extern void q_linear_delete(
  q_type *q_ptr,  
  q_compare_func_type compare_func,
  void *param, 
  q_action_func_type  action_func
);
/*==========================================================================
FUNCTION Q_DESTROY

DESCRIPTION
  This function destroys a specified queue. It should be called if you
  do not require this queue anymore.

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  Elements in the queue will  not be accessible through this queue 
  anymore. It is user's responsibility to deallocate the memory allocated 
  for the queue and its elements to avoid leaks
===========================================================================*/
extern void q_destroy(q_type  *q_ptr);


#endif//QL_QUEUE_H

