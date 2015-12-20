/*------------------------------------------------------------------------------
//                         RESTRICTED RIGHTS LEGEND
//
// Use,  duplication, or  disclosure  by  the  Government is subject 
// to restrictions as set forth in subdivision (c)(1)(ii) of the Rights
// in Technical Data and Computer Software clause at 52.227-7013. 
//
// Copyright 1989, 1990, 1991 Texas Instruments Incorporated.  All rights reserved.
//------------------------------------------------------------------------------
*/

#include <stddef.h>


//Removed fall 2014
/*
#define INT int
#define ALIGN int
#define NALIGN 1

#define Deadlock_sig 31
#define WORD sizeof(union cell)
#define DEFAULT_SEMA_NUM 16

#define UPPER_RANGE_SEMA_NUM 64
#define LOWER_RANGE_SEMA_NUM 3


#define UPPER_RANGE_INTERVAL 120
#define LOWER_RANGE_INTERVAL 1
#define DEFAULT_INTERVAL 5
*/

#define  ZGT_DEFAULT_HASH_TABLE_SIZE  13

#define NTRANSACTION_TYPES 2
#define ODD 1


#define TR_ACTIVE 'P'
#define TR_WAIT   'W'
#define TR_ABORT  'A'
#define TR_END    'E'

//Removed fall 2014
/*
#define SHARED_MEM_AVAIL 0
#define ZGT_SPACE_EMPTY 1
#define ZGT_NO_INIT 2
#define ZGT_INIT_DUPLICATED 3
#define ZGT_INSUFFOCIENT_SEMA 4
#define ZGT_INSUFFOCIENT_SHARED_MEM 5
#define ZGT_DEADLOCK_VICTIM 6
#define ZGT_LOCK_DENIED 7
#define ZGT_SYSTEM_ERROR 8
#define ZGT_NOT_ENOUGH_ARGS 9
#define ZGT_SEMA_ALLOC_FAILS 10
#define ZGT_SHARED_MEM_ALLOC_FAILS 11
#define ZGT_SEMA_P_OP_FAILS 12
#define ZGT_SEMA_V_OP_FAILS 13
#define ZGT_USE_UPDATE_LOCK 14
*/
