/** 
 * @brief It defines the link interface
 * 
 * @file link.h
 * @author Jiri Zak
 * @version 1.0 
 * @date 22-03-2021 
 * @copyright GNU Public License
 */

#ifndef DIE_H
#define DIE_H

#include "types.h"

typedef struct _Link Link;

/**
 * @brief Link create
 *
 * @author Jiri Zak
 * @date 1-03-2021
 * 
 * @param id unique id of the link
 * @return pointer to Link or NULL if error
 */
Link* link_create(Id);

/**
 * @brief Link destroy and set it to NULL
 *
 * @author Jiri Zak
 * @date 1-03-2021
 * 
 * @param l double pointer to Link
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS link_destroy(Link **);

/**
 * @brief Link name setter 
 *
 * @author Jiri Zak
 * @date 22-03-2021
 * 
 * @param l pointer to Link
 * @param str pointer to char
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS link_set_name(Link* l, char* name);

/**
 * @brief Link name getter 
 *
 * @author Jiri Zak
 * @date 22-03-2021
 * 
 * @param p pointer to Link
 * @return pointer to const char or NULL if ERROR 
 */
const char* link_get_name(Link* l);

/**
 * @brief Link first space setter 
 *
 * @author Jiri Zak
 * @date 22-03-2021
 * 
 * @param l pointer to Link
 * @param id id of the first space
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS link_set_first_space(Link* l, Id id);

/**
 * @brief Link first space getter 
 *
 * @author Jiri Zak
 * @date 22-03-2021
 * 
 * @param p pointer to Link
 * @return id of the first space or -1 if ERROR 
 */
Id link_get_first_space(Link* l);

/**
 * @brief Link second space setter 
 *
 * @author Jiri Zak
 * @date 22-03-2021
 * 
 * @param l pointer to Link
 * @param id id of the second space
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS link_set_second_space(Link* l, Id id);

/**
 * @brief Link second space getter 
 *
 * @author Jiri Zak
 * @date 22-03-2021
 * 
 * @param p pointer to Link
 * @return id of the second space or -1 if ERROR 
 */
Id link_get_second_space(Link* l);

/**
 * @brief Link opened setter 
 *
 * @author Jiri Zak
 * @date 22-03-2021
 * 
 * @param l pointer to Link
 * @param opened BOOL of the link status
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS link_set_opened(Link* l, BOOL opened);

/**
 * @brief Link opened getter 
 *
 * @author Jiri Zak
 * @date 22-03-2021
 * 
 * @param p pointer to Link
 * @return TRUE or FALSE if ERROR 
 */
BOOL link_get_opened(Link* l);

#endif