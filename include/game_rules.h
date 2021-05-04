/**
 * @file game_rules.c
 * @author Ivan del Horno Sotillo
 * @brief Library for game rules module
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H


#include "types.h"
#include "game.h"

#include <stdio.h>

/**********************************
 *        Public Functions        *
 **********************************/

/**
 * @brief Executes a random command (or no command)
 * 
 * @param game Pointer to the game
 * @return OK if the command was executed correctly, ERROR otherwise
 */
STATUS game_rules_random_command(Game* game);

#endif