/**
 * \brief Queue implementation by list
 */

#include <queue/queue_list.h>

#include <stdlib.h>

/**
 * lqueue_init - Initialize the lqueue structure
 *
 * \param lq the pointer of pointer of lqueue structure
 *
 * \return bool
 */
bool lqueue_init(lqueue **lq)
{
    *lq = (lqueue *)malloc(sizeof(lqueue));
    if (!(*lq)) return false;

    (*lq)->front = (single_list_head *)malloc(sizeof(single_list_head));
    if (!(*lq)->front) {
        free(*lq);
        return false;
    }

    INIT_SINGLE_LIST_HEAD((*lq)->front);
    (*lq)->rear = (*lq)->front;
    (*lq)->len = 0;

    return true;
}

/**
 * lqueue_front - get the front of the lqueue
 *
 * \param lq the pointer of the lqueue structure
 *
 * \return single_list_head
 */
single_list_head *lqueue_front(lqueue *q)
{
    return q->front->next;
}

/**
 * lqueue_rear - get the rear of the lqueue
 *
 * \param lq the pointer of the lqueue structure
 *
 * \return single_list_head
 */
single_list_head *lqueue_rear(lqueue *q)
{
    return q->rear;
}

/**
 * lqueue_add  - add entry into lqueue
 *
 * \param new the entry to be added
 * \param lq the pointer of the lqueue structure
 *
 * \return bool
 */
bool lqueue_add(single_list_head *new, lqueue *q)
{
    if(!q->front->next) q->rear = new;

    single_list_add(new, q->front);
    q->len++;

    return true;
}

/**
 * lqueue_entry - delete entry into lqueue
 *
 * \param entry the entry to be delete
 * \param lq the pointer of the lqueue structure
 *
 * \return bool
 */
bool lqueue_del(single_list_head *entry, lqueue *q)
{
    single_list_del(entry, q->front);
    q->len--;

    return true;
}

/**
 * lqueue_len - get the length of the lqueue
 *
 * \param lq the pointer of the lqueue structure
 *
 * \return size_t
 */
size_t lqueue_len(lqueue *q)
{
    return q->len;
}

/**
 * lqueue_empty - true if the lqueue is empty
 *
 * \param lq the pointer of the lqueue structure
 *
 * \return bool
 */
bool lqueue_empty(lqueue *q)
{
    return q->front->next = NULL;
}
