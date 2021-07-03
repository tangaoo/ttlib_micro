/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       demo_semaphore.c
 * @ingroup    demo/platform
 * @author     tango
 * @date       2021-07-03 
 * @brief      demo_semaphore.c file
 */


/* //////////////////////////////////////////////////////////////////////////////////////
 * trace
 */
#define TT_TRACE_MODULE_NAME          "DEMO_PLATFORM_SEMAPHORE"
#define TT_TRACE_MODULE_DEBUG         (1)


/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "ttlib.h"
#include "../color.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */
tt_semaphore_ref_t semaphore;

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tt_int_t demo_semaphore_pthread(tt_void_t* priv)
{
    tt_trace_d("semaphore pthread");
    semaphore = tt_semaphore_init(0);

    // post semaphore
    if(semaphore)
    {
        tt_trace_d("demo, semaphore post");
        tt_semaphore_post(semaphore, 1);
    }

    return 0;
}

tt_void_t tt_demo_platform_semaphore_main(tt_int_t argc, tt_char_t** argv)
{
	// print title
	tt_print_title("demo platform_semaphore");

    tt_thread_ref_t td1 = tt_thread_init(tt_null, demo_semaphore_pthread, tt_null, 0);

    tt_thread_wait(td1, 0, tt_null);

    tt_semaphore_wait(semaphore);
    tt_trace_d("have wait semaphore");

}