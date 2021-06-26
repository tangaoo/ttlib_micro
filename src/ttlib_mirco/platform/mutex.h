/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       mutex.h
 * @ingroup    platform
 * @author     tango
 * @date       2020-11-19 
 * @brief      mutex.h file 
 */

#ifndef TT_PLATFORM_MUTEX_H
#define TT_PLATFORM_MUTEX_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "pthread.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */
typedef pthread_mutex_t    tt_mutex_t;
typedef pthread_mutex_t*   tt_mutex_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */
// mutex has two ways to initiailizer, static or dynamic
#define TT_PTHREAD_MUTEX_INITIALIZER    PTHREAD_MUTEX_INITIALIZER 

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! init mutex(alloc mutex outside)
 *
 * @param mutex             the mutex
 *
 * @return                  the mutex or tt_null
 */
tt_mutex_t*                 tt_mutex_init_impl(tt_mutex_t * mutex);

/*! exit mutex
 *
 * @param mutex             the mutex
 *
 * @return                  void
 */
tt_void_t                   tt_mutex_exit_impl(tt_mutex_t * mutex);

/*! int mutex(dynamic malloc inside)
 *
 * @return                  the mutex
 */
tt_mutex_ref_t              tt_mutex_init(tt_void_t);

/*! exit mutex
 *
 * @param mutex             the mutex
 *
 * @return                  void
 */
tt_void_t                   tt_mutex_exit(tt_mutex_ref_t mutex);

/*! entry mutex
 *
 * @param mutex             the mutex
 *
 * @return                  tt_true or tt_false
 */
tt_bool_t                   tt_mutex_entry(tt_mutex_ref_t mutex);

/*! try entry mutex
 *
 * @param mutex             the mutex
 *
 * @return                  tt_true or tt_false
 */
tt_bool_t                   tt_mutex_entry_try(tt_mutex_ref_t mutex);

/*! leave mutex
 *
 * @param mutex             the mutex
 *
 * @return                  tt_true or tt_false
 */
tt_bool_t                   tt_mutex_leave(tt_mutex_ref_t mutex);


/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif