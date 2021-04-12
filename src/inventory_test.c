/**
 * @file inventory_test.c
 * @author Ivan del Horno
 * @brief Tests the inventory module
 * @version 0.1
 * @date 2021-04-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>
#include <stdio.h>

#include "../include/inventory.h"
#include "../include/test.h"
#include "../include/types.h"

void test_inventory_create()
{
    Inventory *i = inventory_create(5);
    PRINT_TEST_RESULT(i != NULL);
}

void test_inventory_create_wrong_cap()
{
    Inventory *i = inventory_create(-1);
    PRINT_TEST_RESULT(i == NULL);
}

void test_inventory_destroy()
{
    Inventory *i = inventory_create(5);
    inventory_destroy(&i);
    PRINT_TEST_RESULT(i == NULL);
}

void test_inventory_destroy_null()
{
    Inventory *i = NULL;
    inventory_destroy(&i);
    PRINT_TEST_RESULT(i == NULL);
}

void test_inventory_get_capacity()
{
    Inventory *i = inventory_create(5);
    PRINT_TEST_RESULT(inventory_get_capacity(i) == 5);
    inventory_destroy(&i);
}

void test_inventory_get_capacity_null()
{
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_get_capacity(i) == -1);
}

void test_inventory_add_id()
{
    Inventory *i = inventory_create(5);
    PRINT_TEST_RESULT(inventory_add_id(i, 123) == OK);
    inventory_destroy(&i);
}

void test_inventory_add_no_id()
{
    Inventory *i = inventory_create(5);
    PRINT_TEST_RESULT(inventory_add_id(i, NO_ID) == ERROR);
    inventory_destroy(&i);
}

void test_inventory_add_id_to_null()
{
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_add_id(i, 123) == ERROR);
}

void test_inventory_del_id()
{
    Inventory *i = inventory_create(5);
    inventory_add_id(i, 123);
    PRINT_TEST_RESULT(inventory_del_id(i, 123) == OK);
    inventory_destroy(&i);
}

void test_inventory_del_notexisting_id()
{
    Inventory *i = inventory_create(5);
    inventory_add_id(i, 123);
    PRINT_TEST_RESULT(inventory_del_id(i, 124) == ERROR);
    inventory_destroy(&i);
}

void test_inventory_del_noid()
{
    Inventory *i = inventory_create(5);
    inventory_add_id(i, 123);
    PRINT_TEST_RESULT(inventory_del_id(i, NO_ID) == ERROR);
    inventory_destroy(&i);
}

void test_inventory_del_id_from_null()
{
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_del_id(i, 123) == ERROR);
}

void test_inventory_isFull_it_is()
{
    Inventory *i = inventory_create(1);
    inventory_add_id(i, 123);
    PRINT_TEST_RESULT(inventory_isFull(i) == TRUE);
    inventory_destroy(&i);
}

void test_inventory_isFull_it_is_not()
{
    Inventory *i = inventory_create(2);
    inventory_add_id(i, 123);
    PRINT_TEST_RESULT(inventory_isFull(i) == FALSE);
    inventory_destroy(&i);
}

void test_inventory_isFull_from_null()
{
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_isFull(i) == TRUE);
}

void test_inventory_isEmpty_it_is()
{
    Inventory *i = inventory_create(1);
    PRINT_TEST_RESULT(inventory_isEmpty(i) == TRUE);
    inventory_destroy(&i);
}

void test_inventory_isEmpty_it_is_not()
{
    Inventory *i = inventory_create(1);
    inventory_add_id(i, 123);
    PRINT_TEST_RESULT(inventory_isEmpty(i) == FALSE);
    inventory_destroy(&i);
}

void test_inventory_isEmpty_from_null()
{
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_isEmpty(i) == TRUE);
}

void test_inventory_add_object()
{
    Inventory *i = inventory_create(4);
    Object *o = object_create(12);
    PRINT_TEST_RESULT(inventory_add_object(i, o) == OK);
    object_destroy(&o);
    inventory_destroy(&i);
}

void test_inventory_add_object_null_obj()
{
    Inventory *i = inventory_create(4);
    Object *o = NULL;
    PRINT_TEST_RESULT(inventory_add_object(i, o) == ERROR);
    inventory_destroy(&i);
}

void test_inventory_add_object_to_null()
{
    Inventory *i = NULL;
    Object *o = object_create(12);
    PRINT_TEST_RESULT(inventory_add_object(i, o) == ERROR);
    object_destroy(&o);
}

void test_inventory_get_nobjects()
{
    Inventory *i = inventory_create(4);
    Object *o = object_create(12);
    inventory_add_object(i, o);
    inventory_add_id(i, 13);
    PRINT_TEST_RESULT(inventory_get_nObjects(i) == 2);
    object_destroy(&o);
    inventory_destroy(&i);
}

void test_inventory_get_nobjects_from_null()
{
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_get_nObjects(i) == -1);
}

void test_inventory_get_elements()
{
    Inventory *i = inventory_create(4);
    inventory_add_id(i, 13);
    PRINT_TEST_RESULT(inventory_get_elements(i) != NULL);
    inventory_destroy(&i);
}

void test_inventory_get_elements_null()
{
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_get_elements(i) == NULL);
}

void test_inventory_has_id()
{
    Inventory *i = inventory_create(4);
    inventory_add_id(i, 14);
    PRINT_TEST_RESULT(inventory_has_id(i, 14) == TRUE);
    inventory_destroy(&i);
}

void test_inventory_has_id_no()
{
    Inventory *i = inventory_create(4);
    inventory_add_id(i, 14);
    PRINT_TEST_RESULT(inventory_has_id(i, 13) == FALSE);
    inventory_destroy(&i);
}

void test_inventory_has_id_noid()
{
    Inventory *i = inventory_create(4);
    inventory_add_id(i, 14);
    PRINT_TEST_RESULT(inventory_has_id(i, NO_ID) == FALSE);
    inventory_destroy(&i);
}

void test_inventory_has_id_null()
{
    Inventory *i = NULL;
    PRINT_TEST_RESULT(inventory_has_id(i, 14) == FALSE);
}



void test_all()
{
    test_inventory_create();
    test_inventory_create_wrong_cap();
    test_inventory_destroy();
    test_inventory_destroy_null();
    test_inventory_get_capacity();
    test_inventory_get_capacity_null();
    test_inventory_add_id();
    test_inventory_add_no_id();
    test_inventory_add_id_to_null();
    test_inventory_del_id();
    test_inventory_del_notexisting_id();
    test_inventory_del_noid();
    test_inventory_del_id_from_null();
    test_inventory_isFull_it_is();
    test_inventory_isFull_it_is_not();
    test_inventory_isFull_from_null();
    test_inventory_isEmpty_it_is();
    test_inventory_isEmpty_it_is_not();
    test_inventory_isEmpty_from_null();
    test_inventory_add_object();
    test_inventory_add_object_null_obj();
    test_inventory_add_object_to_null();
    test_inventory_get_nobjects();
    test_inventory_get_nobjects_from_null();
    test_inventory_get_elements();
    test_inventory_get_elements_null();
    test_inventory_has_id();
    test_inventory_has_id_no();
    test_inventory_has_id_noid();
    test_inventory_has_id_null();

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
int main(int argc, char **argv)
{
    printf("Inventory test\n");
    printf("=========================\n");

    test_all();

    return 0;
}