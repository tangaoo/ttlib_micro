/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       crc32.h
 * @ingroup    hash
 * @author     tango
 * @date       2021-07-10 
 * @brief      crc32.h file
 */

#ifndef TT_HASH_CRC32_H
#define TT_HASH_CRC32_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// encode value
#define tt_crc32_make_value(mode, crc, value)       tt_crc32_make(mode, crc, (tt_byte_t const*)&(value), sizeof(value))

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! make crc32 (IEEE)
 *
 * @param data      the input data
 * @param size      the input size
 * @param seed      uses this seed if be non-zero
 *
 * @return          the crc value
 */
tt_uint32_t         tt_crc32_make(tt_byte_t const* data, tt_size_t size, tt_uint32_t seed);

/*! make crc32 (IEEE) for cstr
 *
 * @param cstr      the input cstr
 * @param seed      uses this seed if be non-zero
 *
 * @return          the crc value
 */
tt_uint32_t         tt_crc32_make_from_cstr(tt_char_t const* cstr, tt_uint32_t seed);

/*! make crc32 (IEEE LE)
 *
 * @param data      the input data
 * @param size      the input size
 * @param seed      uses this seed if be non-zero
 *
 * @return          the crc value
 */
tt_uint32_t         tt_crc32_le_make(tt_byte_t const* data, tt_size_t size, tt_uint32_t seed);

/*! make crc32 (IEEE LE) for cstr
 *
 * @param cstr      the input cstr
 * @param seed      uses this seed if be non-zero
 *
 * @return          the crc value
 */
tt_uint32_t         tt_crc32_le_make_from_cstr(tt_char_t const* cstr, tt_uint32_t seed);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif

