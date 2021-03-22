/**
 * @brief Represents an inventory
 *
 * @file inventory.h
 * @author Eva Moresova
 * @version 1.0
 * @date 22-03-2021
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "object.h"
#include "set.h"

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
Inventory* inventory_create(int); 

/**
 * @brief destructor for inventory
 *
 * @author Eva Moresova
 * @date 22-03-2021 
 * 
 * @param i double pointer to inventory
 * @return STATUS ERROR = 0, OK = 1
 */
void inventory_destroy(Inventory**);

BOOL inventory_isFull(Inventory*);
STATUS inventory_set(Inventory*, Object*);
Object* inventory_get(Inventory*, Id);
STATUS inventory_add(Inventory*, Object*);

/**
 * @brief prints the contents of a specified inventory
 *
 * @author Eva Moresova
 * @date 22-03-2021 
 * 
 * @param i pointer to inventory
 * @param f file pointer
 * @return the number of printed characters or -1 in case of error
 */
int inventory_print(Inventory*, FILE*);


#endif