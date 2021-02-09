/** 
 * @brief It defines the game interface
 * for each command
 * 
 * @file game.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#include "object.h"

Object* object_create(Id id){
    Object *o = (Object *)malloc(sizeof(struct obj));
    if(o == NULL)
        return NULL;
    o->id = id;
    return o;
}
STATUS object_destroy(Object **o){
    if(!object_exist(*o))
        return ERROR;
    
    free(*o);
    *o = NULL;

    return OK;
}

STATUS object_exist(Object *o){
    return o == NULL ? FALSE : TRUE;
}

Id object_get_id(Object *o){
    if(!object_exist(o))
        return -1;
    return o->id;
}

const char* object_get_name(Object *o){
    if(!object_exist(o))
        return NULL;
    return o->name;
}

STATUS object_set_name(Object *o, const char *str){
    if(!object_exist(o) || str == NULL)
        return ERROR;
    if (!strcpy(o->name, str))
        return ERROR;
    return OK;
}

void object_print(Object *o){
    printf("id: %ld\n name: %s\n", o->id, o->name);
}