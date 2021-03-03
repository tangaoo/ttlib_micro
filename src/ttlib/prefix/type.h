/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       type.h
 * @ingroup    prefix
 * @author     tango
 * @date       2020-11-19 
 * @brief      type.h file
 */

#ifndef TT_PREFIX_TYPE_H
#define TT_PREFIX_TYPE_H

/*//////////////////////////////////////////////////////////////////////////////////////
* includes 
*/
#include <stdio.h>
#include "config.h"
#include "cpu.h"
#include "keyword.h"



/*//////////////////////////////////////////////////////////////////////////////////////
* macros
*/

#define tt_true                                    ((tt_bool_t)1)
#define tt_false                                   ((tt_bool_t)0)

//null
#ifdef __cplusplus
#	define tt_null                                 (0)                
#else
#	define tt_null                                 ((tt_pointer_t)0)
#endif

//argument
#ifdef __cplusplus
#	define tt_noarg_t
#else
#	define tt_noarg_t                              tt_void_t
#endif

#if defined(TT_COMPILER_IS_MSVC) || defined(TT_COMPILER_IS_GCC) || defined(TT_COMPILER_IS_CLANG)
/*//////////////////////////////////////////////////////////////////////////////////////
* type
*/
typedef signed int                                 tt_int_t;
typedef unsigned int                               tt_uint_t;
typedef signed short                               tt_short_t;
typedef unsigned short                             tt_ushort_t;
typedef signed char                                tt_int8_t;
typedef unsigned char                              tt_uint8_t;
typedef signed short                               tt_int16_t;
typedef unsigned short                             tt_uint16_t;
typedef signed int                                 tt_int32_t;
typedef unsigned int                               tt_uint32_t;
typedef signed long long                           tt_int64_t;
typedef unsigned long long                         tt_uint64_t;
typedef float                                      tt_f32_t;
typedef double                                     tt_f64_t;
typedef char                                       tt_char_t;
typedef tt_uint8_t                                 tt_byte_t;
typedef tt_int8_t                                  tt_bool_t;
typedef void                                       tt_void_t;
typedef tt_void_t *                                tt_pointer_t;
typedef tt_void_t const *                          tt_cpointer_t;
typedef tt_pointer_t                               tt_handle_t;

/// long and size
#	if defined(TT_COMPILER_IS_MSVC) && defined(TT_CPU_BIT_64)
typedef tt_int64_t                                 tt_long_t;
typedef tt_uint64_t                                tt_ulong_t;
#	else
typedef signed long                                tt_long_t;
typedef unsigned long                              tt_ulong_t;
#	endif
typedef tt_ulong_t                                 tt_size_t;

// hong and hize
typedef tt_int64_t                                 tt_hong_t;
typedef tt_uint64_t                                tt_hize_t;

#elif defined(TT_COMPILER_IS_DSP) 
typedef signed char                                tt_int8_t;
typedef unsigned char                              tt_uint8_t;
typedef signed short                               tt_int16_t;
typedef unsigned short                             tt_uint16_t;
typedef signed int                                 tt_int32_t;
typedef unsigned int                               tt_uint32_t;
typedef signed long long                           tt_int64_t;
typedef unsigned long long                         tt_uint64_t;
typedef float                                      tt_f32_t;
typedef double                                     tt_f64_t;
typedef char                                       tt_char_t;
typedef tt_uint8_t                                 tt_byte_t;
typedef tt_int8_t                                  tt_bool_t;
typedef void                                       tt_void_t;
typedef tt_void_t *                                tt_pointer_t;
typedef tt_void_t const *                          tt_cpointer_t;
typedef tt_pointer_t                               tt_handle_t;
typedef tt_uint32_t                                tt_size_t;
#endif

// the socket type
typedef __tt_typeref__(socket);

// the file type
typedef __tt_typeref__(file);

// the time type
typedef tt_hong_t                                  tt_time_t;

// the suseconds type
typedef tt_long_t                                  tt_susecond_t;

// the timeval type
typedef struct __tt_timeval_t
{
    // the seconds
    tt_time_t       tv_sec;

    // the useconds
    tt_susecond_t   tv_usec;
}tt_timeval_t; 

// the timezone type
typedef struct __tt_timezone_t
{
    // the minutes west of Greenwich
    tt_int_t        tz_minuteswest;

    // the type of dst correction
    tt_int_t        tz_dsttime;
}tt_timezone_t;


#endif