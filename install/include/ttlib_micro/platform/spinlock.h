/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       spinlock.h
 * @ingroup    platform
 * @author     tango
 * @date       2020-11-19 
 * @brief      spinlock.h file
 */

#ifndef TT_PLATFORM_SPINLOCK_H
#define TT_PLATFORM_SPINLOCK_H

// choose use which spin_lock
#ifndef TT_USE_THREAD_LOCK

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "atomic.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */
#define TT_SPINLOCK_INITIALIZER    TT_ATOMIC_FLAG_INIT 

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */
typedef tt_atomic_flag_t        tt_spinlock_t;
typedef tt_atomic_flag_t*       tt_spinlock_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * static implementation
 */

/*! init spinlock
 *
 * @param lock                  the spin lock
 *
 * @return                      tt_true or tt_false
 */
static __tt_inline__ tt_bool_t  tt_spinlock_init_impl(tt_spinlock_ref_t lock)
{
    tt_assert(lock);
    tt_atomic_flag_clear_explicit(lock, TT_ATOMIC_RELAXED);

    return tt_true;
}

/*! exit spinlock
 *
 * @param lock                   the spin lock
 *
 * @return                       tt_void_t
 */
static __tt_inline__ tt_void_t   tt_spinlock_exit(tt_spinlock_ref_t lock)
{
    tt_assert(lock);
    tt_atomic_flag_clear_explicit(lock, TT_ATOMIC_RELAXED);
}

/*! enter spinlock, @note cup core must > 1
 *
 * @param lock                    the spin lock
 *
 * @return                        tt_void_t
 */
static __tt_inline__ tt_void_t    tt_spinlock_enter(tt_spinlock_ref_t lock)
{
    tt_assert(lock);

    while(1)
    {
        // TODO, need opt according diffrent platform
        if(!tt_atomic_flag_test_noatomic(lock) && !tt_atomic_flag_test_and_set(lock))
            return;
    }
}

/*! try enter spinlock
 *
 * @param lock                     the spin lock
 *
 * @return                         tt_true or tt_false
 */
static __tt_inline__ tt_bool_t     tt_spinlock_enter_try(tt_spinlock_ref_t lock)
{
    tt_assert(lock);

    return !tt_atomic_flag_test_and_set(lock);
}

/*! leave spinlock
 *
 * @param lock                      the spin lock
 *
 * @return                          tt_void_t
 */
static __tt_inline__ tt_void_t      tt_spinlock_leave(tt_spinlock_ref_t lock)
{
    tt_assert(lock);

    tt_atomic_flag_clear(lock);
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#else

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "mutex.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * type
 */
typedef tt_mutex_t             tt_spinlock_t;
typedef tt_mutex_ref_t         tt_spinlock_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */
#define TT_SPINLOCK_INITIALIZER TT_PTHREAD_MUTEX_INITIALIZER

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/*! init spinlock(alloc spinlock outside)
 *
 * @param  spinlock            the spinlock ref
 *
 * @return                     spinlock            
 */
tt_spinlock_t*                 tt_spinlock_init_impl(tt_spinlock_t * spinlock)
{
    ///check
    tt_assert(spinlock);
    return (tt_spinlock_t*)tt_mutex_init_impl((tt_mutex_t *)spinlock);
}

/*! exit spinlock
 *
 * @param spinlock             the spinlock             
 *
 * @return                     tt_void
 */
tt_void_t                      tt_spinlock_exit_impl(tt_spinlock_t * spinlock)
{
    ///check
    tt_assert(spinlock);
    tt_mutex_exit_impl((tt_mutex_t *)spinlock);
}

/*! init spinlock(dynamic malloc inside)
 *
 * @param spinlock             the spinlock
 *
 * @return                     the spinlock
 */
tt_spinlock_ref_t              tt_spinlock_init(tt_void_t)
{
    return (tt_spinlock_ref_t)tt_mutex_init();
}

/*! exit spinlock
 *
 * @param spinlock             the spinlock
 *
 * @return                     tt_void
 */
tt_void_t                      tt_spinlock_exit(tt_spinlock_ref_t spinlock)
{
    ///check
    tt_assert(spinlock);
    tt_mutex_exit((tt_mutex_ref_t)spinlock);
}

/*! entry spinlock
 *
 * @param spinloc              the spinlock
 *
 * @return                     tt_true or tt_false
 */
tt_bool_t                      tt_spinlock_enter(tt_spinlock_ref_t spinlock)
{
    ///check
    tt_assert(spinlock);
    return tt_mutex_entry((tt_mutex_ref_t)spinlock);
}

/*! entry spinlock try
 *
 * @param spinloc              the spinlock
 *
 * @return                     tt_true or tt_false
 */
tt_bool_t                      tt_spinlock_enter_try(tt_spinlock_ref_t spinlock)
{
    ///check
    tt_assert(spinlock);
    return tt_mutex_entry_try((tt_mutex_ref_t)spinlock);
}

/*! leave spinlock
 *
 * @param spinloc              the spinlock
 *
 * @return                     tt_true or tt_false
 */
tt_bool_t                      tt_spinlock_leave(tt_spinlock_ref_t spinlock)
{
    ///check
    tt_assert(spinlock);
    return tt_mutex_leave((tt_mutex_ref_t)spinlock);
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif // TT_USE_THREAD_LOCK

#endif