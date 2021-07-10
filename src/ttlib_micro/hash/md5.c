/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       md5.c
 * @ingroup    hash
 * @author     tango
 * @date       2021-07-10 
 * @brief      md5.c file
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include <string.h>
#include "md5.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// TT_MD5_F, TT_MD5_G and TT_MD5_H are basic MD5 functions: selection, majority, parity
#define TT_MD5_F(x, y, z)   (((x) & (y)) | ((~x) & (z)))
#define TT_MD5_G(x, y, z)   (((x) & (z)) | ((y) & (~z)))
#define TT_MD5_H(x, y, z)   ((x) ^ (y) ^ (z))
#define TT_MD5_I(x, y, z)   ((y) ^ ((x) | (~z)))

// TT_MD5_ROTATE_LEFT rotates x left n bits */
#define TT_MD5_ROTATE_LEFT(x, n)    (((x) << (n)) | ((x) >> (32 - (n))))

// TT_MD5_FF, TT_MD5_GG, TT_MD5_HH, and TT_MD5_II transformations for rounds 1, 2, 3, and 4
// Rotation is separate from addition to prevent recomputation
#define TT_MD5_FF(a, b, c, d, x, s, ac) {(a) += TT_MD5_F ((b), (c), (d)) + (x) + (tt_uint32_t)(ac); (a) = TT_MD5_ROTATE_LEFT ((a), (s)); (a) += (b); }
#define TT_MD5_GG(a, b, c, d, x, s, ac) {(a) += TT_MD5_G ((b), (c), (d)) + (x) + (tt_uint32_t)(ac); (a) = TT_MD5_ROTATE_LEFT ((a), (s)); (a) += (b); }
#define TT_MD5_HH(a, b, c, d, x, s, ac) {(a) += TT_MD5_H ((b), (c), (d)) + (x) + (tt_uint32_t)(ac); (a) = TT_MD5_ROTATE_LEFT ((a), (s)); (a) += (b); }
#define TT_MD5_II(a, b, c, d, x, s, ac) {(a) += TT_MD5_I ((b), (c), (d)) + (x) + (tt_uint32_t)(ac); (a) = TT_MD5_ROTATE_LEFT ((a), (s)); (a) += (b); }

// Constants for transformation
#define TT_MD5_S11 7  // Round 1
#define TT_MD5_S12 12
#define TT_MD5_S13 17
#define TT_MD5_S14 22
#define TT_MD5_S21 5  // Round 2
#define TT_MD5_S22 9
#define TT_MD5_S23 14
#define TT_MD5_S24 20
#define TT_MD5_S31 4  // Round 3
#define TT_MD5_S32 11
#define TT_MD5_S33 16
#define TT_MD5_S34 23
#define TT_MD5_S41 6  // Round 4
#define TT_MD5_S42 10
#define TT_MD5_S43 15
#define TT_MD5_S44 21

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */

