/**
 * @brief Implementation of inventory
 *
 * @file inventory.c
 * @author Ivan del Horno and Eva Moresova
 * @version 1.0
 * @date 22-03-2021
 * @copyright GNU Public License
 */

#include "../include/inventory.h"

#include <stdlib.h>
#include <stdio.h>

#define MIN_CAP_INV 1

struct _Inventory
{
	Set *objects; //Pointer to the set of items
	int capacity; //Capacity of the inventory
};

// Private functions

//Should this be private or public?

/**
 * @brief Checks if the inventory contains a given ID
 * @author Ivan del Horno
 * @param i Pointer to the inventory to be checked
 * @param id ID of the object to search
 * @return TRUE if it is conatained, FALSE if it is not
 */
BOOL _inventory_contains_id(Inventory *i, Id id);

BOOL _inventory_contains_id(Inventory *i, Id id)
{
	int a, n;
	Id *ids = NULL;

	if (i == NULL || id == NO_ID)
	{
		return FALSE;
	}

	n = set_get_size(i->objects);
	ids = set_get_elements(i->objects);

	if (ids == NULL)
	{
		return FALSE;
	}

	for (a = 0; a < n; a++)
	{
		if (ids[a] == id)
		{
			return TRUE;
		}
	}

	return FALSE;
}

// Implementation

Inventory *inventory_create(int cap)
{
	Inventory *i = NULL;

	if (cap < MIN_CAP_INV)
		return NULL;

	i = (Inventory *)malloc(sizeof(Inventory));
	if (i == NULL)
	{
		return NULL;
	}

	i->objects = set_create();
	if (i->objects == NULL)
	{
		free(i);
		return NULL;
	}

	i->capacity = cap;

	return i;
}

void inventory_destroy(Inventory **i)
{
	if (i == NULL || *i == NULL)
	{
		return;
	}
	set_destroy(&(*i)->objects);
	free(*i);
	*i = NULL;
	return;
}

BOOL inventory_isFull(Inventory *i)
{
	if (i == NULL)
	{
		return TRUE;
	}

	if (set_get_size(i->objects) == i->capacity)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL inventory_isEmpty(Inventory *i)
{
	if (i == NULL)
	{
		return TRUE;
	}

	return (set_is_empty(i->objects) == TRUE);
}

STATUS inventory_add_id(Inventory *i, Id id)
{
	if (i == NULL || id == NO_ID || inventory_isFull(i) == TRUE)
	{
		return ERROR;
	}

	return set_add(i->objects, id);
}

STATUS inventory_del_id(Inventory *i, Id id)
{
	if (i == NULL)
	{
		return ERROR;
	}

	return (set_delete(i->objects, id));
}

STATUS inventory_add(Inventory *i, Object *o)
{
	if (i == NULL || o == NULL || inventory_isFull(i))
		return ERROR;

	return set_add(i->objects, object_get_id(o));
}


// IDK how to do it to get the object because
// with the set module there is no function that
// returns an object, so this looks impossible for me
Object *inventory_get(Inventory *i, Id id)
{
	int j, pos = 0;
	Id *ids = NULL;
	Object *o = NULL;

	if (i == NULL)
		return NULL;

	ids = set_get_elements(i->objects);
	if (ids == NULL)
	{
		return NULL;
	}

	for (j = 0; j < i->capacity; j++)
	{
		if (ids[j] == id)
		{
			pos = j;
		}
	}
}

int inventory_get_nObjects(Inventory *i)
{
	if (i == NULL)
	{
		return -1;
	}

	return set_get_size(i->objects);
}

int inventory_get_capacity(Inventory *i)
{
	if (i == NULL)
	{
		return -1;
	}

	return i->capacity;
}

int inventory_print(Inventory *inv, FILE *f)
{
	int c;

	if (inv == NULL)
	{
		return -1;
	}

	c = fprintf(f, "Inventory: ");
	c += set_print(inv->objects, f);
	return c;
}