#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

#include <utils/container_of.h>

/**
 * \brief Simple single list implementation
 *
 * This simple single list implementation achieved
 * insert, delete and reverse operation and embed
 * into the struct as member. To access the struct,
 * please use single_list_entry.
 */

/**
 * single_list_head
 *
 * single_list_head points the list head
 *
 */
typedef struct single_list_head {
    struct single_list_head *next; /**< pointer to next node */
} single_list_head;

/**
 * Initialize the single list head's field
 *
 */
#define SINGLE_LIST_INIT(name) { &(name) }

/**
 * Initial the single list head
 */
#define SINGLE_LIST(name) \
    single_list_head name = SINGLE_LIST_INIT(name)
/**
 * INIT_SINGLE_LIST_HEAD - initial the single list head
 *
 * \param head the single list head
 */
extern void INIT_SINGLE_LIST_HEAD(single_list_head *head);

/**
 * single_list_add - add a entry after the head
 *
 * \param[in] new the node to be added
 * \param[in] head the single list head
 *
 * \since 0.1.0
 */
extern void single_list_add(single_list_head *new, single_list_head *head);

/**
 * single_list_del - del a entry from the list
 * \param[in] new the entry to be deleted
 * \param[in] head the single list head
 *
 * \since 0.1.0
 */
extern void single_list_del(single_list_head *new, single_list_head *head);

/**
 * single_list_reverse - reverse the single list
 * \param[in] head the single list head
 *
 * \since 0.1.0
 */
extern void single_list_reverse(single_list_head *head);

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
    for(pos = (head)->next; pos != head ; pos = pos->next)

/**
 * single_list_for_each_safe - iter the single list while remove entry
 */
#define single_list_for_each_safe(pos, n, head) \
    for(pos = (head)->next, n = pos->next; pos != head ; pos = n, n = pos->next)
 
/**
 * single_list_for_each_entry - iter the single list
 */
#define single_list_for_each_entry(pos, head, member) \
    for(pos = single_list_first_entry((head), typeof(*pos), member); \
            &pos->member != head; \
            pos = single_list_next_entry(pos, member))

/**
 * single_list_for_each_entry_safe - iter the single list while remove entry
 */
#define single_list_for_each_entry_safe(pos, n, head, member) \
    for(pos = single_list_first_entry((head), typeof(*pos), member), \
            n = single_list_next_entry(pos, member); \
            &pos->member != head; \
            pos = n, n = single_list_next_entry(pos, member))
#endif //SINGLE_LIST_H
