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

#include <stdio.h>

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

/**
 * @brief Object description setter
 *
 * @author Alba Delgado
 * @date 12-04-2021
 * 
 * @param object pointer to Object
 * @param description description of the object
 * 
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS object_set_description(Object *obj, char *description);

/**
 * @brief Object description getter
 *
 * @author Alba Delgado
 * @date 12-04-2021
 * 
 * @param object pointer to Object
 * 
 * @return object description otherwise NULL
 */
const char * object_get_description(Object* object);

/**
 * @brief Object movable setter
 * 
 * @author Jiri Zak
 * @date 23-12-2021
 * 
 * @param object pointer to Object
 * @param bool TRUE or FALSE
 * 
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS object_set_movable(Object*, BOOL);

/**
 * @brief Object movable getter
 * 
 * @author Jiri Zak
 * @date 23-12-2021
 * 
 * @param object pointer to Object
 * 
 * @return object movable otherwise FALSE
 */
BOOL object_get_movable(Object* object);

/**
 * @brief Object dependency setter
 * 
 * @author Jiri Zak
 * @date 23-12-2021
 * 
 * @param object pointer to Object
 * @param bool TRUE or FALSE
 * 
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS object_set_dependency(Object* object, Id id);

/**
 * @brief Object dependency getter
 * 
 * @author Jiri Zak
 * @date 23-12-2021
 * 
 * @param object pointer to Object
 * 
 * @return object dependency otherwise NO_ID
 */
Id object_get_dependency(Object* object);

/**
 * @brief Object openLink setter
 * 
 * @author Jiri Zak
 * @date 23-12-2021
 * 
 * @param object pointer to Object
 * @param bool TRUE or FALSE
 * 
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS object_set_openLink(Object* object, Id id);

/**
 * @brief Object openLink getter
 * 
 * @author Jiri Zak
 * @date 23-12-2021
 * 
 * @param object pointer to Object
 * 
 * @return object openLink otherwise NO_ID
 */
Id object_get_openLink(Object* object);

/**
 * @brief Object illuminate setter
 * 
 * @author Jiri Zak
 * @date 23-12-2021
 * 
 * @param object pointer to Object
 * @param bool TRUE or FALSE
 * 
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS object_set_illuminate(Object*, BOOL);

/**
 * @brief Object illuminate getter
 * 
 * @author Jiri Zak
 * @date 23-12-2021
 * 
 * @param object pointer to Object
 * 
 * @return object iluminate otherwise FALSE
 */
BOOL object_get_illuminate(Object* object);

/**
 * @brief Object turnedOn setter
 * 
 * @author Jiri Zak
 * @date 23-12-2021
 * 
 * @param object pointer to Object
 * @param bool TRUE or FALSE
 * 
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS object_set_turnedOn(Object*, BOOL);

/**
 * @brief Object turnedOn getter
 * 
 * @author Jiri Zak
 * @date 23-12-2021
 * 
 * @param object pointer to Object
 * 
 * @return object turnedOn otherwise FALSE
 */
BOOL object_get_turnedOn(Object* object);

STATUS object_save(FILE*, Object*);

#endif
