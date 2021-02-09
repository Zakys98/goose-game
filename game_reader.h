/** 
 * @brief It defines the game interface
 * for each command
 * 
 * @file game.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H

#include "space.h"
#include "game.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

STATUS game_create_from_file(Game* game, char* filename);
STATUS game_load_spaces(Game* game, char* filename);

#define GAME_READER_H

#endif
