/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       port.h
 * @ingroup    prefix
 * @author     tango
 * @date       2021-07-11 
 * @brief      port.h file is wrap of stdandard library's memory or string operate.
 */

#ifndef TT_PREFIX_PORT_H
#define TT_PREFIX_PORT_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */

#include "cpu.h"
#include "type.h"
#include "check.h"
#include "assert.h"

// memset_ptr
#ifdef TT_CPU_BIT_64
#   define      tt_memset_ptr(s, p, n)      tt_memset_u64_impl(s, (tt_uint64_t)(p), n)
#else
#   define      tt_memset_ptr(s, p, n)      tt_memset_u32_impl(s, (tt_uint32_t)(p), n)
#endif

static tt_pointer_t tt_memset_u32_impl(tt_pointer_t s, tt_uint32_t c, tt_size_t n)
{
    // check
    tt_assert_and_check_return_val(s, tt_null);

    // no size?
    tt_check_return_val(n, s);

    // must be aligned by 4-bytes
    tt_assert(!(((tt_size_t)s) & 0x3));

    // init
    __tt_register__ tt_uint32_t* p = (tt_uint32_t*)s;

    // done
    while (n--) *p++ = c;

    // ok?
    return s;
}

static tt_pointer_t tt_memset_u64_impl(tt_pointer_t s, tt_uint64_t c, tt_size_t n)
{
    // check
    tt_assert_and_check_return_val(s, tt_null);

    // no size?
    tt_check_return_val(n, s);

    // must be aligned by 8-bytes
    tt_assert(!(((tt_size_t)s) & 0x7));

    // init
    __tt_register__ tt_uint64_t* p = (tt_uint64_t*)s;

    // done
    while (n--) *p++ = c;

    return s;
}

#endif