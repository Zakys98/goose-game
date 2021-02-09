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

#include "player.h"

#include <stdio.h>

Player *player_create(Id id) {
    Player *p = (Player *)malloc(sizeof(struct player));
    if (p == NULL)
        return NULL;
    p->id = id;
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

STATUS player_set_space(Player *p, Space *s){
    if (!player_exist(p) || s == NULL)
        return ERROR;
    p->pos = s;
    return OK;
}

Space *player_get_space(Player *p){
    if (!player_exist(p))
        return NULL;
    return p->pos;
}

STATUS player_set_object(Player *p, Object *o) {
    if (!player_exist(p) || !object_exist(o))
        return ERROR;
    p->o = o;
    return OK;
}

Object *player_get_object(Player *p) {
    if (!player_exist(p))
        return NULL;
    return p->o;
}

void player_print(Player *p) {
    printf("id: %ld\n name: %s\n", p->id, p->name);
}
