/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       bkdr.h
 * @ingroup    hash
 * @author     tango
 * @date       2021-07-10 
 * @brief      bkdr.h file
 */

#ifndef TT_HASH_BKDR_H
#define TT_HASH_BKDR_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! make bkdr hash
 *
 * @param data      the data
 * @param size      the size
 * @param seed      uses this seed if be non-zero
 *
 * @return          the bkdr value
 */
tt_size_t           tt_bkdr_make(tt_byte_t const* data, tt_size_t size, tt_size_t seed);

/*! make bkdr hash from c-string
 *
 * @param cstr      the c-string
 * @param seed      uses this seed if be non-zero
 *
 * @return          the bkdr value
 */
tt_size_t           tt_bkdr_make_from_cstr(tt_char_t const* cstr, tt_size_t seed);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif
