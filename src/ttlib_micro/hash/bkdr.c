/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       bkdr.c
 * @ingroup    hash
 * @author     tango
 * @date       2021-07-10 
 * @brief      bkdr.c file
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include <string.h>
#include "bkdr.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tt_size_t tt_bkdr_make(tt_byte_t const* data, tt_size_t size, tt_size_t seed)
{
    // check
    tt_assert_and_check_return_val(data && size, 0);

    // init value
    tt_size_t value = 0;
    if (seed) value = value * 131313 + seed;

    // generate it
    while (size--) value = (value * 131313) + (*data++);
    return value;
}
tt_size_t tt_bkdr_make_from_cstr(tt_char_t const* cstr, tt_size_t seed)
{
    // check
    tt_assert_and_check_return_val(cstr, 0);

    // make it
    return tt_bkdr_make((tt_byte_t const*)cstr, strlen(cstr) + 1, seed);
}
