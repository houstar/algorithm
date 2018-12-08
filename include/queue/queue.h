#ifndef QUEUE_H
#define QUEUE_H


#include <stddef.h>
#include <stdbool.h>


/**
 * \brief Simple Circle Queue implementation by array
 *
 * This queue use dynamic circle array to save memory.
 * If the queue is full, double the size
 */


/**
 * \brief Definition of dynamic queue
 */
typedef struct queue {
    /* the front element */
    size_t front;
    /* the rear element */
    size_t rear;
    /* the queue's capacity */
    size_t cap;
    /* hold the actual elements */
    void **items;
} queue;

/**
 * \brief Default Queue's Capacity
 */
#define Q_SIZE 32

/**
 * Initialize the Queue structure
 *
 * \param qq the pointer of pointer of Queue structure
 *
 * \return bool
 */
extern bool queue_init(queue **qq);

/**
 * queue_empty - true if the queue is empty
 *
 * \param q the pointer of Queue structure
 *
 * \return bool
 */
extern bool queue_empty(queue *q);

/**
 * queue_full - true if the queue is full
 *
 * \param q the pointer of Queue structure
 *
 * \return bool
 */
extern bool queue_full(queue *q);

/**
 * queue_front - get the front of the queue
 *
 * \param q the pointer of the structure
 *
 * \return the void pointer of the item
 */
extern void *queue_front(queue *q);

/**
 * queue_rear - get the rear of the queue
 *
 * \param q the pointer of the structure
 *
 * \return the void pointer of the item
 */
extern void *queue_rear(queue *q);

/**
 * queue_add - add entry into the queue rear
 *
 * \param q the pointer of pointer of the structure
 * \param item the entry to be added
 *
 * \return bool
 */
extern bool queue_add(void *item, queue **q);


/**
 * queue_del - delete the front entry of the queue
 *
 * \param q the pointer of the structure
 *
 * \return bool
 */
extern bool queue_del(queue *q);

/**
 * queue_len - get the length of the queue
 *
 * \param q the pointer of the structure
 *
 * \return size_t
 */
extern size_t queue_len(queue *q);

#endif //QUEUE_H
