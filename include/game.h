/** 
 * @brief It defines the game interface
 * for each command
 * 
 * @file game.h
 * @author Eva Moresova
 * @version 1.0 
 * @date 17-02-2021 
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>

#include "command.h"
#include "die.h"
#include "object.h"
#include "player.h"
#include "space.h"

typedef struct _Game {
    Player* player;
    Object* objects[MAX_OBJECTS];
    Space* spaces[MAX_SPACES + 1];
    T_Command last_cmd;
    Dice* dice;
    FILE* log;
} Game;

/**
 * @brief inicializes the game, spaces, player and object position 
 * and last command
 * 
 * @param game pointer to game
 * @return STATUS OK = 1
 */
STATUS game_create(Game* game);

/**
 * @brief loads the spaces, player and object positions from a file
 * 
 * @param game pointer to game 
 * @param filename name of file to load the game from
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_create_from_file(Game* game, char* filename);

/**
 * @brief invokes callback function of the specified command
 * 
 * @param game pointer to game 
 * @param cmd new command to execute
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_update(Game* game, T_Command cmd);

/**
 * @brief frees all the game resources
 * 
 * @param game pointer to game
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_destroy(Game* game);

/**
 * @brief indicates if game is over
 * 
 * @param game pointer to game
 * @return always returns false
 */
BOOL game_is_over(Game* game);

/**
 * @brief prints the current state of game
 * 
 * @param game pointer to game
 */
void game_print_data(Game* game);

/**
 * @brief space getter by id
 *
 * @author Eva Moresova
 * @date 12-02-2021
 * 
 * @param game pointer to game 
 * @param id the id of space
 * @return pointer to space with specified id
 */
Space* game_get_space(Game* game, Id id);

/**
 * @brief player location getter
 *
 * @author Eva Moresova
 * @date 12-02-2021
 * 
 * @param game pointer to game
 * @return Id of the space player is currently at
 */
Id game_get_player_location(Game* game);

/**
 * @brief object location getter
 *
 * @author Eva Moresova
 * @date 12-02-2021
 * 
 * @param game pointer to game
 * @return Id of the space object is placed at
 */
//Id     game_get_object_location(Game* game);

Object* game_get_object(Game* game, Id id);

/**
 * @brief last command getter
 * 
 * @param game pointer to game
 * @return last command
 */
T_Command game_get_last_command(Game* game);

/**
 * @brief loads spaces from a file, implemented in game_reader.c
 * 
 * @param game pointer to game
 * @param filename file to load the spaces from
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_load_game(Game* game, char* filename);

/**
 * @brief get number of objects
 * 
 * @param game pointer to game
 * @return number or if ERROR -1
 */
int game_get_number_object(Game* game);

/**
 * @brief indicates if log file is set
 * 
 * @param game pointer to game
 * @return returns true if log file is created returns false otherwise
 */
BOOL game_logfile_exist(Game* game);

#endif
