#ifndef QUEUE_LIST_H
#define QUEUE_LIST_H

/**
 * \brief Queue implementation by list
 */

#include <list/single_list.h>

#include <stdbool.h>

/**
 * \struct lqueue
 *
 * \brief Definition of lqueue
 */
typedef struct lqueue {
    /* front pointer */
    single_list_head *front;
    single_list_head *rear;
    size_t len;
} lqueue;

/**
 * lqueue_init - Initialize the lqueue structure
 *
 * \param lq the pointer of pointer of lqueue structure
 *
 * \return bool
 */
extern bool lqueue_init(lqueue **lq);

/**
 * lqueue_front - get the front of the lqueue
 *
 * \param q the pointer of the lqueue structure
 *
 * \return single_list_head
 */
extern single_list_head *lqueue_front(lqueue *q);

/**
 * lqueue_rear - get the rear of the lqueue
 *
 * \param q the pointer of the lqueue structure
 *
 * \return single_list_head
 */
extern single_list_head *lqueue_rear(lqueue *q);

/**
 * lqueue_add  - add entry into lqueue
 *
 * \param new the entry to be added
 * \param q the pointer of the lqueue structure
 *
 * \return bool
 */
extern bool lqueue_add(single_list_head *new, lqueue *q);

/**
 * lqueue_del  - delete entry from lqueue
 *
 * \param entry the entry to be added
 * \param q the pointer of the lqueue structure
 *
 * \return bool
 */
extern bool lqueue_del(single_list_head *entry, lqueue *q);

/**
 * lqueue_len - get the length of the lqueue
 *
 * \param q the pointer of the lqueue structure
 *
 * \return size_t
 */
extern size_t lqueue_len(lqueue *q);

/**
 * lqueue_empty - true if the lqueue is empty
 *
 * \param q the pointer of the lqueue structure
 *
 * \return bool
 */
extern bool lqueue_empty(lqueue *q);
#endif //QUEUE_LIST_H
