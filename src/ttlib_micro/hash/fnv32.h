/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       fnv32.h
 * @ingroup    hash
 * @author     tango
 * @date       2021-07-10 
 * @brief      fnv32.h file
 */

#ifndef TB_HASH_FNV32_H
#define TB_HASH_FNV32_H

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

/*! make fnv32 hash
 *
 * @param data      the data
 * @param size      the size
 * @param seed      uses this seed if be non-zero
 *
 * @return          the fnv32 value
 */
tt_uint32_t         tt_fnv32_make(tt_byte_t const* data, tt_size_t size, tt_uint32_t seed);

/*! make fnv32 hash from c-string
 *
 * @param cstr      the c-string
 * @param seed      uses this seed if be non-zero
 *
 * @return          the fnv32 value
 */
tt_uint32_t         tt_fnv32_make_from_cstr(tt_char_t const* cstr, tt_uint32_t seed);

/*! make fnv32(1a) hash
 *
 * @param data      the data
 * @param size      the size
 * @param seed      uses this seed if be non-zero
 *
 * @return          the fnv32 value
 */
tt_uint32_t         tt_fnv32_1a_make(tt_byte_t const* data, tt_size_t size, tt_uint32_t seed);

/*! make fnv32(1a) hash from c-string
 *
 * @param cstr      the c-string
 * @param seed      uses this seed if be non-zero
 *
 * @return          the fnv32 value
 */
tt_uint32_t         tt_fnv32_1a_make_from_cstr(tt_char_t const* cstr, tt_uint32_t seed);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif
