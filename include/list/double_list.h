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
 * list_add - add a new entry after the head of list
 *
 * \param[in] new the new entry to be added
 * \param[in] head the double list head
 *
 * \return NULL
 */
extern void list_add(list_head *new, list_head *head);

/**
 * list_add_tail - add a new entry at the tail of list
 *
 * \param[in] new the new entry to be added
 * \param[in] head the double list head
 *
 * \return NULL
 */
extern void list_add_tail(list_head *new, list_head *head);

/**
 * list_del - del entry from the list
 *
 * \param[in] entry the entry to be deleted
 *
 * \return NULL
 */
extern void list_del(list_head *entry);

/**
 * list_entry - get the struct for this entry
 * \param ptr	the &struct list_head pointer.
 * \param type:	the type of the struct this is embedded in.
 * \param member	the name of the list_head within the struct.
 */
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * list_first_entry - get the first element from a list
 * \param ptr	the list head to take the element from.
 * \param type:	the type of the struct this is embedded in.
 * \param member	the name of the list_head within the struct.
 *
 * \note that list is expected to be not empty.
 */
#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

/**
 * list_last_entry - get the last element from a list
 * \param ptr	the list head to take the element from.
 * \param type:	the type of the struct this is embedded in.
 * \param member	the name of the list_head within the struct.
 *
 * \note that list is expected to be not empty.
 */
#define list_last_entry(ptr, type, member) \
	list_entry((ptr)->prev, type, member)

/**
 * list_first_entry_or_null - get the first element from a list
 * \param ptr	the list head to take the element from.
 * \param type:	the type of the struct this is embedded in.
 * \param member	the name of the list_head within the struct.
 *
 * Note that if the list is empty, it returns NULL.
 */
#define list_first_entry_or_null(ptr, type, member) ({ \
	struct list_head *head__ = (ptr); \
	struct list_head *pos__ = READ_ONCE(head__->next); \
	pos__ != head__ ? list_entry(pos__, type, member) : NULL; \
})

/**
 * list_next_entry - get the next element in list
 * \param pos	the type * to cursor
 * \param member	the name of the list_head within the struct.
 */
#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)

/**
 * list_prev_entry - get the prev element in list
 * \param pos	the type * to cursor
 * \param member	the name of the list_head within the struct.
 */
#define list_prev_entry(pos, member) \
	list_entry((pos)->member.prev, typeof(*(pos)), member)

/**
 * list_for_each	-	iterate over a list
 * \param pos	the &struct list_head to use as a loop cursor.
 * \param head	the head for your list.
 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * list_for_each_prev	-	iterate over a list backwards
 * \param pos	the &struct list_head to use as a loop cursor.
 * \param head	the head for your list.
 */
#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev; pos != (head); pos = pos->prev)

/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * \param pos	the &struct list_head to use as a loop cursor.
 * \param n		another &struct list_head to use as temporary storage
 * \param head	the head for your list.
 */
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

/**
 * list_for_each_prev_safe - iterate over a list backwards safe against removal of list entry
 * \param pos	the &struct list_head to use as a loop cursor.
 * \param n		another &struct list_head to use as temporary storage
 * \param head	the head for your list.
 */
#define list_for_each_prev_safe(pos, n, head) \
	for (pos = (head)->prev, n = pos->prev; \
	     pos != (head); \
	     pos = n, n = pos->prev)

/**
 * list_for_each_entry	-	iterate over list of given type
 * \param pos	the type * to use as a loop cursor.
 * \param head	the head for your list.
 * \param member	the name of the list_head within the struct.
 */
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_first_entry(head, typeof(*pos), member);	\
	     &pos->member != (head);					\
	     pos = list_next_entry(pos, member))

/**
 * list_for_each_entry_reverse - iterate backwards over list of given type.
 * \param pos	the type * to use as a loop cursor.
 * \param head	the head for your list.
 * \param member	the name of the list_head within the struct.
 */
#define list_for_each_entry_reverse(pos, head, member)			\
	for (pos = list_last_entry(head, typeof(*pos), member);		\
	     &pos->member != (head); 					\
	     pos = list_prev_entry(pos, member))

/**
 * list_prepare_entry - prepare a pos entry for use in list_for_each_entry_continue()
 * \param pos	the type * to use as a start point
 * \param head	the head of the list
 * \param member	the name of the list_head within the struct.
 *
 * Prepares a pos entry for use as a start point in list_for_each_entry_continue().
 */
#define list_prepare_entry(pos, head, member) \
	((pos) ? : list_entry(head, typeof(*pos), member))

