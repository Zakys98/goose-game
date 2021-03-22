/** 
 * @brief It defines player interface
 * 
 * @file player.h
 * @author Jiri Zak
 * @version 1.0 
 * @date 12-02-2021 
 * @copyright GNU Public License
 */

#include "../include/player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Player *player_create(Id id) {
    Player *p = (Player *)malloc(sizeof(struct player));
    if (p == NULL)
        return NULL;
    p->id = id;
	p->location = NO_ID;
	p->obj = NULL;
    return p;
}

STATUS player_destroy(Player **p) {
    if (!player_exist(*p))
        return FALSE;
    free(*p);
    *p = NULL;
    return OK;
}

STATUS player_exist(Player *p) {
    return p == NULL ? FALSE : TRUE;
}

Id player_get_id(Player *p) {
    if (!player_exist(p))
        return -1;
    return p->id;
}

const char *player_get_name(Player *p) {
    if (!player_exist(p))
        return NULL;
    return p->name;
}

STATUS player_set_name(Player *p, const char *str) {
    if (!player_exist(p) || str == NULL)
        return ERROR;
    if (!strcpy(p->name, str))
        return ERROR;
    return OK;
}

STATUS player_set_location(Player *p, Id s){
    if (!player_exist(p) || s == NO_ID)
        return ERROR;
    p->location = s;
    return OK;
}

Id player_get_location(Player *p){
    if (!player_exist(p))
        return NO_ID;
    return p->location;
}

STATUS player_set_object(Player *p, Object *o) {
    if (!player_exist(p) || !object_exist(o))
        return ERROR;
    p->obj = o;
    return OK;
}

Object* player_get_object(Player *p) {
    if (!player_exist(p))
        return NULL;
    return p->obj;
}

void player_print(Player *p) {
    printf("id: %ld\n name: %s\n", p->id, p->name);
}
