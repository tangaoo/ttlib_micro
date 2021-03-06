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
 * trace
 */
#define TT_TRACE_MODULE_NAME          "TTLIB_CONTAINER_VECTOR"
#define TT_TRACE_MODULE_DEBUG         (1)

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "element/element.h"
#include "vector.h"
#include "../platform/port.h"

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

/* //////////////////////////////////////////////////////////////////////////////////////
 * private implementation
 */
static tt_size_t tt_vector_itor_size(tt_iterator_ref_t iterator)
{
    tt_vector_t* vector = (tt_vector_t*)iterator;
    tt_assert(vector);

    return vector->size;
}

static tt_size_t tt_vector_itor_head(tt_iterator_ref_t iterator)
{
    // head
    return 0;
}

static tt_size_t tt_vector_itor_last(tt_iterator_ref_t iterator)
{
    tt_vector_t* vector = (tt_vector_t*)iterator;
    tt_assert(vector);

    // last
    return vector->size ? vector->size -1 : 0;
}

static tt_size_t tt_vector_itor_tail(tt_iterator_ref_t iterator)
{
    tt_vector_t* vector = (tt_vector_t*)iterator;
    tt_assert(vector);

    // tail, must't access
    return vector->size;
}

static tt_size_t tt_vector_itor_next(tt_iterator_ref_t iterator, tt_size_t itor)
{
    tt_vector_t* vector = (tt_vector_t*)iterator;
    tt_assert(vector);

    tt_assert_and_check_return_val(itor < vector->size, vector->size);

    return itor + 1;
}

static tt_size_t tt_vector_itor_prev(tt_iterator_ref_t iterator, tt_size_t itor)
{
    tt_vector_t* vector = (tt_vector_t*)iterator;
    tt_assert(vector);

    tt_assert_and_check_return_val(itor && itor <= vector->size, 0);

    return itor - 1;
}

static tt_pointer_t tt_vector_itor_item(tt_iterator_ref_t iterator, tt_size_t itor)
{
    tt_vector_t* vector = (tt_vector_t*)iterator;
    tt_assert_and_check_return_val(vector && itor < vector->size, tt_null);

    return vector->element.data(&vector->element, vector->data + itor * iterator->step);
}

static tt_void_t tt_vector_itor_copy(tt_iterator_ref_t iterator, tt_size_t itor, tt_cpointer_t data)
{
    tt_vector_t* vector = (tt_vector_t*)iterator;
    tt_assert_and_check_return(vector && itor < vector->size);

    vector->element.copy(&vector->element, vector->data + itor * iterator->step, data); 
}

static tt_int32_t tt_vector_itor_comp(tt_iterator_ref_t iterator, tt_cpointer_t ldata, tt_cpointer_t rdata)
{
    tt_vector_t* vector = (tt_vector_t*)iterator;
    tt_assert(vector && vector->element.comp);

    return vector->element.comp(&vector->element, ldata, rdata);
}

