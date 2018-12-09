#include <list/double_list.h>
#include <stdlib.h>

#include "../unittest.h"

struct int_list {
    int val;
    list_head list;
};

LIST_HEAD(double_list_test_head);

static void setup(void)
{
    /* use list_add to add entry */
    for(int i = 0; i < 10; i++ ) {
        struct int_list *p = (struct int_list *)malloc(sizeof(struct int_list));
        p->val = i;
        list_add(&p->list, &double_list_test_head);
    }
}

static void teardown(void)
{
}

START_TEST(list_add_test)
{
}
END_TEST

START_TEST(list_del_test)
{
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
    tcase_add_test(tc_core, list_del_test);
    suite_add_tcase(s, tc_core);

    return s;
}
