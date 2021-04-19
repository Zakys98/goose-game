/** 
 * @brief It tests link module
 * 
 * @file link_test.c
 * @author Jiri Zak
 * @version 1.0 
 * @date 17-04-2021
 * @copyright GNU Public License
 */

#include "../include/link.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/test.h"
#include "../include/types.h"

void test_link_init() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(l != NULL);
}

void test_link_destroy() {
    Link *l = link_create(1);
    link_destroy(&l);
    PRINT_TEST_RESULT(l == NULL);
}

void test_link_destroy_null() {
    Link *l = NULL;
    link_destroy(&l);
    PRINT_TEST_RESULT(l == NULL);
}

void test_link_get_id() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_get_id(l) == 1);
}

void test_link_get_id_from_null() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_id(l) == -1);
}

void test_link_set_name() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_name(l, "name") == 1);
}

void test_link_set_name_to_null() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_name(l, "name") == 0);
}

void test_link_get_name() {
    Link *l = link_create(1);
    link_set_name(l, "name");
    PRINT_TEST_RESULT(strcmp(link_get_name(l), "name") == 0);
}

void test_link_get_name_from_null() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_name(l) == NULL);
}

void test_link_set_first_space_id() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_first_space(l, 2) == 1);
}

void test_link_set_first_space_id_to_null() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_first_space(l, 2) == 0);
}

void test_link_get_first_space_id() {
    Link *l = link_create(1);
    link_set_first_space(l, 2);
    PRINT_TEST_RESULT(link_get_first_space(l) == 2);
}

void test_link_get_first_space_id_from_null() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_first_space(l) == -1);
}

void test_link_set_second_space_id() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_second_space(l, 2) == 1);
}

void test_link_set_second_space_id_to_null() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_second_space(l, 2) == 0);
}

void test_link_get_second_space_id() {
    Link *l = link_create(1);
    link_set_second_space(l, 2);
    PRINT_TEST_RESULT(link_get_second_space(l) == 2);
}

void test_link_get_second_space_id_from_null() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_second_space(l) == -1);
}

void test_link_set_opened() {
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_opened(l, FALSE) == 1);
}

void test_link_set_opened_to_null() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_opened(l, FALSE) == 0);
}

void test_link_get_opened() {
    Link *l = link_create(1);
    link_set_opened(l, FALSE);
    PRINT_TEST_RESULT(link_get_opened(l) == FALSE);
}

void test_link_get_opened_from_null() {
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_opened(l) == FALSE);
}

void test_all() {
    test_link_init();
    test_link_destroy();
    test_link_destroy_null();
    test_link_get_id();
    test_link_get_id_from_null();
    test_link_set_name();
    test_link_set_name_to_null();
    test_link_get_name();
    test_link_get_name_from_null();
    test_link_set_first_space_id();
    test_link_set_first_space_id_to_null();
    test_link_get_first_space_id();
    test_link_get_first_space_id_from_null();
    test_link_set_second_space_id();
    test_link_set_second_space_id_to_null();
    test_link_get_second_space_id();
    test_link_get_second_space_id_from_null();
    test_link_set_opened();
    test_link_set_opened_to_null();
    test_link_get_opened();
    test_link_get_opened_from_null();

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
    printf("Link test\n");
    printf("=========================\n");

    if (argc == 2) {
        switch (atoi(argv[1])) {
            case 1:
                test_link_init();
                break;
            case 2:
                test_link_destroy();
                break;
            case 3:
                test_link_destroy_null();
                break;
            case 4:
                test_link_get_id();
                break;
            case 5:
                test_link_get_id_from_null();
                break;
            case 6:
                test_link_set_name();
                break;
            case 7:
                test_link_set_name_to_null();
                break;
            case 8:
                test_link_get_name();
                break;
            case 9:
                test_link_get_name_from_null();
                break;
            case 10:
                test_link_set_first_space_id();
                break;
            case 11:
                test_link_set_first_space_id_to_null();
                break;
            case 12:
                test_link_get_first_space_id();
                break;
            case 13:
                test_link_get_first_space_id_from_null();
                break;
            case 14:
                test_link_set_second_space_id();
                break;
            case 15:
                test_link_set_second_space_id_to_null();
                break;
            case 16:
                test_link_get_second_space_id();
                break;
            case 17:
                test_link_get_second_space_id_from_null();
                break;
            case 18:
                test_link_set_opened();
                break;
            case 19:
                test_link_set_opened_to_null();
                break;
            case 20:
                test_link_get_opened();
                break;
            case 21:
                test_link_get_opened_from_null();
                break;

            default:
                break;
        }
    } else
        test_all();

    return 0;
}