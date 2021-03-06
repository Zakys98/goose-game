/** 
 * @brief It defines the link interface
 * 
 * @file link.c
 * @author Jiri Zak
 * @version 1.0 
 * @date 22-03-2021 
 * @copyright GNU Public License
 */

#include "../include/link.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Link {
    Id id;
    char name[WORD_SIZE + 1];
    Id first;
    Id second;
    BOOL opened;
};

BOOL link_exist(Link* l) {
    return l == NULL ? FALSE : TRUE;
}

BOOL link_not_exist(Link* l) {
    return !link_exist(l);
}

Link* link_create() {
    Link* l = malloc(sizeof(Link));
    if (link_not_exist(l))
        return NULL;

    l->id = NO_ID;
    l->name[0] = '\0';
    l->first = -1;
    l->second = -1;
    l->opened = TRUE;
    return l;
}

void link_set_id(Link *l, Id id) {
	if (l != NULL)
		l->id = id;
}

Id link_get_id(Link *l){
    return link_not_exist(l) ? -1 : l->id;
}

STATUS link_destroy(Link** l) {
    if (link_not_exist(*l)) {
        return ERROR;
    }

    free(*l);
    *l = NULL;

    return OK;
}

STATUS link_set_name(Link* l, char* name) {
    if (link_not_exist(l) || !name || strlen(name) > WORD_SIZE) {
        return ERROR;
    }

    if (!strcpy(l->name, name)) {
        return ERROR;
    }

    return OK;
}

const char* link_get_name(Link* l) {
    if (link_not_exist(l)) {
        return NULL;
    }
    return l->name;
}

STATUS link_set_first_space(Link* l, Id id) {
    if (link_not_exist(l))
        return ERROR;
    l->first = id;
    return OK;
}

Id link_get_first_space(Link* l) {
    if (link_not_exist(l))
        return -1;
    return l->first;
}

STATUS link_set_second_space(Link* l, Id id) {
    if (link_not_exist(l))
        return ERROR;
    l->second = id;
    return OK;
}

Id link_get_second_space(Link* l) {
    if (link_not_exist(l))
        return -1;
    return l->second;
}

STATUS link_set_opened(Link* l, BOOL opened) {
    if (link_not_exist(l))
        return FALSE;
    l->opened = opened;
    return OK;
}

BOOL link_get_opened(Link* l) {
    if (link_not_exist(l))
        return FALSE;
    return l->opened;
}

void link_print(Link* l) {
    printf("%ld %s\n", l->id, l->name);
}

STATUS link_save(FILE* fp, Link* l) {
	if (l == NULL || fp == NULL) return ERROR;
	
	//#l:1|Lnk1|1|2|0|
	fprintf(fp, "#l:%ld|%s|%ld|%ld|%d|\n", l->id, l->name, l->first, l->second, l->opened);
	return OK;
} 