/**
 * list_for_each_entry_continue - continue iteration over list of given type
 * \param pos	the type * to use as a loop cursor.
 * \param head	the head for your list.
 * \param member	the name of the list_head within the struct.
 *
 * Continue to iterate over list of given type, continuing after
 * the current position.
 */
#define list_for_each_entry_continue(pos, head, member) 		\
	for (pos = list_next_entry(pos, member);			\
	     &pos->member != (head);					\
	     pos = list_next_entry(pos, member))

/**
 * list_for_each_entry_continue_reverse - iterate backwards from the given point
 * \param pos	the type * to use as a loop cursor.
 * \param head	the head for your list.
 * \param member	the name of the list_head within the struct.
 *
 * Start to iterate over list of given type backwards, continuing after
 * the current position.
 */
#define list_for_each_entry_continue_reverse(pos, head, member)		\
	for (pos = list_prev_entry(pos, member);			\
	     &pos->member != (head);					\
	     pos = list_prev_entry(pos, member))

/**
 * list_for_each_entry_from - iterate over list of given type from the current point
 * \param pos	the type * to use as a loop cursor.
 * \param head	the head for your list.
 * \param member	the name of the list_head within the struct.
 *
 * Iterate over list of given type, continuing from current position.
 */
#define list_for_each_entry_from(pos, head, member) 			\
	for (; &pos->member != (head);					\
	     pos = list_next_entry(pos, member))

/**
 * list_for_each_entry_from_reverse - iterate backwards over list of given type
 *                                    from the current point
 * \param pos	the type * to use as a loop cursor.
 * \param head	the head for your list.
 * \param member	the name of the list_head within the struct.
 *
 * Iterate backwards over list of given type, continuing from current position.
 */
#define list_for_each_entry_from_reverse(pos, head, member)		\
	for (; &pos->member != (head);					\
	     pos = list_prev_entry(pos, member))

/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * \param pos	the type * to use as a loop cursor.
 * \param n		another type * to use as temporary storage
 * \param head	the head for your list.
 * \param member	the name of the list_head within the struct.
 */
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_first_entry(head, typeof(*pos), member),	\
		n = list_next_entry(pos, member);			\
	     &pos->member != (head); 					\
	     pos = n, n = list_next_entry(n, member))

/**
 * list_for_each_entry_safe_continue - continue list iteration safe against removal
 * \param pos	the type * to use as a loop cursor.
 * \param n		another type * to use as temporary storage
 * \param head	the head for your list.
 * \param member	the name of the list_head within the struct.
 *
 * Iterate over list of given type, continuing after current point,
 * safe against removal of list entry.
 */
#define list_for_each_entry_safe_continue(pos, n, head, member) 		\
	for (pos = list_next_entry(pos, member), 				\
		n = list_next_entry(pos, member);				\
	     &pos->member != (head);						\
	     pos = n, n = list_next_entry(n, member))

/**
 * list_for_each_entry_safe_from - iterate over list from current point safe against removal
 * \param pos	the type * to use as a loop cursor.
 * \param n		another type * to use as temporary storage
 * \param head	the head for your list.
 * \param member	the name of the list_head within the struct.
 *
 * Iterate over list of given type from current point, safe against
 * removal of list entry.
 */
#define list_for_each_entry_safe_from(pos, n, head, member) 			\
	for (n = list_next_entry(pos, member);					\
	     &pos->member != (head);						\
	     pos = n, n = list_next_entry(n, member))

/**
 * list_for_each_entry_safe_reverse - iterate backwards over list safe against removal
 * \param pos	the type * to use as a loop cursor.
 * \param n		another type * to use as temporary storage
 * \param head	the head for your list.
 * \param member	the name of the list_head within the struct.
 *
 * Iterate backwards over list of given type, safe against removal
 * of list entry.
 */
#define list_for_each_entry_safe_reverse(pos, n, head, member)		\
	for (pos = list_last_entry(head, typeof(*pos), member),		\
		n = list_prev_entry(pos, member);			\
	     &pos->member != (head); 					\
	     pos = n, n = list_prev_entry(n, member))

/**
 * list_safe_reset_next - reset a stale list_for_each_entry_safe loop
 * \param pos	the loop cursor used in the list_for_each_entry_safe loop
 * \param n		temporary storage used in list_for_each_entry_safe
 * \param member	the name of the list_head within the struct.
 *
 * list_safe_reset_next is not safe to use in general if the list may be
 * modified concurrently (eg. the lock is dropped in the loop body). An
 * exception to this is if the cursor element (pos) is pinned in the list,
 * and list_safe_reset_next is called after re-taking the lock and before
 * completing the current iteration of the loop body.
 */
#define list_safe_reset_next(pos, n, member)				\
	n = list_next_entry(pos, member)

#endif //DOUBLE_LIST_H
