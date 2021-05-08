/**
 * @file dialogue.h
 * @author Ivan del Horno Sotillo
 * @brief Defines the Dialogue interface
 * @version 0.1
 * @date 2021-04-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "types.h"
#include "space.h"
#include "command.h"
#include "game.h"

/**
 * @brief Function that returns the dialogue based on the input command and if it was executed correctly or not
 * @author Ivan del Horno
 * @param cmd T_Command
 * @param st Status of the command (ERROR or OK)
 * @return Returns a pointer to a char where the text to be printed is contained
 */
char *dialogue_cmd_print(T_Command cmd, STATUS st, Game *game);

/**
 * @brief Function that returns a dialogue based on the rule executed
 * 
 * @param rule 
 * @param game 
 * @return char* 
 */
char *dialogue_rule_print(T_Rules rule, Game *game);

#endif