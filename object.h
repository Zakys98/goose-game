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

#ifndef OBJECT_H
#define OBJECT_H

#include "space.h"
#include "types.h"

typedef struct obj {
    Id id;
    char name[WORD_SIZE + 1];
} Object;

Object *object_create(Id);
STATUS object_destroy(Object **);
STATUS object_exist(Object *);
Id object_get_id(Object *);
const char *object_get_name(Object *);
STATUS object_set_name(Object *, const char *);
void object_print(Object *);

#endif
