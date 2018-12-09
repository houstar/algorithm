#include <list/double_list.h>

#include <stddef.h>

/* Originally clone from linux kernel source without RCU */

/**
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_add(list_head *new,
        list_head *prev,
        list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    WRITE_ONCE(prev->next, new);
}

/**
 * list_add - add a new entry after the head of list
 *
 * \param[in] new the new entry to be added
 * \param[in] head the double list head
 *
 * \return NULL
 */
void list_add(list_head *new, list_head *head)
{
    __list_add(new, head, head->next);
}

/**
 * list_add_tail - add a new entry at the tail of list
 *
 * \param[in] new the new entry to be added
 * \param[in] head the double list head
 *
 * \return NULL
 */
void list_add_tail(list_head *new, list_head *head)
{
    __list_add(new, head->prev, head);
}

/**
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static void __list_del(list_head *prev, list_head *next)
{
	next->prev = prev;
	WRITE_ONCE(prev->next, next);
}

/**
 * list_del - deletes entry from list.
 * \param[in] entry the element to delete from the list.
 *  \note list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
static void __list_del_entry(list_head *entry)
{
	__list_del(entry->prev, entry->next);
}

/**
 * list_del - del entry from the list
 *
 * \param[in] entry the entry to be deleted
 *
 * \return NULL
 */
void list_del(list_head *entry)
{
    __list_del_entry(entry);
    entry->prev = entry;
    entry->next = entry;
}
