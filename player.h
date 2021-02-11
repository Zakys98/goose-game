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

#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "space.h"
#include "types.h"

typedef struct player {
    Id id;
    char name[WORD_SIZE + 1];
    Id location;
    Object *obj;
} Player;

Player*     player_create(Id);
STATUS      player_destroy(Player **);
STATUS      player_exist(Player *);
Id          player_get_id(Player *);
const char* player_get_name(Player *);
STATUS      player_set_name(Player *, const char *);
STATUS      player_set_location(Player *, Id);
Id      	player_get_location(Player *);
STATUS      player_set_object(Player *, Object *);
Object*     player_get_object(Player *);
void        player_print(Player *);

#endif