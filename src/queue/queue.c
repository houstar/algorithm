#include <queue/queue.h>

#include <stdlib.h>

/**
 * Initialize the Queue structure
 *
 * \param qq the pointer of pointer of Queue structure
 *
 * \return bool
 */
bool queue_init(queue **qq)
{
    *qq = (queue *)malloc(sizeof(queue));

    if ( ! (*qq)) return false;

    (*qq)->front = (*qq)->rear = 0;
    (*qq)->cap = Q_SIZE;

    /* allocate memory for items */
    (*qq)->items = (void **)malloc(sizeof(void *) * (*qq)->cap);

    if ( !(*qq)->items) {
        /* If failed to alloc memory, then free Q */
        free(*qq);
        return false;
    }

    return true;

}


/**
 * __queue_is_valid - valid the queue if NULL
 */
static inline bool __queue_is_valid(queue *q)
{
    if (!q) {
        return false;
    }

    return true;
}
/**
 * queue_empty - true if the queue is empty
 *
 * \param q the pointer of Queue structure
 *
 * \return bool
 */
bool queue_empty(queue *q)
{
    __queue_is_valid(q);

    return q->rear == q->front;
}

/**
 * queue_full - true if the queue is full
 *
 * \param q the pointer of Queue structure
 *
 * \return bool
 */
bool queue_full(queue *q)
{
    __queue_is_valid(q);

    return (q->rear + 1) % q->cap == q->front;
}

/**
 * queue_front - get the front of the queue
 *
 * \param q the pointer of the structure
 *
 * \return the void pointer of the item
 */
void *queue_front(queue *q)
{
    if (!q) return NULL;

    return q->items[q->front];

}

/**
 * queue_rear - get the rear of the queue
 *
 * \param q the pointer of the structure
 *
 * \return the void pointer of the item
 */
void *queue_rear(queue *q)
{
    if (!q) return NULL;

    return q->items[q->rear];
}

/**
 * __queue_extend - extend the queue's array
 */
static inline bool __queue_extend(queue **qq)
{
    if ( !(*qq) ) return queue_init(qq);

    if ( !queue_full(*qq) ) return true;
    /* if the Queue is full, then extend the size */
    (*qq)->items = (void **)realloc((*qq)->items, sizeof(void *) * ( (*qq)->cap) << 1);

    /* if rear on the lefside of the middle and front*/
    if ((*qq)->rear < (*qq)->front ) {
        if ((*qq)->rear <  ((*qq)->cap >> 1) ) {
            for(size_t i = 0; i < (*qq)->rear; i++) {
                (*qq)->items[(*qq)->cap + i] = (*qq)->items[i];
            }
            (*qq)->rear += (*qq)->cap;

        } else {
            for(size_t i = (*qq)->front; i < (*qq)->cap; i++) {
                (*qq)->items[(*qq)->cap + i] = (*qq)->items[i];
            }
            (*qq)->front += (*qq)->cap;
        }
    }

    (*qq)->cap <<= 1;

    return true;
}

/**
 * queue_add - add entry into the queue rear
 *
 * \param q the pointer of pointer of the structure
 * \param item the entry to be added
 *
 * \return bool
 */
bool queue_add(void *item, queue **q)
{
    __queue_extend(q);

    (*q)->items[(*q)->rear] = item;
    (*q)->rear =((*q)->rear + 1) % (*q)->cap;

    return true;
}


/**
 * queue_del - delete the front entry of the queue
 *
 * \param q the pointer of the structure
 *
 * \return bool
 */
bool queue_del(queue *q)
{
    if (queue_empty(q)) return false;

    q->front = (q->front + 1) % q->cap;

    return true;
}

/**
 * queue_len - get the length of the queue
 *
 * \param q the pointer of the structure
 *
 * \return size_t
 */
size_t queue_len(queue *q)
{
    return (q->rear - q->front + q->cap) % q->cap;
}
