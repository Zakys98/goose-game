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

#include "types.h"
#include "object.h"

typedef struct player {
    Id id;
    char name[WORD_SIZE + 1];
    // location
    Object *o;
} Player;

Player* player_create(Id);
STATUS player_destroy(Player **);
Id player_get_id(Player *);
void player_set_id(Player *, Id);
const char* player_get_name(Player *);
void player_set_name(Player *, const char *);
void player_set_object(Player *, Object *);
Object* player_get_object(Player *);
void player_print(Player *);

#endif