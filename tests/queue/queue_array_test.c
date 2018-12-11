#include <queue/queue_array.h>
#include "../unittest.h"

#include <stdlib.h>

static queue *q = NULL;

static void setup(void)
{
    /* allocate memory for queue  */
    ck_assert_int_eq(true, queue_init(&q));
}

static void teardown(void)
{
    /* free the remain memory  */
    for(int i = 0; i < queue_len(q); i++) {
        int *p = queue_front(q);
        queue_del(q);
        free(p);
    }
}

START_TEST(queue_add_tail_test)
{
    for(int i = 0; i < 512; i++) {
        int *p = (int *)malloc(sizeof(int));
        *p = i;
        ck_assert_int_eq(true, queue_add((void *)p, &q));
    }

    queue_init(&q);
    for(int i = 0; i < queue_len(q); i++) {
        ck_assert_int_eq(i, *(int *)q->items[i]);
    }
}
END_TEST

START_TEST(queue_add_leftside_test)
{
    /* add element into queue*/
    for(int i = 0; i < 512; i++) {
        int *p = (int *)malloc(sizeof(int));
        *p = i;
        ck_assert_int_eq(true, queue_add((void *)p, &q));
    }

    /* move front to index 99  */
    for(int i = 0; i < 100; i++) {
        int *p = (int *)queue_front(q);
        ck_assert_int_eq(i, *p);
        ck_assert_int_eq(true, queue_del(q));
        free(p);
    }

    /* add to 20000 */
    for(int i = 512; i < 20000; i++) {
        int *p = (int *)malloc(sizeof(int));
        *p = i;
        ck_assert_int_eq(true, queue_add((void *)p, &q));
    }

    /* verify the access */
    for(int i = 100; i < 20000; i++) {
        int *p = queue_front(q);
        ck_assert_int_eq(i, *p);
        queue_del(q);
        free(p);
    }
}
END_TEST

START_TEST(queue_add_rightside_test)
{
    /* add element into queue*/
    for(int i = 0; i < 512; i++) {
        int *p = (int *)malloc(sizeof(int));
        *p = i;
        ck_assert_int_eq(true, queue_add((void *)p, &q));
    }

    /* move front to index 99  */
    for(int i = 0; i < 300; i++) {
        int *p = (int *)queue_front(q);
        ck_assert_int_eq(i, *p);
        ck_assert_int_eq(true, queue_del(q));
        free(p);
    }

    /* add to 20000 */
    for(int i = 512; i < 20000; i++) {
        int *p = (int *)malloc(sizeof(int));
        *p = i;
        ck_assert_int_eq(true, queue_add((void *)p, &q));
    }

    /* verify the access */
    for(int i = 300; i < 20000; i++) {
        int *p = queue_front(q);
        ck_assert_int_eq(i, *p);
        queue_del(q);
        free(p);
    }
}
END_TEST

Suite *make_queue_array_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("queue_array");
    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, queue_add_tail_test);
    tcase_add_test(tc_core, queue_add_leftside_test);
    tcase_add_test(tc_core, queue_add_rightside_test);
    suite_add_tcase(s, tc_core);

    return s;
}
