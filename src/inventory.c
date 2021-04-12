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



struct _Inventory
{
	Set *objects; //Pointer to the set of items
	int capacity; //Capacity of the inventory
};



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

STATUS inventory_add_object(Inventory *i, Object *o)
{
	if (i == NULL || o == NULL || inventory_isFull(i))
		return ERROR;

	return set_add(i->objects, object_get_id(o));
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

Id *inventory_get_elements(Inventory *i)
{
	if (i == NULL)
	{
		return NULL;
	}

	return set_get_elements(i->objects);
}

BOOL inventory_has_id(Inventory *i, Id id)
{
	int j;
	Id *ids = NULL;

	if (i == NULL || id == NO_ID)
	{
		return FALSE;
	}

	ids = inventory_get_elements(i);
	if (ids == NULL)
	{
		return FALSE;
	}

	for (j = 0; j < i->capacity; j++)
	{
		if (ids[j] == id)
		{
			return TRUE;
		}
	}

	return FALSE;
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