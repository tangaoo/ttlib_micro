/*
 * @Copyright (C) 2019-2020, TTLIB
 * @file       mix.h
 * @ingroup    utils
 * @author     tango
 * @date       2020-11-19 
 * @brief      mix.h file
 */

#ifndef TT_UTILS_MIX_H
#define TT_UTILS_MIX_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */
typedef enum {
    // little endian
    TT_LITTLE_ENDIAN = 0, 

    // big endian
    TT_BIG_ENDIAN

}tt_cpu_endian_e;

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! env is little endian?
 *
 * @param             void 
 *
 * @return            tt_true or tt_false 
 */
tt_bool_t tt_little_endian(tt_void_t);


#endif
