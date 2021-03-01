/** 
 * @brief It defines an interface for reading the game from a file
 * 
 * @file game_reader.h
 * @author Eva Moresova
 * @version 1.0 
 * @date 10-02-2021 
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "space.h"
#include "game.h"

STATUS game_load_spaces (Game* game, char* line);
STATUS game_load_objects (Game* game, char* line);

#endif
