/** 
 * @brief It tests the die module
 * 
 * @file die_test.c
 * @author Eva Moresova
 * @version 1.0 
 * @date 14-03-2021
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>

#include "../include/die.h"
#include "../include/test.h"
#include "../include/types.h"

void test_die_create() {
    Dice* d = dice_create(1, 6);
    PRINT_TEST_RESULT(d != NULL);
}

void test_die_create_wrong() {
    Dice* d = dice_create(6, 1);
    PRINT_TEST_RESULT(d == NULL);
}

void test_die_destroy_inicialized() {
    Dice* d = dice_create(1, 6);
    dice_destroy(&d);
    PRINT_TEST_RESULT(d == NULL);
}

void test_die_destroy_null() {
    Dice* d = NULL;
    dice_destroy(&d);
    PRINT_TEST_RESULT(d == NULL);
}

void test_die_roll() {
    Dice* d = dice_create(1, 6);
	int a = dice_roll(d);
    PRINT_TEST_RESULT(1 <= a && 6>= a);
    dice_destroy(&d);
}

void test_die_roll_null() {
    Dice* d = NULL;
	int a = dice_roll(d);
    PRINT_TEST_RESULT(a == -1);
    dice_destroy(&d);
}

void test_die_last_roll() {
    Dice* d = dice_create(3, 42);
	int a = dice_roll(d);
	int b = dice_get_last_roll(d);
    PRINT_TEST_RESULT(a == b);
    dice_destroy(&d);
}

void test_die_last_roll_initialized() {
    Dice* d = dice_create(3, 42);
	int a = dice_get_last_roll(d);
    PRINT_TEST_RESULT(a == -1);
    dice_destroy(&d);
}



void test_all() {
    test_die_create();
	test_die_create_wrong();
    test_die_destroy_inicialized();
    test_die_destroy_null();
	test_die_roll();
	test_die_roll_null();
	test_die_last_roll();
	test_die_last_roll_initialized();

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
    printf("Die test\n");
    printf("=========================\n");

    if (argc == 2) {
        switch (atoi(argv[1])) {
            case 1:
                test_die_create();
                break;
			case 2:
                test_die_create_wrong();
                break;
            case 3:
                test_die_destroy_inicialized();
                break;
            case 4:
                test_die_destroy_null();
                break;
			case 5:
				test_die_roll();
				break;
			case 6:
				test_die_roll_null();
				break;
			case 7:
				test_die_last_roll();
				break;
			case 8:
				test_die_last_roll_initialized();
				break;
            default:
                break;
        }
    } else
        test_all();

    return 0;
}