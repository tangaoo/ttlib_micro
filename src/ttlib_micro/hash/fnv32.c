/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       fnv32.c
 * @ingroup    hash
 * @author     tango
 * @date       2021-07-10 
 * @brief      fnv32.c file
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include <string.h>
#include "fnv32.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// the pnv32 prime and offset basis
#define TT_FNV32_PRIME          (16777619)
#define TT_FNV32_OFFSET_BASIS   (2166136261)

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tt_uint32_t tt_fnv32_make(tt_byte_t const* data, tt_size_t size, tt_uint32_t seed)
{
    // check
    tt_assert_and_check_return_val(data && size, 0);

    // init value
    tt_uint32_t value = TT_FNV32_OFFSET_BASIS;
    if (seed) value = (value * TT_FNV32_PRIME) ^ seed;

    // generate it
    while (size)
    {
        value *= TT_FNV32_PRIME;
        value ^= (tt_uint32_t)*data++;
        size--;
    }
    return value;
}
tt_uint32_t tt_fnv32_make_from_cstr(tt_char_t const* cstr, tt_uint32_t seed)
{
    // check
    tt_assert_and_check_return_val(cstr, 0);

    // make it
    return tt_fnv32_make((tt_byte_t const*)cstr, strlen(cstr) + 1, seed);
}
tt_uint32_t tt_fnv32_1a_make(tt_byte_t const* data, tt_size_t size, tt_uint32_t seed)
{
    // check
    tt_assert_and_check_return_val(data && size, 0);

    // init value
    tt_uint32_t value = TT_FNV32_OFFSET_BASIS;
    if (seed) value = (value * TT_FNV32_PRIME) ^ seed;

    // generate it
    while (size)
    {
        value ^= (tt_uint32_t)*data++;
        value *= TT_FNV32_PRIME;
        size--;
    }
    return value;
}
tt_uint32_t tt_fnv32_1a_make_from_cstr(tt_char_t const* cstr, tt_uint32_t seed)
{
    // check
    tt_assert_and_check_return_val(cstr, 0);

    // make it
    return tt_fnv32_1a_make((tt_byte_t const*)cstr, strlen(cstr) + 1, seed);
}
