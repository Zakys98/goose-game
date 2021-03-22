/**
 * @brief Implementation of inventory
 *
 * @file inventory.c
 * @author Eva Moresova
 * @version 1.0
 * @date 22-03-2021
 * @copyright GNU Public License
 */

#include "../include/inventory.h"

#include <stdlib.h>
#include <stdio.h>

struct _Inventory {
	Set* objects;
	int capacity;
};

// Private functions


// Implementation

Inventory* inventory_create(int cap) {
	if (cap <= 0) return NULL;

	Inventory* i = malloc(sizeof(struct _Inventory));
	if (i != NULL) {
		i->capacity = cap;
		i->objects = set_create();
		if (i->objects == NULL)
			return NULL;
	}
	return i;
} 

void inventory_destroy(Inventory** i) {
	if (i == NULL || *i == NULL)
		return;
	set_destroy(&(*i)->objects);
	free(*i);
	*i = NULL;
}

BOOL inventory_isFull(Inventory* i) {
	if (set_get_size(i->objects) == i->capacity) 
		return TRUE;

	return FALSE;
}

BOOL inventory_isEmpty(Inventory* i) {
	
	if (set_get_size(i->objects) == i->capacity) 
		return TRUE;

	return FALSE;
}

// STATUS inventory_set(Inventory* i, Object* o) {
// 	if (i == NULL || o == NULL) return ERROR;

// 	return OK;
// }

Object* inventory_get(Inventory* i, Id id) {
	if(i == NULL) return NULL;

	if (set_delete(i->objects, id) == ERROR) return NULL;
	//return game_get_object(g, id);
	return NULL;
}

STATUS inventory_add(Inventory* i, Object* o) {
	if (i == NULL || o == NULL || inventory_isFull(i)) 
		return ERROR;

	return set_add(i->objects, object_get_id(o));
}

int inventory_print(Inventory* i, FILE* f) { 
	if (i == NULL) return -1;

	int c = fprintf(f, "Inventory: ");
	c += set_print(i->objects, f);
	return c;
}