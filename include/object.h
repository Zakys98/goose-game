/** 
 * @brief It defines the object interface
 * 
 * @file object.h
 * @author Jiri Zak
 * @version 1.0 
 * @date 12.02.2021 
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

#define MAX_OBJECTS 50

typedef struct _Obj Object;

/**
 * @brief Object create
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param id id of object
 * @return pointer to Obejct
 */
Object *object_create(Id);

/**
 * @brief Object destroy and set it to NULL
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param o double pointer to Object
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS object_destroy(Object **);

/**
 * @brief Check if object is not NULL
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param o pointer to Object
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS object_exist(Object *);

/**
 * @brief Object id getter 
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param o pointer to Object
 * @return Id or -1 if ERROR
 */
Id object_get_id(Object *);

/**
 * @brief Object name getter 
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param o pointer to Object
 * @return pointer to const char or NULL if ERROR 
 */
const char *object_get_name(Object *);

/**
 * @brief Object name setter 
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param o pointer to Object
 * @param str pointer to const char
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS object_set_name(Object *, const char *);

/**
 * @brief Object location setter 
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param o pointer to Object
 * @param id id of location
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS object_set_location(Object* , Id);

/**
 * @brief Object location getter 
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param o pointer to Object
 * @return Id or NO_ID if ERROR 
 */
Id object_get_location(Object*);

/**
 * @brief Object print
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param o pointer to Object
 */
void object_print(Object *);

#endif
