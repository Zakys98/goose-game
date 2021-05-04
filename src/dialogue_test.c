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
    PRINT_TEST_RESULT(strcmp(dialogue_print(cmd, st, g), str) == 0);
}

void test_all()
{

    PRINT_PASSED_PERCENTAGE;
}

int main()
{
    printf("Dialogue test\n");
    printf("=========================\n");

    test_all();

    return 0;
}
