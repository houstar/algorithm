#ifndef CIRCLE_LIST_H
#define CIRCLE_LIST_H

#include <utils/container_of.h>

/**
 * \brief Simple circle list implementation
 */
typedef struct circle_list_head {
    struct circle_list_head *next;
} circle_list_head;

/**
 * Initialize the circle list head's field
 *
 * This next field will be as head itself
 */
#define CIRCLE_LIST_INIT(name) { &(name) }

/*
 * Initial the circle list head
 */
#define CIRCLE_LIST(name) \
    circle_list_head name = CIRCLE_LIST_INIT(name)

/**
 * circle_list_add - add a entry after the head
 *
 * This can be simple implement stack
 *
 * \param[in] new entry to be added
 * \param[in] head circle list head
 */
void circle_list_add(circle_list_head *new, circle_list_head *head);

/**
 * circle_list_del - del a entry from the list
 *
 * \param[in] new the entry to be deleted
 * \param[in] head the circle list head
 */
void circle_list_del(circle_list_head *new, circle_list_head *head);

/**
 * circle_list_entry - get the struct of this list embbed in
 */
#define circle_list_entry(ptr, type, member) \
    container_of(ptr, type, member)

/**
 * circle_list_first_entry - get the first entry from the list
 */
#define circle_list_first_entry(ptr, type, member) \
    circle_list_entry((ptr)->next, type, member)

/**
 * circle_list_next_entry - get the next entry from the list
 */
#define circle_list_next_entry(pos, member) \
    circle_list_entry((pos)->member.next, typeof(*(pos)), member)

/**
 * circle_list_for_each - iter the circle list
 */
#define circle_list_for_each(pos, head) \
    for(pos = (head)->next; pos != (head); pos = pos->next)

/**
 * circle_list_for_each_entry - iter the circle list
 */
#define circle_list_for_each_entry(pos, head, member) \
    for(pos = circle_list_first_entry((head), typeof(*pos), member); \
            &pos->member != head; \
            pos = circle_list_next_entry(pos, member))

#endif //CIRCLE_LIST_H