static tt_void_t tt_vector_itor_remove(tt_iterator_ref_t iterator, tt_size_t itor)
{
    tt_vector_t* vector = (tt_vector_t*)iterator;
    tt_assert(vector);

    // remove
    tt_vector_remove((tt_vector_ref_t)vector, itor);
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */

tt_vector_ref_t tt_vector_init(tt_size_t grow, tt_element_t e)
{
    // check
    tt_assert_and_check_return_val(e.size && e.data && e.dupl && e.repl, tt_null);

    // done
    tt_bool_t    ok = tt_false;
    tt_vector_t* vector = tt_null;
    do
    {
        if(!grow) grow = TT_VECTOR_GROW;

        vector = tt_malloc0(sizeof(tt_vector_t));
        tt_assert_and_check_break(vector);

        // init vector
        vector->size = 0;
        vector->maxn = grow;
        vector->grow = grow;
        vector->element = e;
        tt_assert_and_check_break(vector->maxn < TT_VECTOR_MAXN);

        // init iterator operation
        static tt_iterator_op_t op = 
        {
            tt_vector_itor_size,
            tt_vector_itor_head,
            tt_vector_itor_last,
            tt_vector_itor_tail,
            tt_vector_itor_prev,
            tt_vector_itor_next,
            tt_vector_itor_item,
            tt_vector_itor_comp,
            tt_vector_itor_copy,
            tt_vector_itor_remove,
            tt_null
        };
        
        // init itor
        vector->itor.mode = TT_ITERATOR_MODE_FORWARD | TT_ITERATOR_MODE_REVERSE | TT_ITERATOR_MODE_RACCESS | TT_ITERATOR_MODE_MUTABLE;
        vector->itor.priv = tt_null;
        vector->itor.step = e.size;
        vector->itor.op   = &op;

        // make data
        vector->data = tt_nalloc0(e.size, vector->maxn);
        tt_assert_and_check_break(vector->data);

        ok = tt_true;

    } while (0);

    if(!ok) 
    {
        if(vector->data) 
        {
            tt_free(vector->data);
            vector->data = tt_null;
        }
        if(vector) 
        {
            tt_free(vector);
            vector = tt_null;
        }
    }

    return (tt_vector_ref_t)vector; 
}

tt_void_t tt_vector_exit(tt_vector_ref_t self)
{
    tt_vector_t* vector = (tt_vector_t*)self;
    tt_assert_and_check_return(vector);

    // clear data
    tt_vector_clear(self);

    // free data
    if(vector->data) 
    {
        tt_free(vector->data);
        vector->data = tt_null;
    }

    tt_free(vector);
}

tt_void_t tt_vector_clear(tt_vector_ref_t self)
{
    tt_vector_t* vector = (tt_vector_t*)self;
    tt_assert_and_check_return(vector);

    // free vector item
    if(vector->element.nfree) vector->element.nfree(&vector->element, vector->data, vector->size);

    vector->size = 0;
}

tt_pointer_t tt_vector_data(tt_vector_ref_t self)
{
    tt_vector_t* vector = (tt_vector_t*)self;
    tt_assert_and_check_return_val(vector, tt_null);

    return (tt_pointer_t)vector->data;
}

tt_pointer_t tt_vector_head(tt_vector_ref_t self)
{
    return tt_vector_itor_item(self, tt_vector_itor_head(self));
}

tt_pointer_t tt_vector_last(tt_vector_ref_t self)
{
    return tt_vector_itor_item(self, tt_vector_itor_last(self));
}

tt_bool_t tt_vector_resize(tt_vector_ref_t self, tt_size_t size)
{
    tt_vector_t* vector = (tt_vector_t*)self;
    tt_assert_and_check_return_val(vector, tt_false);

    // done
    tt_bool_t ok = tt_false;
    do
    {
        // size < vector's size
        if (size < vector->size)
        {
            if (vector->element.nfree)
                vector->element.nfree(&vector->element, vector->data + size * vector->element.size, vector->size - size);
        }
        // size > vector's maxn
        if (size > vector->maxn)
        {
            tt_size_t maxn = tt_align(size, vector->maxn);
            tt_assert_and_check_break(maxn < TT_VECTOR_MAXN);

            // realloc data
            vector->data = (tt_byte_t *)tt_ralloc(vector->data, maxn * vector->element.size);
            tt_assert_and_check_break(vector->data);

            // must be algin by 4-bytes
            tt_assert_and_check_break(!(((tt_size_t)vector->data) & 3));

            // clear new vector item
            tt_memset(vector->data + vector->size * vector->element.size, 0, (maxn - vector->maxn) * vector->element.size);
            vector->maxn = maxn;
        }

        // update size
        vector->size = size;
        ok = tt_true;
    } while (0);
    
    return ok;
}

tt_void_t tt_vector_copy(tt_vector_ref_t self, tt_vector_ref_t copy)
{
    tt_vector_t* vector = (tt_vector_t*)self;
    tt_vector_t const* vector_copy = (tt_vector_t*)copy;
    tt_assert_and_check_return(vector && vector_copy);

    // done
    do
    {
        // check element
        tt_assert_and_check_break(vector->element.size == vector_copy->element.size);
        tt_assert_and_check_break(vector->element.type == vector_copy->element.type);

        // null? 
        if(!vector_copy->size)
        {
            tt_vector_clear(self);
            break;
        }
        
        if(vector_copy->size > vector->size) tt_vector_resize(self, vector_copy->size);

        // tt_assert_and_check_break(vector->data && vector_copy->data && vector->size >= vector_copy->size);
        tt_memcpy(vector->data, vector_copy->data, vector_copy->size * vector_copy->element.size);
        
        // update size
        vector->size = vector_copy->size;

    } while (0);

    return;
}

tt_void_t tt_vector_insert_prev(tt_vector_ref_t self, tt_size_t itor, tt_cpointer_t data)
{
    tt_vector_t* vector = (tt_vector_t*)self;
    tt_assert_and_check_return(vector && vector->data && vector->element.size && itor <= vector->size);

    tt_size_t osize = vector->size;
    // resizett
    if(!tt_vector_resize(self, osize + 1))
    {
        tt_trace_d("vector resize failed");
        return;        
    }

    // memmov
    if(itor != osize) tt_memmov(vector->data + (itor + 1) * vector->element.size, 
                                vector->data + itor * vector->element.size, (osize - itor) * vector->element.size);

    vector->element.dupl(&vector->element, vector->data + itor * vector->element.size, data);
}

tt_void_t tt_vector_insert_next(tt_vector_ref_t self, tt_size_t itor, tt_cpointer_t data)
{
    tt_vector_insert_prev(self, tt_iterator_next(self, itor), data);
}

tt_void_t tt_vector_insert_head(tt_vector_ref_t self, tt_cpointer_t data)
{
    tt_vector_insert_prev(self, tt_iterator_head(self), data);
}

tt_void_t tt_vector_insert_tail(tt_vector_ref_t self, tt_cpointer_t data)
{
    tt_vector_insert_prev(self, tt_iterator_tail(self), data);
}

tt_void_t tt_vector_replace(tt_vector_ref_t self, tt_size_t itor, tt_cpointer_t data)
{
    tt_vector_t* vector = (tt_vector_t*)self;
    tt_assert_and_check_return(vector && vector->data && vector->element.size && itor < vector->size);

    if(vector->element.repl)
        vector->element.repl(&vector->element, vector->data + itor * vector->element.size, data);
}

tt_void_t tt_vector_replace_head(tt_vector_ref_t self, tt_cpointer_t data)
{
    tt_vector_replace(self, tt_iterator_head(self), data);
}

tt_void_t tt_vector_replace_last(tt_vector_ref_t self, tt_cpointer_t data)
{
    tt_vector_replace(self, tt_iterator_last(self), data);
}

tt_void_t tt_vector_remove(tt_vector_ref_t self, tt_size_t itor)
{
    tt_vector_t* vector = (tt_vector_t*)self;
    tt_assert_and_check_return(vector && vector->data && vector->element.size && itor < vector->size);

    // free item
    if(vector->element.free)
        vector->element.free(&vector->element, vector->data + itor * vector->element.size);

    tt_size_t osize = vector->size;

    // memmov
    if(itor != tt_iterator_last(self)) 
        tt_memmov(vector->data + itor * vector->element.size, 
                  vector->data + (itor + 1) * vector->element.size, (osize - itor -1) * vector->element.size);

    // update size
    vector->size--;
}
tt_void_t tt_vector_remove_head(tt_vector_ref_t self)
{
    tt_vector_remove(self, tt_iterator_head(self));
}

tt_void_t tt_vector_remove_last(tt_vector_ref_t self)
{
    tt_vector_remove(self, tt_iterator_last(self));
}

tt_size_t tt_vector_size(tt_vector_ref_t self)
{
    tt_vector_t* vector = (tt_vector_t*)self;
    tt_assert_and_check_return_val(vector, 0);

    return vector->size;
}

tt_size_t tt_vector_grow(tt_vector_ref_t self)
{
    tt_vector_t* vector = (tt_vector_t*)self;
    tt_assert_and_check_return_val(vector, 0);

    return vector->grow;
}

tt_size_t tt_vector_maxn(tt_vector_ref_t self)
{
    tt_vector_t* vector = (tt_vector_t*)self;
    tt_assert_and_check_return_val(vector, 0);

    return vector->maxn;
}
