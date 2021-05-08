/** 
 * @brief It defines a space
 * 
 * @file space.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "link.h"
#include "object.h"
#include "types.h"

typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1

Space* space_create(Id id);
STATUS space_destroy(Space** space);
Id space_get_id(Space* space);
STATUS space_set_name(Space* space, char* name);
STATUS space_set_description(Space *space, char *description);
STATUS space_set_detailed_description(Space *space, char *detailed_description);
const char* space_get_name(Space* space);
STATUS space_set_north(Space* space, Link* l);
Link* space_get_north(Space* space);
STATUS space_set_south(Space* space, Link* l);
Link* space_get_south(Space* space);
STATUS space_set_east(Space* space, Link* l);
STATUS space_set_gdesc(Space* space, int line, char* name);
Link* space_get_east(Space* space);
STATUS space_set_west(Space* space, Link* l);
Link* space_get_west(Space* space);
STATUS space_set_up(Space *space, Link *l);
Link *space_get_up(Space *space);
STATUS space_set_down(Space *space, Link *l);
Link *space_get_down(Space *space);
STATUS space_add_object(Space* space, Id id);
STATUS space_remove_object(Space* space, Id id);
char* space_get_gdesc(Space* space, int line);
Id* space_get_objects(Space* s);
int space_objects_count(Space* s);
STATUS space_set_illumination(Space *space, BOOL illumination);
BOOL space_get_illumination(Space *space);
STATUS space_print(Space* space);
const char *space_get_description(Space *space);
const char *space_get_detailed_description(Space *space);
BOOL space_hasObject(Space *space, Id id);

STATUS space_save(FILE*, Space*);
#endif
