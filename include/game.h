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

typedef struct _Game Game;

/**
 * @brief Game create
 *
 * @author Jiri Zak
 * @date 22-03-2021
 * 
 * @return pointer to Game
 */
Game* game_init();

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
 * @brief object getter with id
 *
 * @author Eva Moresova
 * @date 12-02-2021
 * 
 * @param game pointer to game
 * @param id id of object
 * @return object with id or NULL
 */
Object* game_get_object(Game* game, Id id);

/**
 * @brief object getter at position
 *
 * @author Eva Moresova
 * @date 12-02-2021
 * 
 * @param game pointer to game
 * @param id position in game
 * @return object with id or NULL
 */
Object* game_get_object_at_position(Game* game, int id);

/**
 * @brief player getter
 *
 * @author Eva Moresova
 * @date 12-02-2021
 * 
 * @param game pointer to game
 * @return player or NULL
 */
Player* game_get_player(Game* game);

/**
 * @brief dice getter
 *
 * @author Jiri Zak
 * @date 22-03-2021
 * 
 * @param game pointer to game
 * @return dice or NULL
 */
Dice* game_get_dice(Game* game);

/**
 * @brief open log file for output
 *
 * @author Jiri Zak
 * @date 22-03-2021
 * 
 * @param game pointer to game
 * @param filename name of the file
 */
void game_open_log_file(Game *game, char *filename);

/**
 * @brief log getter
 *
 * @author Jiri Zak
 * @date 22-03-2021
 * 
 * @param game pointer to game
 * @return FILE or NULL
 */
FILE* game_get_log_file(Game* game);

/**
 * @brief add space to game
 *
 * @author Eva Moresova
 * @date 10-02-2021
 * 
 * @param game pointer to game
 * @param space pointer to space, which is added to game
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_add_space(Game* game, Space* space);

/**
 * @brief add object to game
 *
 * @author Eva Moresova
 * @date 08-03-2021
 * 
 * @param game pointer to game
 * @param obj pointer to object, which is added to game
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_add_object(Game* game, Object* obj);

/**
 * @brief set player
 *
 * @author Eva Moresova
 * @date 22-03-2021
 * 
 * @param game pointer to game
 * @param p pointer to player
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_set_player(Game* game, Player* p);


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

/**
 * @brief Returns the arguement used after some commands (move west for example)
 * @author Ivan del Horno
 * @param game pointer to game
 * @return string of the command
 */
char *game_get_argument(Game* game);

char* game_get_description(Game* game);

#endif
