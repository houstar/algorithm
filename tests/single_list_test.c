
#include <list/single_list.h>
#include <stdlib.h>

#include "unittest.h"

struct int_list {
    int val;
    struct single_list_head list;
};

SINGLE_LIST(l);

START_TEST(single_list_add_test)
{
    /* use single_list_add to add entry */
    for(int i = 0; i < 10; i++ ){
        struct int_list *p = (struct int_list *)malloc(sizeof(struct int_list));
        p->val = i;
        single_list_add(&p->list, &l);
    }

    /* iter the single list */
    struct int_list *p = NULL;
    int j = 10;
    single_list_for_each_entry(p, &l, list) {
        j--;
        ck_assert_int_eq(p->val, j);
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

START_TEST(single_list_del_test)
{
    struct int_list *p = NULL;
    p = single_list_first_entry(&l, struct int_list, list);
    single_list_del(&p->list, &l);

    struct int_list *q = NULL;
    for(int j = _i; j < 10; j++) {
        single_list_for_each_entry(q, &l, list) {
            ck_assert_int_eq(q->val, j);
        }
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
    tcase_add_test(tc_core, single_list_add_test);
    tcase_add_test(tc_core, single_list_reverse_test);
    tcase_add_loop_test(tc_core, single_list_del_test, 0, 10);
    suite_add_tcase(s, tc_core);

    return s;
}
