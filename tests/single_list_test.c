#include <list/single_list.h>
#include <stdlib.h>

#include "unittest.h"

struct int_list {
    int val;
    single_list_head list;
};

SINGLE_LIST(l);

void setup(void)
{
    /* use single_list_add to add entry */
    for(int i = 0; i < 10; i++ ) {
        struct int_list *p = (struct int_list *)malloc(sizeof(struct int_list));
        p->val = i;
        single_list_add(&p->list, &l);
    }
}

void teardown(void)
{
    /* iter the single list */
    struct int_list *p = NULL;
    single_list_for_each_entry(p, &l, list) {
        free(p);
    }
}

START_TEST(single_list_add_test)
{
    struct int_list *p = NULL;
    /* use single_list_add to add entry */
    for(int i = 10; i < 100; i++ ) {
        p = (struct int_list *)malloc(sizeof(struct int_list));
        p->val = i;
        single_list_add(&p->list, &l);
    }

    int j = 99;
    single_list_for_each_entry(p, &l, list) {
        ck_assert_int_eq(p->val, j);
        j--;
    }

}
END_TEST

START_TEST(single_list_del_test)
{
    /* iter the single list */
    struct int_list *p = NULL;
    single_list_for_each_entry(p, &l, list) {
        single_list_del(&p->list, &l);
        free(p);
    }
}
END_TEST

START_TEST(single_list_reverse_test)
{
    /* reverse the single list */
    single_list_reverse(&l);

    /* iter the single list */
    struct int_list *p = NULL;
    int i = 0;
    single_list_for_each_entry(p, &l, list) {
        ck_assert_int_eq(p->val, i);
        i++;
    }
}
END_TEST

Suite *make_single_list_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("single_list");
    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, single_list_add_test);
    tcase_add_test(tc_core, single_list_reverse_test);
    tcase_add_loop_test(tc_core, single_list_del_test, 0, 10);
    suite_add_tcase(s, tc_core);

    return s;
}
