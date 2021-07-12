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

/*! exit 
 *
 * @param vector        the vector
 *
 * @return              tt_void_t
 */
tt_void_t               tt_vector_exit(tt_vector_ref_t vector);








/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tt_extern_c_leave__

#endif