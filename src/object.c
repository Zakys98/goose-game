/** 
 * @brief It defines the object interface
 * 
 * @file object.c
 * @author Jiri Zak
 * @version 1.0 
 * @date 12-02-2021 
 * @copyright GNU Public License
 */

#include "../include/object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Structure for Object
 * Id id
 * char[] name
 * id location 
 */
struct _Obj {
    Id id;
    char name[WORD_SIZE + 1];
	Id location;
    char description[WORD_SIZE + 1];
};

Object *object_create(Id id) {
    Object *o = (Object *)malloc(sizeof(struct _Obj));
    if (o == NULL)
        return NULL;
    o->id = id;
	o->location = NO_ID;
    memset(o->description, '\0', WORD_SIZE + 1);
    
    return o;
}

STATUS object_destroy(Object **o) {
    if (!object_exist(*o))
        return ERROR;

    free(*o);
    *o = NULL;

    return OK;
}

STATUS object_exist(Object *o) {
    return o == NULL ? FALSE : TRUE;
}

Id object_get_id(Object *o) {
    if (!object_exist(o))
        return -1;
    return o->id;
}

const char *object_get_name(Object *o) {
    if (!object_exist(o))
        return NULL;
    return o->name;
}

STATUS object_set_name(Object *o, const char *str) {
    if (!object_exist(o) || str == NULL)
        return ERROR;
    if (!strcpy(o->name, str))
        return ERROR;
    return OK;
}

STATUS object_set_location(Object* o, Id s) {
	if (!object_exist(o)) 
		return ERROR;

	o->location = s;
	return OK;
}


Id object_get_location(Object* o) {
	if (!object_exist(o))
		return NO_ID;
		
	return o->location;
}

void object_print(Object *o) {
    printf("id: %ld\n name: %s\n", o->id, o->name);
}

STATUS object_set_description(Object *obj, char *description){
    if(obj == NULL || description == NULL || strlen(description) > 49)
        return ERROR;

    strcpy(obj->description, description);
    return OK;
}

const char * object_get_description(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->description;
}