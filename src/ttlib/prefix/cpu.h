#ifndef _PREFIC_CUP_H_
#define _PREFIC_CUP_H_

/// 64 bit
#define TT_CPU_BIT_64          0
#define TT_CPU_BIT_32          1

/// CUP shift
#if TT_CPU_BIT_64
#   define TT_CPU_SHIFT        (6)
#   define TT_CPU_BITSIZE      (64)
#   define TT_CPU_BITBYTE      (8)
#else // 32bit
#   define TT_CPU_SHIFT        (5)
#   define TT_CPU_BITSIZE      (32)
#   define TT_CPU_BITBYTE      (4)
#endif


#endif

