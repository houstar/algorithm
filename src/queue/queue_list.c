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
 * \param q the pointer of the lqueue structure
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
 * \param q the pointer of the lqueue structure
 *
 * \return single_list_head
 * \note O(1) S(1)
 */
single_list_head *lqueue_rear(lqueue *q)
{
    return q->rear;
}

/**
 * lqueue_add  - add entry into lqueue
 *
 * \param new the entry to be added
 * \param q the pointer of the lqueue structure
 *
 * \return bool
 *
 * \note O(1) S(1)
 */
bool lqueue_add(single_list_head *new, lqueue *q)
{
    new->next = NULL;
    single_list_add(new, q->rear);
    q->rear = q->rear->next;
    q->len++;

    return true;
}

/**
 * lqueue_entry - delete entry into lqueue
 *
 * \param entry the entry to be delete
 * \param q the pointer of the lqueue structure
 *
 * \return bool
 * \note O(n) S(1)
 */
bool lqueue_del(single_list_head *entry, lqueue *q)
{
    if(!entry || !q) return false;

    single_list_head *prev = q->front;

    while( prev->next != entry  && prev->next != NULL) {
        prev = prev->next;
    }

    if ( prev->next ) {
        prev->next = prev->next->next;
        q->rear = prev;
        q->len--;
        return true;
    }

    /* not found the element  */
    return false;
}

/**
 * lqueue_len - get the length of the lqueue
 *
 * \param q the pointer of the lqueue structure
 *
 * \return size_t
 * \note O(1) S(1)
 */
size_t lqueue_len(lqueue *q)
{
    return q->len;
}

/**
 * lqueue_empty - true if the lqueue is empty
 *
 * \param q the pointer of the lqueue structure
 *
 * \return bool
 * \note O(1) S(1)
 */
bool lqueue_empty(lqueue *q)
{
    return q->front->next = NULL;
}
