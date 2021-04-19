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

/**
 * Structure for Player
 * Id id
 * char[] name
 * id location 
 * Object *obj
 */
struct _Player {
    Id id; 		//Id of the player
    char name[WORD_SIZE + 1]; 	//Name of the player
    Id location;	 //Id of the location of the player
    Inventory *inventory; 	//Inventory of the player
};

Player* player_create(Id id, int cap)
{
    Player *p = NULL;

    if (id == NO_ID || cap < MIN_CAP_INV)
    {
        return NULL;
    }

    p = (Player *)malloc(sizeof(struct _Player));
    if (p == NULL)
    {
        return NULL;
    }

    p->inventory = inventory_create(cap);
    if (p->inventory == NULL)
        return NULL;
    p->id = id;
    p->location = NO_ID;
    return p;
}

STATUS player_destroy(Player **p)
{
    if (!player_exist(*p))
    {
        return FALSE;
    }
    inventory_destroy(&(*p)->inventory);
    free(*p);
    *p = NULL;
    return OK;
}

STATUS player_exist(Player *p)
{
    return p == NULL ? FALSE : TRUE;
}

Id player_get_id(Player *p)
{
    if (!player_exist(p))
        return -1;
    return p->id;
}

const char *player_get_name(Player *p)
{
    if (!player_exist(p))
        return NULL;
    return p->name;
}

STATUS player_set_name(Player *p, const char *str)
{
    if (!player_exist(p) || str == NULL)
        return ERROR;
    if (!strcpy(p->name, str))
        return ERROR;
    return OK;
}

STATUS player_set_location(Player *p, Id s)
{
    if (!player_exist(p) || s == NO_ID)
        return ERROR;
    p->location = s;
    return OK;
}

Id player_get_location(Player *p)
{
    if (!player_exist(p))
        return NO_ID;
    return p->location;
}

Inventory *player_get_inventory(Player *p) {
	if (p == NULL) return NULL;
	return p->inventory;
}

STATUS player_add_object(Player *p, Object *o)
{
    if (!player_exist(p) || !object_exist(o))
        return ERROR;
    return inventory_add_id(p->inventory, object_get_id(o));
}

STATUS player_delete_object(Player *p, Object *o)
{
    if (!player_exist(p) || !object_exist(o))
        return ERROR;
    return inventory_del_id(p->inventory, object_get_id(o));
}

BOOL player_inventory_full(Player *p)
{
    if (p == NULL)
        return TRUE;

    return inventory_isFull(p->inventory);
}

void player_print(Player *p)
{
    printf("id: %ld\n name: %s\n", p->id, p->name);
}
