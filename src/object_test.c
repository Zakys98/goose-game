/** 
 * @brief It tests the object module
 * 
 * @file die_test.c
 * @author Alba Delgado
 * @version 1.0 
 * @date 19-04-2021
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>

#include "../include/object.h"
#include "../include/test.h"
#include "../include/types.h"

void test1_object_create()
{
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(o != NULL);
  object_destroy(&o);
}

void test2_object_create()
{
  Object *o;
  o = object_create(4);
  PRINT_TEST_RESULT(object_get_id(o) == 4);
  object_destroy(&o);
}

void test1_object_get_id()
{
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_get_id(o) == 5);
  object_destroy(&o);
}

void test2_object_get_id()
{
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_id(o) == NO_ID);
}

void test1_object_set_name()
{
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_name(o, "hola") == OK);
  object_destroy(&o);
}

void test2_object_set_name()
{
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_name(o, NULL) == ERROR);
  object_destroy(&o);
}

void test3_object_set_name()
{
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_name(o, "hola") == ERROR);
}

void test1_object_get_name()
{
  Object *o;
  o = object_create(5);
  object_set_name(o, "hola");
  PRINT_TEST_RESULT(strcmp(object_get_name(o), "hola") == 0);
  object_destroy(&o);
}

void test2_object_get_name()
{
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_name(o) == ERROR);
}

void test1_object_set_description()
{
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_description(o, "hola") == OK);
  object_destroy(&o);
}

void test2_object_set_description()
{
  Object *o;
  o = object_create(5);
  PRINT_TEST_RESULT(object_set_description(o, NULL) == ERROR);
  object_destroy(&o);
}

void test3_object_set_description()
{
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_description(o, "hola") == ERROR);
}

void test1_object_get_description()
{
  Object *o;
  o = object_create(5);
  object_set_description(o, "hola");
  PRINT_TEST_RESULT(strcmp(object_get_description(o), "hola") == 0);
  object_destroy(&o);
}

void test2_object_get_description()
{
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_description(o) == ERROR);
}

void test_all()
{
  test1_object_create();
  test2_object_create();
  test1_object_get_id();
  test2_object_get_id();
  test1_object_set_name();
  test2_object_set_name();
  test3_object_set_name();
  test1_object_get_name();
  test2_object_get_name();
  test1_object_set_description();
  test2_object_set_description();
  test3_object_set_description();
  test1_object_get_description();
  test2_object_get_description();

  PRINT_PASSED_PERCENTAGE;
}

/**
 * @brief Principal funtion to test the object module
 */
int main(int argc, char **argv)
{
  printf("Object test\n");
  printf("=========================\n");

  if (argc == 2)
  {
    switch (atoi(argv[1]))
    {
    case 1:
      test1_object_create();
      break;
    case 2:
      test2_object_create();
      break;
    case 3:
      test1_object_get_id();
      break;
    case 4:
      test2_object_get_id();
      break;
    case 5:
      test1_object_set_name();
      break;
    case 6:
      test2_object_set_name();
      break;
    case 7:
      test3_object_set_name();
      break;
    case 8:
      test1_object_get_name();
      break;
    case 9:
      test2_object_get_name();
      break;
    case 10:
      test1_object_set_description();
      break;
    case 11:
      test2_object_set_description();
      break;
    case 12:
      test3_object_set_description();
      break;
    case 13:
      test1_object_get_description();
      break;
    case 14:
      test2_object_get_description();
      break;
    default:
      break;
    }
  }
  else
    test_all();

  return 0;
}
