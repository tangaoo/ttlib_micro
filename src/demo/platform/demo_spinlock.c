/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       demo_spinlock.c
 * @ingroup    demo_platform
 * @author     tango
 * @date       2021-06-26 
 * @brief      demo_spinlock.c file
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * trace
 */
#define TT_TRACE_MODULE_NAME          "DEMO_PLATFORM_SPINLOCK"
#define TT_TRACE_MODULE_DEBUG         (1)


/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "ttlib.h"
#include "../color.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */
static __tt_volatile__ tt_uint_t s_cnt = 0;
static tt_spinlock_t lock = TT_SPINLOCK_INITIALIZER;

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tt_int_t func_add(tt_cpointer_t priv)
{
    for(tt_uint_t i = 0; i < 10000; i++)
    {
        tt_spinlock_enter(&lock);
        s_cnt++;
        tt_spinlock_leave(&lock);
    }

    return 0;
}

tt_void_t tt_demo_platform_spinlock_main(tt_int_t argc, tt_char_t** argv)
{
	// print title
	tt_print_title("demo platform_spinlock");

    tt_thread_ref_t td1 = tt_thread_init(tt_null, func_add, tt_null, 0);
    tt_thread_ref_t td2 = tt_thread_init(tt_null, func_add, tt_null, 0);

    tt_thread_wait(td1, 0, tt_null);
    tt_thread_wait(td2, 0, tt_null);

    tt_trace_i("s_cnt, %u", s_cnt);
}