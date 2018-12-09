#include <list/circle_list.h>
#include <stdlib.h>

#include "unittest.h"

struct int_list {
    int val;
    circle_list_head list;
};

CIRCLE_LIST(circle_list_test_head);

static void setup(void)
{
    /* use circle_list_add to add entry */
    for(int i = 0; i < 10; i++ ) {
        struct int_list *p = (struct int_list *)malloc(sizeof(struct int_list));
        p->val = i;
        circle_list_add(&p->list, &circle_list_test_head);
    }
}

static void teardown(void)
{
    /* iter the circle list */
    struct int_list *p = NULL;
    circle_list_for_each_entry(p, &circle_list_test_head, list) {
        free(p);
    }
}

START_TEST(circle_list_add_test)
{
    struct int_list *p = NULL;
    /* use circle_list_add to add entry */
    for(int i = 10; i < 100; i++ ) {
        p = (struct int_list *)malloc(sizeof(struct int_list));
        p->val = i;
        circle_list_add(&p->list, &circle_list_test_head);
    }

    int j = 99;
    circle_list_for_each_entry(p, &circle_list_test_head, list) {
        ck_assert_int_eq(p->val, j);
        j--;
    }

}
END_TEST

START_TEST(circle_list_del_test)
{
    /* iter the circle list */
    struct int_list *p = NULL;
    circle_list_for_each_entry(p, &circle_list_test_head, list) {
        circle_list_del(&p->list, &circle_list_test_head);
        free(p);
    }
}
END_TEST

Suite *make_circle_list_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("circle_list");
    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, circle_list_add_test);
    tcase_add_loop_test(tc_core, circle_list_del_test, 0, 10);
    suite_add_tcase(s, tc_core);

    return s;
}
