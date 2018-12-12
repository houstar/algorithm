#include <list/circle_list.h>
#include <utils/container_of.h>

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
void circle_list_add(circle_list_head *new, circle_list_head *head)
{
    if (!new || !head) return;

    new->next = head->next;
    head->next = new;
}

/**
 * circle_list_del - del a entry from the list
 *
 * \param[in] new the entry to be deleted
 * \param[in] head the circle list head
 */
void circle_list_del(circle_list_head *new, circle_list_head *head)
{
    if (!new || !head) return;

    circle_list_head **cur = &head;
    for( ; *cur != new; cur = &(*cur)->next);

    if (*cur) {
        *cur = (*cur)->next;
    }
}
