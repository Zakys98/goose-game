/**
 * @brief Represents an inventory
 *
 * @file inventory.h
 * @author Ivan del Horno and Eva Moresova
 * @version 1.0
 * @date 22-03-2021
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "object.h"
#include "set.h"

#define MIN_CAP_INV 1

typedef struct _Inventory Inventory;

/**
 * @brief creates and initializes an inventory
 *
 * @author Eva Moresova
 * @date 22-03-2021 
 * 
 * @param cap capacity of backpack
 * @return pointer to created inventory or NULL in case of error
 */
Inventory *inventory_create(int cap);

/**
 * @brief destructor for inventory
 *
 * @author Ivan del Horno
 * @date 22-03-2021 
 * 
 * @param i double pointer to inventory
 * @return STATUS ERROR = 0, OK = 1
 */
void inventory_destroy(Inventory **i);

/**
 * @brief Checks if the given inventory is full
 * 
 * @param i Pointer to the inventory to be checked
 * @return TRUE if it is full, NULL if it is not
 */
BOOL inventory_isFull(Inventory *i);

/**
 * @brief Checks if the given inventory is full
 * 
 * @param i Pointer to the inventory to be checked
 * @return TRUE if it is empty, NULL if it is not
 */
BOOL inventory_isEmpty(Inventory *i);

/**
 * @brief Adds an ID to the inventory
 * @author Ivan del Horno
 * @param i Pointer to the inventory
 * @param id Id of object to add
 * @return OK or ERROR
 */
STATUS inventory_add_id(Inventory *i, Id id);

/**
 * @brief Deletes an object from the inventory given its Id
 * @author Ivan del Horno
 * @param i Pointer to the inventory
 * @param id Id of the object to delete
 * @return OK or ERROR
 */
STATUS inventory_del_id(Inventory *i, Id id);

/**
 * @brief Adds an object to an inventory
 * @author Ivan del Horno and Eva Moresova
 * @param i Pointer to the inventory
 * @param o Pointer to the object
 * @return ERROR or OK
 */
STATUS inventory_add_object(Inventory *i, Object *o);



    /**
 * @brief Get the number of objects inside an inventory
 * @author Ivan del Horno
 * @param i Pointer to the inventory
 * @return Number of objects inside the inventory or -1 in case of error
 */
int inventory_get_nObjects(Inventory *i);

/**
 * @brief Get the max number of objects inside a set
 * @author Ivan del Horno
 * @param i Pointer to the inventory
 * @return Int number of max objects or -1 in case of error
 */
int inventory_get_capacity(Inventory *i);

/**
 * @brief Returns an array of the elements in the inventory
 * @author Ivan del Horno
 * @param i Pointer to the inventory
 * @return Array of Ids or NULL if error
 */
Id* inventory_get_elements(Inventory *i);

/**
 * @brief Checks if a given ID is inside the inventory
 * @author Ivan del Horno
 * @param i Pointer to the inventory
 * @param id Id to search
 * @return TRUE if it is contained, or FALSE
 */
BOOL inventory_has_id(Inventory *i, Id id);

/**
 * @brief prints the contents of a specified inventory
 *
 * @author Ivan del Horno and Eva Moresova
 * @date 22-03-2021 
 * 
 * @param i pointer to inventory
 * @param f file pointer
 * @return the number of printed characters or -1 in case of error
 */
int inventory_print(Inventory *inv, FILE *f);

#endif