/* Padding */
static tt_byte_t g_md5_padding[64] =
{
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaion
 */

// basic md5 step. the sp based on ip
static tt_void_t tt_md5_transform(tt_uint32_t* sp, tt_uint32_t* ip)
{
    // check
    tt_assert_and_check_return(sp && ip);

    // init
    tt_uint32_t a = sp[0], b = sp[1], c = sp[2], d = sp[3];

    // round 1
    TT_MD5_FF ( a, b, c, d, ip[ 0], TT_MD5_S11, (tt_uint32_t) 3614090360u); /* 1 */
    TT_MD5_FF ( d, a, b, c, ip[ 1], TT_MD5_S12, (tt_uint32_t) 3905402710u); /* 2 */
    TT_MD5_FF ( c, d, a, b, ip[ 2], TT_MD5_S13, (tt_uint32_t)  606105819u); /* 3 */
    TT_MD5_FF ( b, c, d, a, ip[ 3], TT_MD5_S14, (tt_uint32_t) 3250441966u); /* 4 */
    TT_MD5_FF ( a, b, c, d, ip[ 4], TT_MD5_S11, (tt_uint32_t) 4118548399u); /* 5 */
    TT_MD5_FF ( d, a, b, c, ip[ 5], TT_MD5_S12, (tt_uint32_t) 1200080426u); /* 6 */
    TT_MD5_FF ( c, d, a, b, ip[ 6], TT_MD5_S13, (tt_uint32_t) 2821735955u); /* 7 */
    TT_MD5_FF ( b, c, d, a, ip[ 7], TT_MD5_S14, (tt_uint32_t) 4249261313u); /* 8 */
    TT_MD5_FF ( a, b, c, d, ip[ 8], TT_MD5_S11, (tt_uint32_t) 1770035416u); /* 9 */
    TT_MD5_FF ( d, a, b, c, ip[ 9], TT_MD5_S12, (tt_uint32_t) 2336552879u); /* 10 */
    TT_MD5_FF ( c, d, a, b, ip[10], TT_MD5_S13, (tt_uint32_t) 4294925233u); /* 11 */
    TT_MD5_FF ( b, c, d, a, ip[11], TT_MD5_S14, (tt_uint32_t) 2304563134u); /* 12 */
    TT_MD5_FF ( a, b, c, d, ip[12], TT_MD5_S11, (tt_uint32_t) 1804603682u); /* 13 */
    TT_MD5_FF ( d, a, b, c, ip[13], TT_MD5_S12, (tt_uint32_t) 4254626195u); /* 14 */
    TT_MD5_FF ( c, d, a, b, ip[14], TT_MD5_S13, (tt_uint32_t) 2792965006u); /* 15 */
    TT_MD5_FF ( b, c, d, a, ip[15], TT_MD5_S14, (tt_uint32_t) 1236535329u); /* 16 */

    // round 2
    TT_MD5_GG ( a, b, c, d, ip[ 1], TT_MD5_S21, (tt_uint32_t) 4129170786u); /* 17 */
    TT_MD5_GG ( d, a, b, c, ip[ 6], TT_MD5_S22, (tt_uint32_t) 3225465664u); /* 18 */
    TT_MD5_GG ( c, d, a, b, ip[11], TT_MD5_S23, (tt_uint32_t)  643717713u); /* 19 */
    TT_MD5_GG ( b, c, d, a, ip[ 0], TT_MD5_S24, (tt_uint32_t) 3921069994u); /* 20 */
    TT_MD5_GG ( a, b, c, d, ip[ 5], TT_MD5_S21, (tt_uint32_t) 3593408605u); /* 21 */
    TT_MD5_GG ( d, a, b, c, ip[10], TT_MD5_S22, (tt_uint32_t)   38016083u); /* 22 */
    TT_MD5_GG ( c, d, a, b, ip[15], TT_MD5_S23, (tt_uint32_t) 3634488961u); /* 23 */
    TT_MD5_GG ( b, c, d, a, ip[ 4], TT_MD5_S24, (tt_uint32_t) 3889429448u); /* 24 */
    TT_MD5_GG ( a, b, c, d, ip[ 9], TT_MD5_S21, (tt_uint32_t)  568446438u); /* 25 */
    TT_MD5_GG ( d, a, b, c, ip[14], TT_MD5_S22, (tt_uint32_t) 3275163606u); /* 26 */
    TT_MD5_GG ( c, d, a, b, ip[ 3], TT_MD5_S23, (tt_uint32_t) 4107603335u); /* 27 */
    TT_MD5_GG ( b, c, d, a, ip[ 8], TT_MD5_S24, (tt_uint32_t) 1163531501u); /* 28 */
    TT_MD5_GG ( a, b, c, d, ip[13], TT_MD5_S21, (tt_uint32_t) 2850285829u); /* 29 */
    TT_MD5_GG ( d, a, b, c, ip[ 2], TT_MD5_S22, (tt_uint32_t) 4243563512u); /* 30 */
    TT_MD5_GG ( c, d, a, b, ip[ 7], TT_MD5_S23, (tt_uint32_t) 1735328473u); /* 31 */
    TT_MD5_GG ( b, c, d, a, ip[12], TT_MD5_S24, (tt_uint32_t) 2368359562u); /* 32 */

    // round 3
    TT_MD5_HH ( a, b, c, d, ip[ 5], TT_MD5_S31, (tt_uint32_t) 4294588738u); /* 33 */
    TT_MD5_HH ( d, a, b, c, ip[ 8], TT_MD5_S32, (tt_uint32_t) 2272392833u); /* 34 */
    TT_MD5_HH ( c, d, a, b, ip[11], TT_MD5_S33, (tt_uint32_t) 1839030562u); /* 35 */
    TT_MD5_HH ( b, c, d, a, ip[14], TT_MD5_S34, (tt_uint32_t) 4259657740u); /* 36 */
    TT_MD5_HH ( a, b, c, d, ip[ 1], TT_MD5_S31, (tt_uint32_t) 2763975236u); /* 37 */
    TT_MD5_HH ( d, a, b, c, ip[ 4], TT_MD5_S32, (tt_uint32_t) 1272893353u); /* 38 */
    TT_MD5_HH ( c, d, a, b, ip[ 7], TT_MD5_S33, (tt_uint32_t) 4139469664u); /* 39 */
    TT_MD5_HH ( b, c, d, a, ip[10], TT_MD5_S34, (tt_uint32_t) 3200236656u); /* 40 */
    TT_MD5_HH ( a, b, c, d, ip[13], TT_MD5_S31, (tt_uint32_t)  681279174u); /* 41 */
    TT_MD5_HH ( d, a, b, c, ip[ 0], TT_MD5_S32, (tt_uint32_t) 3936430074u); /* 42 */
    TT_MD5_HH ( c, d, a, b, ip[ 3], TT_MD5_S33, (tt_uint32_t) 3572445317u); /* 43 */
    TT_MD5_HH ( b, c, d, a, ip[ 6], TT_MD5_S34, (tt_uint32_t)   76029189u); /* 44 */
    TT_MD5_HH ( a, b, c, d, ip[ 9], TT_MD5_S31, (tt_uint32_t) 3654602809u); /* 45 */
    TT_MD5_HH ( d, a, b, c, ip[12], TT_MD5_S32, (tt_uint32_t) 3873151461u); /* 46 */
    TT_MD5_HH ( c, d, a, b, ip[15], TT_MD5_S33, (tt_uint32_t)  530742520u); /* 47 */
    TT_MD5_HH ( b, c, d, a, ip[ 2], TT_MD5_S34, (tt_uint32_t) 3299628645u); /* 48 */

    // round 4
    TT_MD5_II ( a, b, c, d, ip[ 0], TT_MD5_S41, (tt_uint32_t) 4096336452u); /* 49 */
    TT_MD5_II ( d, a, b, c, ip[ 7], TT_MD5_S42, (tt_uint32_t) 1126891415u); /* 50 */
    TT_MD5_II ( c, d, a, b, ip[14], TT_MD5_S43, (tt_uint32_t) 2878612391u); /* 51 */
    TT_MD5_II ( b, c, d, a, ip[ 5], TT_MD5_S44, (tt_uint32_t) 4237533241u); /* 52 */
    TT_MD5_II ( a, b, c, d, ip[12], TT_MD5_S41, (tt_uint32_t) 1700485571u); /* 53 */
    TT_MD5_II ( d, a, b, c, ip[ 3], TT_MD5_S42, (tt_uint32_t) 2399980690u); /* 54 */
    TT_MD5_II ( c, d, a, b, ip[10], TT_MD5_S43, (tt_uint32_t) 4293915773u); /* 55 */
    TT_MD5_II ( b, c, d, a, ip[ 1], TT_MD5_S44, (tt_uint32_t) 2240044497u); /* 56 */
    TT_MD5_II ( a, b, c, d, ip[ 8], TT_MD5_S41, (tt_uint32_t) 1873313359u); /* 57 */
    TT_MD5_II ( d, a, b, c, ip[15], TT_MD5_S42, (tt_uint32_t) 4264355552u); /* 58 */
    TT_MD5_II ( c, d, a, b, ip[ 6], TT_MD5_S43, (tt_uint32_t) 2734768916u); /* 59 */
    TT_MD5_II ( b, c, d, a, ip[13], TT_MD5_S44, (tt_uint32_t) 1309151649u); /* 60 */
    TT_MD5_II ( a, b, c, d, ip[ 4], TT_MD5_S41, (tt_uint32_t) 4149444226u); /* 61 */
    TT_MD5_II ( d, a, b, c, ip[11], TT_MD5_S42, (tt_uint32_t) 3174756917u); /* 62 */
    TT_MD5_II ( c, d, a, b, ip[ 2], TT_MD5_S43, (tt_uint32_t)  718787259u); /* 63 */
    TT_MD5_II ( b, c, d, a, ip[ 9], TT_MD5_S44, (tt_uint32_t) 3951481745u); /* 64 */

    sp[0] += a;
    sp[1] += b;
    sp[2] += c;
    sp[3] += d;
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */

// set pseudo_rand to zero for rfc md5 implementation
tt_void_t tt_md5_init(tt_md5_t* md5, tt_uint32_t pseudo_rand)
{
    // check
    tt_assert_and_check_return(md5);

    // init
    md5->i[0] = md5->i[1] = (tt_uint32_t)0;

    // load magic initialization constants
    md5->sp[0] = (tt_uint32_t)0x67452301 + (pseudo_rand * 11);
    md5->sp[1] = (tt_uint32_t)0xefcdab89 + (pseudo_rand * 71);
    md5->sp[2] = (tt_uint32_t)0x98badcfe + (pseudo_rand * 37);
    md5->sp[3] = (tt_uint32_t)0x10325476 + (pseudo_rand * 97);
}

tt_void_t tt_md5_spak(tt_md5_t* md5, tt_byte_t const* data, tt_size_t size)
{
    // check
    tt_assert_and_check_return(md5 && data);

    // init
    tt_uint32_t ip[16];
    tt_size_t   i = 0, ii = 0;

    // compute number of bytes mod 64
    tt_int_t mdi = (tt_int_t)((md5->i[0] >> 3) & 0x3F);

    // update number of bits
    if ((md5->i[0] + ((tt_uint32_t)size << 3)) < md5->i[0]) md5->i[1]++;

    md5->i[0] += ((tt_uint32_t)size << 3);
    md5->i[1] += ((tt_uint32_t)size >> 29);

    while (size--)
    {
        // add new character to buffer, increment mdi
        md5->ip[mdi++] = *data++;

        // transform if necessary
        if (mdi == 0x40)
        {
            for (i = 0, ii = 0; i < 16; i++, ii += 4)
            {
                ip[i] =     (((tt_uint32_t)md5->ip[ii + 3]) << 24)
                        |   (((tt_uint32_t)md5->ip[ii + 2]) << 16)
                        |   (((tt_uint32_t)md5->ip[ii + 1]) << 8)
                        |   ((tt_uint32_t)md5->ip[ii]);
            }

            tt_md5_transform(md5->sp, ip);
            mdi = 0;
        }
    }
}

tt_void_t tt_md5_exit(tt_md5_t* md5, tt_byte_t* data, tt_size_t size)
{
    // check
    tt_assert_and_check_return(md5 && data);

    // init
    tt_uint32_t ip[16];
    tt_int_t    mdi = 0;
    tt_size_t   i = 0;
    tt_size_t   ii = 0;
    tt_size_t   pad_n = 0;

    // save number of bits
    ip[14] = md5->i[0];
    ip[15] = md5->i[1];

    // compute number of bytes mod 64
    mdi = (tt_int_t)((md5->i[0] >> 3) & 0x3F);

    // pad out to 56 mod 64
    pad_n = (mdi < 56) ? (56 - mdi) : (120 - mdi);
    tt_md5_spak (md5, g_md5_padding, pad_n);

    // append length ip bits and transform
    for (i = 0, ii = 0; i < 14; i++, ii += 4)
    {
        ip[i] =     (((tt_uint32_t)md5->ip[ii + 3]) << 24)
                |   (((tt_uint32_t)md5->ip[ii + 2]) << 16)
                |   (((tt_uint32_t)md5->ip[ii + 1]) <<  8)
                |   ((tt_uint32_t)md5->ip[ii]);
    }
    tt_md5_transform (md5->sp, ip);

    // store buffer ip data
    for (i = 0, ii = 0; i < 4; i++, ii += 4)
    {
        md5->data[ii]   = (tt_byte_t)( md5->sp[i]        & 0xff);
        md5->data[ii+1] = (tt_byte_t)((md5->sp[i] >>  8) & 0xff);
        md5->data[ii+2] = (tt_byte_t)((md5->sp[i] >> 16) & 0xff);
        md5->data[ii+3] = (tt_byte_t)((md5->sp[i] >> 24) & 0xff);
    }

    // output
    memcpy(data, md5->data, 16);
}

tt_size_t tt_md5_make(tt_byte_t const* ib, tt_size_t in, tt_byte_t* ob, tt_size_t on)
{
    // check
    tt_assert_and_check_return_val(ib && in && ob && on >= 16, 0);

    // init
    tt_md5_t md5;
    tt_md5_init(&md5, 0);

    // spank
    tt_md5_spak(&md5, ib, in);

    // exit
    tt_md5_exit(&md5, ob, on);

    // ok
    return 16;
}

