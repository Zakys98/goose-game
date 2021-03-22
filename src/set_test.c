/** 
 * @brief It tests space module
 * 
 * @file space_test.c
 * @author Jiri Zak
 * @version 1.0 
 * @date 07-03-2021
 * @copyright GNU Public License
 */

#include "../include/set.h"

#include <stdlib.h>

#include "../include/test.h"
#include "../include/types.h"

void test_set_init() {
    Set *s = set_create();
    PRINT_TEST_RESULT(s != NULL);
}

void test_set_destroy_inicialized() {
    Set *s = set_create();
    set_destroy(&s);
    PRINT_TEST_RESULT(s == NULL);
}

void test_set_destroy_null() {
    Set *s = NULL;
    set_destroy(&s);
    PRINT_TEST_RESULT(s == NULL);
}

void test_set_get_size() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_get_size(s) == 0);
}

void test_set_get_size_null() {
    Set *s = NULL;
    PRINT_TEST_RESULT(set_get_size(s) == -1);
}

void test_set_add_item() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_add(s, 5) == OK);
}

void test_set_add_to_null() {
    Set *s = NULL;
    PRINT_TEST_RESULT(set_add(s, 2) == ERROR);
}

void test_set_delete_item() {
    Set *s = set_create();
    set_add(s, 5);
    PRINT_TEST_RESULT(set_delete(s, 5) == OK);
}

void test_set_delete_to_null() {
    Set *s = NULL;
    PRINT_TEST_RESULT(set_delete(s, 2) == ERROR);
}

void test_set_delete_non_existing_item() {
    Set *s = set_create();
    PRINT_TEST_RESULT(set_delete(s, 5) == ERROR);
}

void test_all() {
    test_set_init();
    test_set_destroy_inicialized();
    test_set_destroy_null();
    test_set_get_size();
    test_set_get_size_null();
    test_set_add_item();
    test_set_add_to_null();
    test_set_delete_item();
    test_set_delete_to_null();
    test_set_delete_non_existing_item();

    PRINT_PASSED_PERCENTAGE;
}

/** 
 * @brief Main function for SET unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char **argv) {
    printf("Set test\n");
    printf("=========================\n");

    if (argc == 2) {
        switch (atoi(argv[1])) {
            case 1:
                test_set_init();
                break;
            case 2:
                test_set_destroy_inicialized();
                break;
            case 3:
                test_set_destroy_null();
                break;
            case 4:
                test_set_get_size();
                break;
            case 5:
                test_set_get_size_null();
                break;
            case 6:
                test_set_add_item();
                break;
            case 7:
                test_set_add_to_null();
                break;
            case 8:
                test_set_delete_item();
                break;
            case 9:
                test_set_delete_to_null();
                break;
            case 10:
                test_set_delete_non_existing_item();
                break;
            default:
                break;
        }
    } else
        test_all();

    return 0;
}