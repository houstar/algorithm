#include <stdlib.h>

#include "unittest.h"

int main(int argc, char *argv[])
{
    int number_failed;
    SRunner *sr;

    sr = srunner_create(make_single_list_suite());
    srunner_add_suite(sr, make_circle_list_suite());
    srunner_add_suite(sr, make_double_list_suite());
    srunner_add_suite(sr, make_queue_array_suite());
    srunner_add_suite(sr, make_queue_list_suite());
    srunner_add_suite(sr, make_binary_tree_suite());

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
