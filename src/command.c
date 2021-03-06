/** 
 * @brief It implements the command interpreter
 * 
 * @file command.c
 * @author Eva moresova
 * @version 1.0 
 * @date 15-02-2021 
 * @copyright GNU Public License
 */

#include "../include/command.h"

#include <stdio.h>
#include <strings.h>

#define CMD_LENGHT 30

// array for comapring user input and commands
char *cmd_to_str[N_CMD][N_CMDT] =
    {{"", "No command"},
     {"", "Unknown"},
     {"e", "Exit"},
     {"t", "Take"},
     {"d", "Drop"},
     {"rl", "Roll"},
	 {"m", "Move"},
     {"i", "Inspect"},
     {"", "Turnon"},
     {"", "Turnoff"},
     {"", "Open"},
	 {"", "Save"},
	 {"", "Load"}};

T_Command get_user_input() {
    T_Command cmd = NO_CMD;
    char input[CMD_LENGHT] = "";
    int i = UNKNOWN - NO_CMD + 1;
    if (scanf("%s", input) > 0) {
        cmd = UNKNOWN;
        while (cmd == UNKNOWN && i < N_CMD) {
            if (!strcasecmp(input, cmd_to_str[i][CMDS]) 
            || !strcasecmp(input, cmd_to_str[i][CMDL])) {
                cmd = i + NO_CMD;
            } else {
                i++;
            }
        }
    }
    return cmd;
}