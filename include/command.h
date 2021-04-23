/**
 * @brief It implements the command interpreter
 *
 * @file command.h
 * @author Eva Moresova
 * @version 1.0
 * @date 15-02-2021
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#define N_CMDT 2
#define N_CMD 14

typedef enum enum_CmdType {
    CMDS,
    CMDL
} T_CmdType;

// enum for commands type
typedef enum enum_Command {
    NO_CMD = -1,
    UNKNOWN,
    EXIT,
    NEXT,
    BACK,
    TAKE,
    DROP,
    ROLL,
    LEFT,
    RIGHT,
    MOVE,
    INSPECT,
    TURNON,
    TURNOFF
} T_Command;

/**
 * @brief scan user input and interpret it to command
 *
 * @author Eva Moresova
 * @date 15-02-2021
 * @return Command type
 */
T_Command get_user_input();

#endif
