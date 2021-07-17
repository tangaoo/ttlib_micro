/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       str.c
 * @ingroup    element
 * @author     tango
 * @date       2021-07-10 
 * @brief      str.c file
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "element.h"
#include "hash.h"
#include "../../platform/port.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * private interfaces
 */
static tt_size_t tt_element_str_hash(tt_element_ref_t e, tt_cpointer_t data, tt_size_t mask, tt_size_t index)
{
    return tt_element_hash_cstr((tt_char_t const *)data, mask, index);
}

static tt_long_t tt_element_str_comp(tt_element_ref_t e, tt_cpointer_t ldata, tt_cpointer_t rdata)
{
    tt_assert_and_check_return_val(e && ldata && rdata, 0);

    // compare it
    return e->flag ? tt_strcmp((tt_char_t const *)ldata, (tt_char_t const *)rdata) : tt_stricmp((tt_char_t const *)ldata, (tt_char_t const *)rdata);
}

static tt_pointer_t tt_element_str_data(tt_element_ref_t e, tt_cpointer_t buff)
{
    /// check
    tt_assert_and_check_return_val(buff, tt_null);

    return *((tt_pointer_t*)buff);
}

static tt_char_t const * tt_element_str_cstr(tt_element_ref_t e, tt_cpointer_t data, tt_char_t *str, tt_size_t maxn)
{
    return (tt_char_t const *)data;
}

static tt_void_t tt_element_str_free(tt_element_ref_t e, tt_pointer_t buff)
{
    /// check
    tt_assert_and_check_return(e && buff);

    tt_pointer_t cstr =  *((tt_pointer_t*)buff);
    if(cstr)
    {
        tt_free(cstr);

        // clear it
        *((tt_pointer_t*)buff) = tt_null;
    }
}

static tt_void_t tt_element_str_dupl(tt_element_ref_t e, tt_pointer_t buff, tt_cpointer_t data)
{
    // check
    tt_assert_and_check_return(e && buff);

    // duplicate it
    if(data) *((tt_pointer_t**)buff) = (tt_pointer_t)tt_strdup((tt_char_t const*)data);
    else *((tt_pointer_t**)buff) = tt_null;
}

static tt_void_t tt_element_str_repl(tt_element_ref_t e, tt_pointer_t buff, tt_cpointer_t data)
{
    // check
    tt_assert_and_check_return(e && e->dupl && buff);

    // free it
    if(e->free) e->free(e, buff);

    // dupl it
    e->dupl(e, buff, data);
}

static tt_void_t tt_element_str_copy(tt_element_ref_t e, tt_pointer_t buff, tt_cpointer_t data)
{
    // check
    tt_assert_and_check_return(e && buff);

    *((tt_cpointer_t*)buff) = data;
}

static tt_void_t tt_element_str_nfree(tt_element_ref_t e, tt_pointer_t buff, tt_size_t size)
{
    // check
    tt_assert_and_check_return(e && buff);

    // free
    if(e->free)
    {
        tt_size_t n = size;
        while(n--) e->free(e, (tt_char_t*)buff + n * sizeof(tt_char_t*));
    }

    if(size) memset(buff, 0, size * sizeof(tt_char_t*));
}

static tt_void_t tt_element_str_ncopy(tt_element_ref_t e, tt_pointer_t buff, tt_cpointer_t data, tt_size_t size)
{
    // check
    tt_assert_and_check_return(buff);

    // memset
    if(size) tt_memset_ptr(buff, data, size); 
}

static tt_void_t tt_element_str_ndupl(tt_element_ref_t e, tt_pointer_t buff, tt_cpointer_t data, tt_size_t size)
{
    // check
    tt_assert_and_check_return(e && buff);

    // duplicate 
    if(e->dupl) while(size--) e->dupl(e, (tt_byte_t*)buff + size * sizeof(tt_char_t*), data); 
}

static tt_void_t tt_element_str_nrepl(tt_element_ref_t e, tt_pointer_t buff, tt_cpointer_t data, tt_size_t size)
{
    // check
    tt_assert_and_check_return(e && buff);

    // replace
    if(e->repl) while(size--) e->repl(e, (tt_byte_t*)buff + size * sizeof(tt_char_t*), data); 
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */
tt_element_t        tt_element_str(tt_bool_t bcase)
{
    tt_element_t e = {0};

    e.type   = TT_ELEMENT_TYPE_STR;
    e.flag   = !!(bcase);
    e.size   = sizeof(tt_char_t*);
    e.hash   = tt_element_str_hash;
    e.comp   = tt_element_str_comp;
    e.data   = tt_element_str_data;
    e.cstr   = tt_element_str_cstr;
    e.free   = tt_element_str_free;
    e.dupl   = tt_element_str_dupl;
    e.repl   = tt_element_str_repl;
    e.copy   = tt_element_str_copy;
    e.nfree  = tt_element_str_nfree;
    e.ndupl  = tt_element_str_ndupl;
    e.nrepl  = tt_element_str_nrepl;
    e.ncopy  = tt_element_str_ncopy;

    return e;
}