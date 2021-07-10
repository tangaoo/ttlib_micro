/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       hash.h
 * @ingroup    hash
 * @author     tango
 * @date       2021-07-10 
 * @brief      hash.h file
 */

#ifndef TT_CONTAINER_ELEMENT_HASH_H
#define TT_CONTAINER_ELEMENT_HASH_H

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

/* compute the uint8 hash
 *
 * @param value     the value
 * @param mask      the mask. @note mask usually be (pow2 -1)
 * @param index     the hash func index
 *
 * @return          the hash value
 */
tt_size_t           tt_element_hash_uint8(tt_uint8_t value, tt_size_t mask, tt_size_t index);

/* compute the uint16 hash
 *
 * @param value     the value
 * @param mask      the mask. @note mask usually be (pow2 -1)
 * @param index     the hash func index
 *
 * @return          the hash value
 */
tt_size_t           tt_element_hash_uint16(tt_uint16_t value, tt_size_t mask, tt_size_t index);

/* compute the uint32 hash
 *
 * @param value     the value
 * @param mask      the mask. @note mask usually be (pow2 -1)
 * @param index     the hash func index
 *
 * @return          the hash value
 */
tt_size_t           tt_element_hash_uint32(tt_uint32_t value, tt_size_t mask, tt_size_t index);

/* compute the uint64 hash
 *
 * @param value     the value
 * @param mask      the mask. @note mask usually be (pow2 -1)
 * @param index     the hash func index
 *
 * @return          the hash value
 */
tt_size_t           tt_element_hash_uint64(tt_uint64_t value, tt_size_t mask, tt_size_t index);

/* compute the data hash
 *
 * @param data      the data
 * @param size      the size
 * @param mask      the mask. @note mask usually be (pow2 -1)
 * @param index     the hash func index
 *
 * @return          the hash value
 */
tt_size_t           tt_element_hash_data(tt_byte_t const* data, tt_size_t size, tt_size_t mask, tt_size_t index);

/* compute the cstring hash
 *
 * @param cstr      the cstring
 * @param mask      the mask. @note mask usually be (pow2 -1)
 * @param index     the hash func index
 *
 * @return          the hash value
 */
tt_size_t           tt_element_hash_cstr(tt_char_t const* cstr, tt_size_t mask, tt_size_t index);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif
