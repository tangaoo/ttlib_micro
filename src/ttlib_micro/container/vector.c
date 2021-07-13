/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       vector.c
 * @ingroup    container
 * @author     tango
 * @date       2021-07-11 
 * @brief      vector.c file
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "element/element.h"
#include "vector.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

// the vector grow
#define TT_VECTOR_GROW          64              

// the vector maxn
#define TT_VECTOR_MAXN          (1 << 16)              

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */
typedef struct __tt_vector_t
{
    // iterator
    tt_iterator_t       itor;

    // the vector data
    tt_byte_t*          data;

    // the vector size
    tt_size_t           size;

    // the vector grow
    tt_size_t           grow;

    // the vector manx
    tt_size_t           maxn;

    // the element
    tt_element_t        element;

}tt_vector_t;

tt_vector_ref_t tt_vector_init(tt_size_t grow, tt_element_t e);

tt_void_t tt_vector_exit(tt_vector_ref_t vector);

tt_pointer_t tt_vector_data(tt_vector_ref_t vector);

tt_pointer_t tt_vector_head(tt_vector_ref_t vector);

tt_pointer_t tt_vector_last(tt_vector_ref_t vector);

tt_bool_t tt_vector_resize(tt_vector_ref_t vector, tt_size_t size);

tt_void_t tt_vector_clear(tt_vector_ref_t vector);

tt_void_t tt_vector_copy(tt_vector_ref_t vector, tt_vector_ref_t copy);

tt_void_t tt_vector_insert_prev(tt_vector_ref_t vector, tt_size_t itor, tt_cpointer_t data);

tt_void_t tt_vector_insert_next(tt_vector_ref_t vector, tt_size_t itor, tt_cpointer_t data);

tt_void_t tt_vector_insert_head(tt_vector_ref_t vector, tt_cpointer_t data);

tt_void_t tt_vector_insert_tail(tt_vector_ref_t vector, tt_cpointer_t data);

tt_void_t tt_vector_replace(tt_vector_ref_t vector, tt_size_t itor, tt_cpointer_t data);

tt_void_t tt_vector_replace_head(tt_vector_ref_t vector, tt_cpointer_t data);

tt_void_t tt_vector_replace_last(tt_vector_ref_t vector, tt_cpointer_t data);

tt_void_t tt_vector_remove(tt_vector_ref_t vector, tt_size_t itor);

tt_void_t tt_vector_remove_head(tt_vector_ref_t vector);

tt_void_t tt_vector_remove_last(tt_vector_ref_t vector);

tt_size_t tt_vector_size(tt_vector_ref_t vector);

tt_size_t tt_vector_grow(tt_vector_ref_t vector);

tt_size_t tt_vector_maxn(tt_vector_ref_t vector);
