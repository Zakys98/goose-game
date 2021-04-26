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

struct _Obj {
    Id id;
    char name[WORD_SIZE + 1];
	Id location;
    char description[WORD_SIZE + 1];
    BOOL movable;
    Id dependency;
    Id openLink;
    BOOL illuminate;
    BOOL turnedOn;
};

Object *object_create(Id id) {
    Object *o = (Object *)malloc(sizeof(struct _Obj));
    if (o == NULL)
        return NULL;
    o->id = id;
	o->location = NO_ID;
    o->movable = FALSE;
    o->dependency = NO_ID;
    o->openLink = NO_ID;
    o->illuminate = FALSE;
    o->turnedOn = FALSE;
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

STATUS object_set_movable(Object* object, BOOL bool){
    if(object == NULL)
        return ERROR;

    object->movable = bool;
    return OK;
}

BOOL object_get_movable(Object* object){
    return object == NULL ? FALSE : object->movable;
}

STATUS object_set_dependency(Object* object, Id id){
    if(object == NULL)
        return ERROR;

    object->dependency = id;
    return OK;
}

Id object_get_dependency(Object* object){
    return object == NULL ? FALSE : object->dependency;
}

STATUS object_set_openLink(Object* object, Id id){
    if(object == NULL)
        return ERROR;

    object->openLink = id;
    return OK;
}

Id object_get_openLink(Object* object){
    return object == NULL ? FALSE : object->openLink;
}

STATUS object_set_illuminate(Object* object, BOOL bool){
    if(object == NULL)
        return ERROR;

    object->illuminate = bool;
    return OK;
}

BOOL object_get_illuminate(Object* object){
    return object == NULL ? FALSE : object->illuminate;
}

STATUS object_set_turnedOn(Object* object, BOOL bool){
    if(object == NULL)
        return ERROR;

    object->turnedOn = bool;
    return OK;
}

BOOL object_get_turnedOn(Object* object){
    return object == NULL ? FALSE : object->turnedOn;
}

STATUS object_save(FILE* fp, Object* o) {
	if (o == NULL || fp == NULL) return ERROR;
	
	//#o:id|name|description|location|dependency|openLink|movable|illuminate|turnedOn
	fprintf(fp, "#o:%ld|%s|%s|%ld|%ld|%ld|%d|%d|%d\n", 
	o->id, o->name, o->description, o->location, o->dependency, o->openLink, o->movable, o->illuminate, o->turnedOn);

	return OK;
} 