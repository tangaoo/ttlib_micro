/*!The TT Library
 *
 * @Copyright (C) 2019-2020, TTLIB
 *
 * @file       demo_fixed_pool.c
 * @ingroup    demo_fixed_pool
 * @author     tango
 * @date       2020-12-21 
 * @brief      demo_fixed_pool.c file
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * trace
 */
#define TT_TRACE_MODULE_NAME          "FIXED_POOL"
#define TT_TRACE_MODULE_DEBUG         (1)

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "ttlib.h"
#include "../color.h"

tt_void_t tt_demo_fixed_pool_main(tt_void_t)
{
    // init fixed pool
    tt_static_fixed_pool_ref_t pool = tt_fixed_pool_init(tt_null, 100, 100, tt_null, tt_null, tt_null);

    // malloc 
    tt_pointer_t p1 = tt_fixed_pool_malloc(pool);
    tt_pointer_t p2 = tt_fixed_pool_malloc(pool);

    // trace 
    tt_trace_d("%p, %p", p1, p2);

    tt_fixed_pool_free(pool, p1);
    tt_fixed_pool_free(pool, p1);

}