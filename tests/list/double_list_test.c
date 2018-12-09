#include <list/double_list.h>
#include <stdlib.h>
#include <stdio.h>

#include "../unittest.h"

struct int_list {
    int val;
    list_head list;
};

LIST_HEAD(double_list_test_head);

static void setup(void)
{
    /* use list_add to add entry */
    for(int i = 0; i < 20; i++ ) {
        struct int_list *p = (struct int_list *)malloc(sizeof(struct int_list));
        p->val = i;
        list_add(&p->list, &double_list_test_head);
    }
}

static void teardown(void)
{
    struct int_list *p = NULL;
    list_for_each_entry(p, &double_list_test_head, list) {
        free(p);
    }
}

START_TEST(list_add_test)
{
    struct int_list *p = NULL;
    for(int i = 20; i < 100; i++ ) {
        p = (struct int_list *)malloc(sizeof(struct int_list));
        p->val = i;
        list_add(&p->list, &double_list_test_head);
    }

    int k = 99;
    list_for_each_entry(p, &double_list_test_head, list) {
        ck_assert_int_eq(p->val, k--);
    }
}
END_TEST

START_TEST(list_add_tail_test)
{
    struct int_list *p = NULL;
    for(int i = -1; i > -10; i-- ) {
        p = (struct int_list *)malloc(sizeof(struct int_list));
        p->val = i;
        list_add_tail(&p->list, &double_list_test_head);
    }

    int k = 19;
    list_for_each_entry(p, &double_list_test_head, list) {
        ck_assert_int_eq(p->val, k--);
    }
}
END_TEST

START_TEST(list_del_test)
{
    struct int_list *p = NULL;
    struct int_list *n = NULL;
    list_for_each_entry_safe(p, n, &double_list_test_head, list) {
        list_del(&p->list);
    }
}
END_TEST

Suite *make_double_list_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("double_list");
    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, list_add_test);
    tcase_add_test(tc_core, list_add_tail_test);
    tcase_add_test(tc_core, list_del_test);
    suite_add_tcase(s, tc_core);

    return s;
}
