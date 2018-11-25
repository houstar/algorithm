#ifndef CIRCLE_LIST_H
#define CIRCLE_LIST_H

#include "container_of.h"

/*
 * Simple circle list implementation
 */
struct circle_list_head {
    struct circle_list_head *next;
};

/*
 * Initialize the circle list head's field
 *
 * This next field will be as head itself
 */
#define CIRCLE_LIST_INIT(name) { &(name) }

/*
 * Initial the circle list head
 */
#define CIRCLE_LIST(name) \
    struct circle_list_head name = CIRCLE_LIST_INIT(name)

/**
 * circle_list_add - add a entry after the head
 * @new: new entry to be added
 * @head: circle list head
 *
 * This can be simple implement stack
 */
void circle_list_add(struct circle_list_head *new, struct circle_list_head *head) {
    if (!new || !head) return;

    new->next = head->next;
    head->next = new;
}

/**
 * circle_list_del - del a entry from the list
 * @new: the entry to be deleted
 * @head: the circle list head
 */
void circle_list_del(struct circle_list_head *new, struct circle_list_head *head) {
    if (!new || !head) return;

    struct circle_list_head *prev = head;

    // find new entry's prev pointer
    while (prev->next != new) {
        prev = prev->next;
    }

    // delete the new entry
    prev->next = prev->next->next;
}

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