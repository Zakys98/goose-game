/** 
 * @brief It tests the inventory module
 * 
 * @file inventory_test.c
 * @author Eva Moresova
 * @version 1.0 
 * @date 22-03-2021
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>

#include "../include/inventory.h"
#include "../include/test.h"
#include "../include/types.h"

void test_inventory_create() {
    Inventory* i = inventory_create(10);
    PRINT_TEST_RESULT(i != NULL);
}

void test_inventory_create_negative_cap() {
	Inventory* i = inventory_create(-2);
    PRINT_TEST_RESULT(i == NULL);
}

void test_inventory_destroy_inicialized() {
    Inventory* i = inventory_create(10);
    inventory_destroy(i);
    PRINT_TEST_RESULT(i == NULL);
}

void test_inventory_destroy_null() {
    Inventory* i = NULL;
    inventory_destroy(i);
    PRINT_TEST_RESULT(i == NULL);
}




void test_all() {
    test_inventory_create();
	test_inventory_create_negative_cap();
    test_inventory_destroy_inicialized();
    test_inventory_destroy_null();

    PRINT_PASSED_PERCENTAGE;
}

int main(int argc, char **argv) {
    printf("Die test\n");
    printf("=========================\n");

    if (argc == 2) {
        switch (atoi(argv[1])) {
            case 1:
                test_inventory_create();
                break;
			case 2:
                test_inventory_create_negative_cap();
                break;
            case 3:
                test_inventory_destroy_inicialized();
                break;
            case 4:
                test_inventory_destroy_null();
                break;
            default:
                break;
        }
    } else
        test_all();

    return 0;
}