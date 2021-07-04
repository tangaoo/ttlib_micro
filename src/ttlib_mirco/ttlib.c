
/*
 * @Copyright (C) 2019-2021, TTLIB
 * @file       ttlib.c
 * @ingroup    ttlib
 * @author     tango
 * @date       2020-11-19 
 * @brief      ttlib.c file
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * trace macro
 */
#define TT_TRACE_MODULE_NAME     "ttlib"
#define TT_TRACE_DEBUG           (1)

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "ttlib.h"

// the ttlib version
static const char* version = "v0.1.2";

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tt_bool_t tt_lib_init(tt_handle_t priv)
{
	tt_bool_t ret = tt_false;
	
	tt_trace_raw("********************************************\n");

	/// done
	do{
		/// trace init
		if(!tt_trace_init()) break;

		tt_trace_raw("ttlib version(%s)\n", version);

		// detect compiler and print
#ifdef TT_COMPILER_IS_GCC
		tt_trace_raw("compiler is gcc\n");
#elif defined TT_COMPILER_IS_MSVC 
		tt_trace_raw("compiler is msvc\n");
#elif defined TT_COMPILER_IS_CLANG
		tt_trace_raw("compiler is clang\n");
#elif defined TT_COMPILER_IS_DSP
		tt_trace_raw("compiler is dsp\n");
#else
		tt_trace_raw("compiler is unkonwn\n");
#endif

		// detect cpu endian
		if(tt_little_endian() == TT_LITTLE_ENDIAN) tt_trace_raw("litter endian\n");
		else if(tt_little_endian() == TT_BIG_ENDIAN) tt_trace_raw("big endian\n");
		else tt_trace_w("wrong endian");

		ret = tt_true;
	} while (0);
	
	if(!ret) tt_trace_e("ttlib init error!!!");

	tt_trace_raw("********************************************\n");

	return ret;
}

tt_void_t tt_lib_exit(tt_void_t)
{
	/// trace
	tt_trace_exit();
}