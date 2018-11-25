#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#include "container_of.h"

/*
 * Simple single list implementation
 */
struct single_list_head {
    struct single_list_head *next;
};

/*
 * Initialize the single list head's field
 */
#define SINGLE_LIST_INIT(name) { NULL }

/*
 * Initial the single list head
 */
#define SINGLE_LIST(name) \
    struct single_list_head name = SINGLE_LIST_INIT(name)

/**
 * single_list_add - add a entry after the head
 * @new: new entry to be added
 * @head: single list head
 *
 * This can be simple implement stack
 */
void single_list_add(struct single_list_head *new, struct single_list_head *head) {
    if (!new || !head) return;

    new->next = head->next;
    head->next = new;
}

/**
 * single_list_del - del a entry from the list
 * @new: the entry to be deleted
 * @head: the single list head
 */
void single_list_del(struct single_list_head *new, struct single_list_head *head) {
    if (!new || !head) return;

    struct single_list_head *prev = head;

    // find new entry's prev pointer
    while (prev->next != new) {
        prev = prev->next;
    }

    // delete the new entry
    prev->next = prev->next->next;
}

/**
 * single_list_reverse - reverse the single list
 * @head: the single list head
 */
void single_list_reverse(struct single_list_head *head) {
    if (!head || !head->next) return;

    struct single_list_head *prev = head->next;
    struct single_list_head *current = prev->next;
    while( current != NULL ) {
        prev->next = current->next;
        // move current as first element
        current->next = head->next;
        head->next = current;
        current = prev->next;
    }
}

/**
 * single_list_entry - get the struct of this list embbed in
 */
#define single_list_entry(ptr, type, member) \
    container_of(ptr, type, member)

/**
 * single_list_first_entry - get the first entry from the list
 */
#define single_list_first_entry(ptr, type, member) \
    single_list_entry((ptr)->next, type, member)

/**
 * single_list_next_entry - get the next entry from the list
 */
#define single_list_next_entry(pos, member) \
    single_list_entry((pos)->member.next, typeof(*(pos)), member)

/**
 * single_list_for_each - iter the single list
 */
#define single_list_for_each(pos, head) \
    for(pos = (head)->next; pos != NULL; pos = pos->next)

/**
 * single_list_for_each_entry - iter the single list
 */
#define single_list_for_each_entry(pos, head, member) \
    for(pos = single_list_first_entry((head), typeof(*pos), member); \
            &pos->member != NULL; \
            pos = single_list_next_entry(pos, member))

#endif //SINGLE_LIST_H
