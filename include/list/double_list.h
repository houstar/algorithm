#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include <utils/container_of.h>

/**
 * \brief Simple double linked list implementation
 */

/**
 * Definition of the double linked list
 */
typedef struct list_head {
    struct list_head *prev, *next;
} list_head;

/**
 * Initialize the list head
 */
#define LIST_HEAD_INIT(name) { &(name), &(name) }


/**
 * Declare the LIST HEAD
 */
#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

/**
 * list_add - add a new entry
 *
 * \param[in] new the new entry to be added
 * \param[in] head the double list head
 *
 * \return NULL
 */
extern void list_add(list_head *new, list_head *head);

/**
 * list_del - del entry from the list
 *
 * \param[in] entry the entry to be deleted
 *
 * \return NULL
 */
extern void list_del(list_head *entry);

/**
 * list_entry - get the struct of this list embbed in
 */
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

/**
 * list_first_entry - get the first entry from the list
 */
#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

/**
 * list_next_entry - get the next entry from the list
 */
#define list_next_entry(pos, member) \
    list_entry((pos)->member.next, typeof(*(pos)), member)

/**
 * list_for_each - iter the double list
 */
#define list_for_each(pos, head) \
    for(pos = (head)->next; pos != NULL; pos = pos->next)

/**
 * list_for_each_entry - iter the double list
 */
#define list_for_each_entry(pos, head, member) \
    for(pos = list_first_entry((head), typeof(*pos), member); \
            &pos->member != NULL; \
            pos = list_next_entry(pos, member))



#endif //DOUBLE_LIST_H
