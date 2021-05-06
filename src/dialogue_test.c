/**
 * @file dialogue_test.c
 * @author Ivan del Horno Sotillo
 * @brief Tests the dialogue module
 * @version 0.1
 * @date 2021-04-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/dialogue.h"
#include "../include/test.h"
#include "../include/types.h"

void test_dialogue_no_cmd()
{
    Game *g = game_init();
    STATUS st = OK;
    T_Command cmd = NO_CMD;
    char str[60] = "Introduce a command: ";
    char *str2 = dialogue_print(cmd, st, g);
    PRINT_TEST_RESULT(strcmp(str2, str) == 0);
    free(str2);
    free(g);
}

void test_dialogue_game_null()
{
    Game *g = NULL;
    STATUS st = OK;
    T_Command cmd = NEXT;
    char *str2 = dialogue_print(cmd, st, g);
    PRINT_TEST_RESULT(str2 == NULL);
    free(str2);
}

void test_dialogue_status_wrong()
{
    Game *g = game_init();
    STATUS st = 3;
    T_Command cmd = NO_CMD;
    char *str2 = dialogue_print(cmd, st, g);
    PRINT_TEST_RESULT(str2 == NULL);
    free(str2);
    free(g);
}

void test_dialogue_command_wrong()
{
    Game *g = game_init();
    STATUS st = OK;
    T_Command cmd = UNKNOWN;
    char str[60] = "This is not a valid action. Try again.";
    char *str2 = dialogue_print(cmd, st, g);
    PRINT_TEST_RESULT(strcmp(str2, str) == 0);
    free(str2);
    free(g);
}

// void test_dialogue_repeated_wrong()
// {
//     Game *g = game_init();
//     STATUS st = ERROR;
//     T_Command cmd = TAKE;
//     char str[60] = "You have done this before without success.";
//     char *str2 = dialogue_print(cmd, st, g);
//     free(str2);
//     str2 = dialogue_print(cmd, st, g);
//     PRINT_TEST_RESULT(strcmp(str2, str) == 0);
//     free(str2);
//     free(g);
// }

void test_all()
{
    test_dialogue_no_cmd();
    test_dialogue_game_null();
    test_dialogue_status_wrong();
    test_dialogue_command_wrong();
    //test_dialogue_repeated_wrong();

    PRINT_PASSED_PERCENTAGE;
}

int main()
{
    printf("Dialogue test\n");
    printf("=========================\n");

    test_all();

    return 0;
}
