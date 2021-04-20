/**
 * @brief It tests player module
 *
 * @file player_test.c
 * @author Alba Delgado
 * @version 1.0
 * @date 20/04/2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/player.h"
#include "../include/test.h"

void test1_player_create()
{
    Player *p;
    p = player_create(4,1);
    PRINT_TEST_RESULT(p != NULL);
    player_destroy(&p);
}

void test2_player_create()
{
    Player *p;
    p = player_create(4,1);
    PRINT_TEST_RESULT(player_get_id(p) == 4);
    player_destroy(&p);
}

void test1_player_get_id()
{
    Player *p;
    p = player_create(4,1);
    PRINT_TEST_RESULT(player_get_id(p) == 4);
    player_destroy(&p);
}

void test2_player_get_id()
{
    Player *p = NULL;
    PRINT_TEST_RESULT(player_get_id(p) == NO_ID);
}

void test1_player_set_name()
{
    Player *p;
    p = player_create(4,1);
    PRINT_TEST_RESULT(player_set_name(p, "hola") == OK);
    player_destroy(&p);
}

void test2_player_set_name()
{
    Player *p;
    p = player_create(4,1);
    PRINT_TEST_RESULT(player_set_name(p, NULL) == ERROR);
    player_destroy(&p);
}

void test3_player_set_name()
{
    Player *p = NULL;
    PRINT_TEST_RESULT(player_set_name(p, "hola") == ERROR);
}

void test1_player_get_name()
{
    Player *p;
    p = player_create(4,1);
    player_set_name(p, "hola");
    PRINT_TEST_RESULT(strcmp(player_get_name(p), "hola") == 0);
    player_destroy(&p);
}

void test2_player_get_name()
{
    Player *p = NULL;
    PRINT_TEST_RESULT(player_get_name(p) == ERROR);
}

void test1_player_set_player_location()
{
    Player *p;
    p = player_create(4,1);
    PRINT_TEST_RESULT(player_set_location(p, 5) == OK);
    player_destroy(&p);
}

void test2_player_set_player_location()
{
    Player *p;
    p = player_create(4,1);
    PRINT_TEST_RESULT(player_set_location(p, NO_ID) == ERROR);
    player_destroy(&p);
}

void test3_player_set_player_location()
{
    Player *p = NULL;
    PRINT_TEST_RESULT(player_set_location(p, 5) == ERROR);
}

void test1_player_get_player_location()
{
    Player *p;

    p = player_create(4,1);
    player_set_location(p, 5);
    PRINT_TEST_RESULT(player_get_location(p) == 5);
    player_destroy(&p);
}

void test2_player_get_player_location()
{
    Player *p = NULL;

    PRINT_TEST_RESULT(player_get_location(p) == NO_ID);
}

void test1_player_get_numObj()
{
    Player *p;
    p = player_create(4,1);
    PRINT_TEST_RESULT(player_getnObjects(p) == 0);
    player_destroy(&p);
}

void test2_player_get_numObj()
{
    Player *p = NULL;
    PRINT_TEST_RESULT(player_getnObjects(p) == ERROR);
}

void test_all()
{
    test1_player_create();
    test2_player_create();
    test1_player_get_id();
    test2_player_get_id();
    test1_player_set_name();
    test2_player_set_name();
    test3_player_set_name();
    test1_player_get_name();
    test2_player_get_name();
    test1_player_set_player_location();
    test2_player_set_player_location();
    test3_player_set_player_location();
    test1_player_get_player_location();
    test2_player_get_player_location();
    test1_player_get_numObj();
    test2_player_get_numObj();

    PRINT_PASSED_PERCENTAGE;
}

/**
 * @brief Principal funtion to test the object module
 */
int main(int argc, char **argv)
{
    printf("Player test\n");
    printf("=========================\n");

    if (argc == 2)
    {
        switch (atoi(argv[1]))
        {
        case 1:
            test1_player_create();
            break;
        case 2:
            test2_player_create();
            break;
        case 3:
            test1_player_get_id();
            break;
        case 4:
            test2_player_get_id();
            break;
        case 5:
            test1_player_set_name();
            break;
        case 6:
            test2_player_set_name();
            break;
        case 7:
            test3_player_set_name();
            break;
        case 8:
            test1_player_get_name();
            break;
        case 9:
            test2_player_get_name();
            break;
        case 10:
            test1_player_set_player_location();
            break;
        case 11:
            test2_player_set_player_location();
            break;
        case 12:
            test3_player_set_player_location();
            break;
        case 13:
            test1_player_get_player_location();
            break;
        case 14:
            test2_player_get_player_location();
            break;
        case 15:
            test1_player_get_numObj();
            break;
        case 16:
            test2_player_get_numObj();
            break;
        default:
            break;
        }
    }
    else
        test_all();

    return 0;
}