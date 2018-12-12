#include <queue/queue_list.h>
#include "../unittest.h"

#include <stdlib.h>

static lqueue *q = NULL;


typedef struct int_list {
    int val;
    single_list_head list;
} int_list;

static void setup(void)
{
    ck_assert_int_eq(true, lqueue_init(&q));

    for(int i = 0; i < 10; i++) {
        int_list *p = (int_list *)calloc(0, sizeof(int_list));
        p->val = i;
        lqueue_add(&p->list, q);
    }
}

static void teardown(void)
{
    for(single_list_head *it = lqueue_front(q); it != NULL; it = it->next) {
        int_list *p = single_list_entry(it, int_list, list);
        lqueue_del(it, q);
        free(p);
    }
}

START_TEST(lqueue_add_test)
{
    for(int i = 10; i < 20; i++) {
        int_list *p = (int_list *)calloc(0, sizeof(int_list));
        p->val = i;
        lqueue_add(&p->list, q);
    }
    ck_assert_int_eq(20, lqueue_len(q));

    int i = 0;
    for(single_list_head *it = lqueue_front(q); it != NULL; it = it->next, i++) {
        int_list *p = single_list_entry(it, int_list, list);
        ck_assert_int_eq(i, p->val);
    }
}
END_TEST

START_TEST(lqueue_del_test)
{
    for(single_list_head *it = lqueue_front(q); it != NULL; it = it->next) {
        int_list *p = single_list_entry(it, int_list, list);
        if(p->val == _i) {
            lqueue_del(it, q);
        }
    }

    for(single_list_head *it = lqueue_front(q); it != NULL; it = it->next) {
        int_list *p = single_list_entry(it, int_list, list);
        ck_assert_int_ne(_i, p->val);
    }
    ck_assert_int_eq(9, lqueue_len(q));
}
END_TEST

START_TEST(lqueue_rear_test)
{
    single_list_head *rear = lqueue_rear(q);
    int_list *p = single_list_entry(rear, int_list, list);
    int k = p->val - 1;
    lqueue_del(rear, q);

    rear = lqueue_rear(q);
    p = single_list_entry(rear, int_list, list);
    ck_assert_int_eq(k, p->val);
}
END_TEST

Suite *make_queue_list_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("queue_list");
    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, lqueue_add_test);
    tcase_add_test(tc_core, lqueue_rear_test);
    tcase_add_loop_test(tc_core, lqueue_del_test, 0, 10);
    suite_add_tcase(s, tc_core);

    return s;
}
