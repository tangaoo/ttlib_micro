/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       crc16.h
 * @ingroup    hash
 * @author     tango
 * @date       2021-07-10 
 * @brief      crc16.h file
 */

#ifndef TT_HASH_CRC16_H
#define TT_HASH_CRC16_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// encode value
#define tt_crc16_make_value(mode, crc, value)       tt_crc16_make(mode, crc, (tt_byte_t const*)&(value), sizeof(value))

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! make crc16 (ANSI)
 *
 * @param data      the input data
 * @param size      the input size
 * @param seed      uses this seed if be non-zero
 *
 * @return          the crc value
 */
tt_uint16_t         tt_crc16_make(tt_byte_t const* data, tt_size_t size, tt_uint16_t seed);

/*! make crc16 (ANSI) for cstr
 *
 * @param cstr      the input cstr
 * @param seed      uses this seed if be non-zero
 *
 * @return          the crc value
 */
tt_uint16_t         tt_crc16_make_from_cstr(tt_char_t const* cstr, tt_uint16_t seed);

/*! make crc16 (CCITT)
 *
 * @param data      the input data
 * @param size      the input size
 * @param seed      uses this seed if be non-zero
 *
 * @return          the crc value
 */
tt_uint16_t         tt_crc16_ccitt_make(tt_byte_t const* data, tt_size_t size, tt_uint16_t seed);

/*! make crc16 (CCITT) for cstr
 *
 * @param cstr      the input cstr
 * @param seed      uses this seed if be non-zero
 *
 * @return          the crc value
 */
tt_uint16_t         tt_crc16_ccitt_make_from_cstr(tt_char_t const* cstr, tt_uint16_t seed);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif

