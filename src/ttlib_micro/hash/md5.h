/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       md5.h
 * @ingroup    hash
 * @author     tango
 * @date       2021-07-10 
 * @brief      md5.h file
 */

#ifndef TT_HASH_MD5_H
#define TT_HASH_MD5_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

// data structure for md5 (message data) computation
typedef struct __tt_md5_t
{
    tt_uint32_t     i[2];       //!< number of _bits_ handled mod 2^64
    tt_uint32_t     sp[4];      //!< scratch buffer
    tt_byte_t       ip[64];     //!< input buffer
    tt_byte_t       data[16];   //!< actual data after tt_md5_exit call

}tt_md5_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! init md5
 *
 * @param md5           the md5
 * @param pseudo_rand   the pseudo rand
 */
tt_void_t               tt_md5_init(tt_md5_t* md5, tt_uint32_t pseudo_rand);

/*! exit md5
 *
 * @param md5           the md5
 * @param data          the data
 * @param size          the size
 */
tt_void_t               tt_md5_exit(tt_md5_t* md5, tt_byte_t* data, tt_size_t size);

/*! spak md5
 *
 * @param md5           the md5
 * @param data          the data
 * @param size          the size
 */
tt_void_t               tt_md5_spak(tt_md5_t* md5, tt_byte_t const* data, tt_size_t size);

/*! make md5
 *
 * @param ib            the input data
 * @param in            the input size
 * @param ob            the output data
 * @param on            the output size
 *
 * @return              the real size
 */
tt_size_t               tt_md5_make(tt_byte_t const* ib, tt_size_t in, tt_byte_t* ob, tt_size_t on);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif

