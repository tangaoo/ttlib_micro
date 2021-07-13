/*!The TT Library
 *
 * @Copyright (C) 2019-2021, TTLIB
 *
 * @file       vector.h
 * @ingroup    container
 * @author     tango
 * @date       2021-07-11 
 * @brief      vector.h file
 */

#ifndef TT_CONTAINER_VECTOR_H
#define TT_CONTAINER_VECTOR_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "element/element.h"
#include "iterator.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

/*! the vector ref type
 *
 * <pre>
 * vector: |-----|--------------------------------------------|------|
 *       head                                               last    tail(can't access)
 *
 * performance:
 *
 * insert:
 * insert midd: slow
 * insert head: slow
 * insert tail: fast
 *
 * ninsert:
 * ninsert midd: slow
 * ninsert head: slow
 * ninsert tail: fast
 *
 * remove:
 * remove midd: slow
 * remove head: slow
 * remove last: fast
 *
 * nremove:
 * nremove midd: slow
 * nremove head: slow
 * nremove last: fast
 *
 * iterator:
 * next: fast
 * prev: fast
 * </pre>
 *
 * @note the itor of the same item is mutable
 *
 */
typedef tt_iterator_ref_t tt_vector_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/*! init vector
 *
 * @param grow          the item grow
 * @param e             the element
 *
 * @return              the vector
 */
tt_vector_ref_t         tt_vector_init(tt_size_t grow, tt_element_t e);

/*! exit vector
 *
 * @param vector        the vector
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_exit(tt_vector_ref_t vector);

/*! vector data
 *
 * @param vector        the vector
 *
 * @return              the vector's data
 */
tt_pointer_t            tt_vector_data(tt_vector_ref_t vector);

/*! vector head item
 *
 * @param vector        the vector
 *
 * @return              the vector head item
 */
tt_pointer_t            tt_vector_head(tt_vector_ref_t vector);

/*! vector last item
 *
 * @param vector        the vector
 *
 * @return              the vector last item
 */
tt_pointer_t            tt_vector_last(tt_vector_ref_t vector);

/*! vector resize
 *
 * @param vector        the vector
 * @param size          the vector size
 *
 * @return              tt_true or tt_false
 */
tt_bool_t               tt_vector_resize(tt_vector_ref_t vector, tt_size_t size);

/*! clear vector
 *
 * @param vector        the vector
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_clear(tt_vector_ref_t vector);

/*! copy vector
 *
 * @param vector        the vector
 * @param copy          the copy vector
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_copy(tt_vector_ref_t vector, tt_vector_ref_t copy);

/*! insert the vector prev item
 *
 * @param vector        the vector
 * @param itor          the itor
 * @param data          the data
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_insert_prev(tt_vector_ref_t vector, tt_size_t itor, tt_cpointer_t data);

/*! insert the vector next item
 *
 * @param vector        the vector
 * @param itor          the itor
 * @param data          the data
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_insert_next(tt_vector_ref_t vector, tt_size_t itor, tt_cpointer_t data);

/*! insert the vector head
 *
 * @param vector        the vector
 * @param data          the data
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_insert_head(tt_vector_ref_t vector, tt_cpointer_t data);

/*! insert the vector tail
 *
 * @param vector        the vector
 * @param data          the data
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_insert_tail(tt_vector_ref_t vector, tt_cpointer_t data);

/*! replace the vector item
 *
 * @param vector        the vector
 * @param itor          the itor
 * @param data          the data
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_replace(tt_vector_ref_t vector, tt_size_t itor, tt_cpointer_t data);

/*! replace the vector head item
 *
 * @param vector        the vector
 * @param data          the data
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_replace_head(tt_vector_ref_t vector, tt_cpointer_t data);

/*! replace the vector last
 *
 * @param vector        the vector
 * @param data          the data
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_replace_last(tt_vector_ref_t vector, tt_cpointer_t data);

/*! remove the vector item
 *
 * @param vector        the vector
 * @param itor          the item itor
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_remove(tt_vector_ref_t vector, tt_size_t itor);

/*! remove the vector head item
 *
 * @param vector        the vector
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_remove_head(tt_vector_ref_t vector);

/*! remove the vector last item
 *
 * @param vector        the vector
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_remove_last(tt_vector_ref_t vector);

/*! the vector size
 *
 * @param vector        the vector
 *
 * @return              the vector size
 */
tt_size_t               tt_vector_size(tt_vector_ref_t vector);

/*! the vector grow
 *
 * @param vector        the vector
 *
 * @return              the vector grow
 */
tt_size_t               tt_vector_grow(tt_vector_ref_t vector);

/*! the vector maxn
 *
 * @param vector        the vector
 *
 * @return              the vector maxn
 */
tt_size_t               tt_vector_maxn(tt_vector_ref_t vector);



/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif