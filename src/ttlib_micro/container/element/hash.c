/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       hash.c
 * @ingroup    element
 * @author     tango
 * @date       2021-07-10 
 * @brief      hash.c file
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include <string.h>
#include "hash.h"
#include "../../hash/hash.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * data hash implementation
 */
static tt_size_t tt_element_hash_data_func_0(tt_byte_t const* data, tt_size_t size)
{
    return tt_bkdr_make(data, size, 0);
}
static tt_size_t tt_element_hash_data_func_1(tt_byte_t const* data, tt_size_t size)
{
    return tt_fnv32_1a_make(data, size, 0);
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * cstr hash implementation
 */
static tt_size_t tt_element_hash_cstr_func_0(tt_char_t const* data)
{
    return tt_bkdr_make_from_cstr(data, 0);
}
static tt_size_t tt_element_hash_cstr_func_1(tt_char_t const* data)
{
    return tt_fnv32_1a_make_from_cstr(data, 0);
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * uint8 hash implementation
 */
static tt_size_t tt_element_hash_uint8_func_0(tt_uint8_t value)
{
    return (tt_size_t)value;
}
static tt_size_t tt_element_hash_uint8_func_1(tt_uint8_t value)
{
    return (tt_size_t)(((tt_uint64_t)(value) * 2654435761ul) >> 16);
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * uint16 hash implementation
 */
static tt_size_t tt_element_hash_uint16_func_0(tt_uint16_t value)
{
    return (tt_size_t)(((tt_uint64_t)(value) * 2654435761ul) >> 16);
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * uint32 hash implementation
 */
static tt_size_t tt_element_hash_uint32_func_0(tt_uint32_t value)
{
    return (tt_size_t)(((tt_uint64_t)(value) * 2654435761ul) >> 16);
}
static tt_size_t tt_element_hash_uint32_func_1(tt_uint32_t value)
{
    // Bob Jenkins' 32 bit integer hash function
    value = (value + 0x7ed55d16) + (value << 12);
    value = (value ^ 0xc761c23c) ^ (value >> 19);
    value = (value + 0x165667b1) + (value << 5);
    value = (value + 0xd3a2646c) ^ (value << 9);
    value = (value + 0xfd7046c5) + (value << 3);
    value = (value ^ 0xb55a4f09) ^ (value >> 16);
    return value;
}
static tt_size_t tt_element_hash_uint32_func_2(tt_uint32_t value)
{
    // Tomas Wang
    value = ~value + (value << 15);
    value = value ^ (value >> 12);
    value = value + (value << 2);
    value = value ^ (value >> 4);
    value = value * 2057;
    value = value ^ (value >> 16);
    return value;
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * uint64 hash implementation
 */
static tt_size_t tt_element_hash_uint64_func_0(tt_uint64_t value)
{
    return (tt_size_t)((value * 2654435761ul) >> 16);
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tt_size_t tt_element_hash_uint8(tt_uint8_t value, tt_size_t mask, tt_size_t index)
{
    // check
    tt_assert_and_check_return_val(mask, 0);

    // for optimization
    if (index < 2)
    {
        // the func
        static tt_size_t (*s_func[])(tt_uint8_t) =
        {
            tt_element_hash_uint8_func_0
        ,   tt_element_hash_uint8_func_1
        };
        tt_assert_and_check_return_val(index < tt_arrayn(s_func), 0);

        // done
        return s_func[index](value) & mask;
    }

    // using uint32 hash
    tt_uint32_t v = (tt_uint32_t)value;
    return tt_element_hash_uint32(v | (v << 8) | (v << 16) | (v << 24), mask, index - 1);
}
tt_size_t tt_element_hash_uint16(tt_uint16_t value, tt_size_t mask, tt_size_t index)
{
    // check
    tt_assert_and_check_return_val(mask, 0);

    // for optimization
    if (index < 1)
    {
        // the func
        static tt_size_t (*s_func[])(tt_uint16_t) =
        {
            tt_element_hash_uint16_func_0
        };
        tt_assert_and_check_return_val(index < tt_arrayn(s_func), 0);

        // done
        return s_func[index](value) & mask;
    }

    // using uint32 hash
    tt_uint32_t v = (tt_uint32_t)value;
    return tt_element_hash_uint32(v | (v << 16), mask, index);
}
tt_size_t tt_element_hash_uint32(tt_uint32_t value, tt_size_t mask, tt_size_t index)
{
    // check
    tt_assert_and_check_return_val(mask, 0);

    // for optimization
    if (index < 3)
    {
        // the func
        static tt_size_t (*s_func[])(tt_uint32_t) =
        {
            tt_element_hash_uint32_func_0
        ,   tt_element_hash_uint32_func_1
        ,   tt_element_hash_uint32_func_2
        };
        tt_assert_and_check_return_val(index < tt_arrayn(s_func), 0);

        // done
        return s_func[index](value) & mask;
    }

    // done
    return tt_element_hash_data((tt_byte_t const*)&value, sizeof(tt_uint32_t), mask, index - 3);
}
tt_size_t tt_element_hash_uint64(tt_uint64_t value, tt_size_t mask, tt_size_t index)
{
    // for optimization
    if (index < 1)
    {
        // the func
        static tt_size_t (*s_func[])(tt_uint64_t) =
        {
            tt_element_hash_uint64_func_0
        };
        tt_assert_and_check_return_val(index < tt_arrayn(s_func), 0);

        // done
        return s_func[index](value) & mask;
    }

    // using the uint32 hash
    tt_size_t hash0 = tt_element_hash_uint32((tt_uint32_t)value, mask, index);
    tt_size_t hash1 = tt_element_hash_uint32((tt_uint32_t)(value >> 32), mask, index);
    return ((hash0 ^ hash1) & mask);
}
tt_size_t tt_element_hash_data(tt_byte_t const* data, tt_size_t size, tt_size_t mask, tt_size_t index)
{
    // check
    tt_assert_and_check_return_val(data && size && mask, 0);

    // the func
    static tt_size_t (*s_func[])(tt_byte_t const* , tt_size_t) =
    {
        tt_element_hash_data_func_0
    ,   tt_element_hash_data_func_1
    };
    tt_assert_and_check_return_val(index < tt_arrayn(s_func), 0);

    // done
    return s_func[index](data, size) & mask;
}
tt_size_t tt_element_hash_cstr(tt_char_t const* cstr, tt_size_t mask, tt_size_t index)
{
    // check
    tt_assert_and_check_return_val(cstr && mask, 0);

    // for optimization
    if (index < 2)
    {
        // the func
        static tt_size_t (*s_func[])(tt_char_t const*) =
        {
            tt_element_hash_cstr_func_0
        ,   tt_element_hash_cstr_func_1
        };
        tt_assert_and_check_return_val(index < tt_arrayn(s_func), 0);

        // done
        return s_func[index](cstr) & mask;
    }

    // using the data hash
    return tt_element_hash_data((tt_byte_t const*)cstr, strlen(cstr), mask, index);
}
