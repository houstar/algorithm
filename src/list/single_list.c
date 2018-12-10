#include <list/single_list.h>

/**
 * \brief Simple single list implementation
 *
 * This simple single list implementation achieved
 * insert, delete and reverse operation and embed
 * into the struct as member. To access the struct,
 * please use single_list_entry.
 */

/**
 * single_list_add - add a entry after the head
 *
 * \param[in] new the node to be added
 * \param[in] head the single list head
 *
 * \since 0.1.0
 */
void single_list_add(single_list_head *new, single_list_head *head)
{
    if (!new || !head) return;

    new->next = head->next;
    head->next = new;
}

/**
 * INIT_SINGLE_LIST_HEAD - initial the single list head
 *
 * \param head the single list head
 */
void INIT_SINGLE_LIST_HEAD(single_list_head *head)
{
    head->next = NULL;
}

/**
 * single_list_del - del a entry from the list
 * \param[in] new the entry to be deleted
 * \param[in] head the single list head
 *
 * \since 0.1.0
 */
void single_list_del(single_list_head *new, single_list_head *head)
{
    if (!new || !head) return;

    single_list_head *prev = head;

    // find new entry's prev pointer
    while (prev->next != new) {
        prev = prev->next;
    }

    // delete the new entry
    prev->next = prev->next->next;
}

/**
 * single_list_reverse - reverse the single list
 * \param[in] head the single list head
 *
 * \since 0.1.0
 */
void single_list_reverse(single_list_head *head)
{
    if (!head || !head->next) return;

    single_list_head *prev = head->next;
    single_list_head *current = prev->next;
    while( current != NULL ) {
        prev->next = current->next;
        // move current as first element
        current->next = head->next;
        head->next = current;
        current = prev->next;
    }
}
