/** 
 * @brief It defines set interface
 * 
 * @file set.h
 * @author Eva Moresova
 * @version 1.0 
 * @date 01-03-2021 
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

#include <stdio.h>

typedef struct _Set Set;

/**
 * @brief getter for set size
 *
 * @author Eva Moresova
 * @date 01-03-2021 
 * 
 * @param s pointer to set
 * @return integer size of set, -1 in case of error
 */
int set_get_size(Set* s);

/**
 * @brief creates and initializes a set
 *
 * @author Eva Moresova
 * @date 01-03-2021 
 * 
 * @return pointer to created set or NULL in case of error
 */
Set* set_create(); 

/**
 * @brief destructor for set
 *
 * @author Eva Moresova
 * @date 01-03-2021 
 * 
 * @param s double pointer to set
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS 	set_destroy(Set** s);

/**
 * @brief adds new element with specified id to the set. If the element
 * is in the set already no changes are made.
 *
 * @author Eva Moresova
 * @date 01-03-2021 
 * 
 * @param s pointer to set
 * @param id of the new element
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS 	set_add(Set* s, Id id);

/**
 * @brief deletes element from set with specified id
 *
 * @author Eva Moresova
 * @date 01-03-2021 
 * 
 * @param s pointer to set
 * @param id of the element to be deleted
 * @return STATUS OK if the element was deleted, 
 * ERROR if the set is NULL or empty
 */
STATUS 	set_delete(Set* s, Id id);

/**
 * @brief prints the contents of a specified set
 *
 * @author Eva Moresova
 * @date 01-03-2021 
 * 
 * @param s pointer to set
 * @param fp file pointer, set is printed to this file
 * @return the number of printed characters or -1 in case of error
 */
int set_print(Set* s, FILE* fp);


/**
 * @brief returns array of Ids of elements inside the set
 *
 * @author Eva Moresova
 * @date 08-03-2021 
 * 
 * @param s pointer to set
 * @return array of Id
 */
Id* set_get_elements(Set* s);

#endif