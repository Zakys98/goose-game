/** 
 * @brief Contains the implementation for set and its functions
 * 
 * @file set.c
 * @author Eva Moresova
 * @version 1.0 
 * @date 01-03-2021 
 * @copyright GNU Public License
 */

#include "set.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct _Vector {
	Id id;
	struct _Vector* next;
} Vector;

struct _Set {
	Vector* head;
	int size;
};

/** Private functions definitions */

/**
 * @brief for testing if set is empty
 *
 * @author Eva Moresova
 * @date 01-03-2021 
 * 
 * @param s pointer to set
 * @return TRUE if empty, FALSE otherwise
 */
BOOL set_is_empty(Set* s);

/**
 * @brief for testing if element with specified id is in the set
 *
 * @author Eva Moresova
 * @date 01-03-2021 
 * 
 * @param s pointer to set
 * @param id Id of element
 * @return TRUE if element exists in the set, FALSE otherwise
 */
BOOL set_element_exists(Set* s, Id id);

/**
 * @brief getter for element from a set by its id
 *
 * @author Eva Moresova
 * @date 01-03-2021 
 * 
 * @param s pointer to set
 * @param id Id of element
 * @return pointer to element with specified id
 */
Vector* set_get_element_by_id(Set* s, Id id);



/** Private functions implementation */

BOOL set_is_empty(Set* s) {
	if (s != NULL && set_get_size(s) == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOL set_element_exists(Set* s, Id id) {
	return (set_get_element_by_id(s, id) != NULL);
}

Vector* set_get_element_by_id(Set* s, Id id) {
	if (s == NULL)
		return NULL;

	Vector* v = s->head;
	for (int i=0; i < set_get_size(s); i++) {
		if (v->id == id) {
			return v;
		}
		v = v->next;
	}
	return NULL;
}


/** Interface implementation */
int set_get_size(Set* s) {
	return (s == NULL) ? -1 : s->size;
}

Set* set_create() {
	Set* s = (Set*)malloc(sizeof(struct _Set));
	if (s != NULL) {
		s->head = NULL;
		s->size = 0;
	}
	return s;
}

STATUS set_destroy(Set* s) {
	if (s == NULL) 
		return OK;

	if (!set_is_empty(s)) {
		for(int i = 0; i < set_get_size(s); i++) {
			Vector* tmp = s->head;
			s->head = s->head->next;
			free(tmp);
		}
	}
	free(s);
	return OK;
}

STATUS set_add(Set* s, Id id) {
	if (s == NULL) 
		return ERROR;

	if (set_element_exists(s, id)) 
		return OK;

	Vector* v = (Vector*)malloc(sizeof(Vector));
	if (v == NULL) {
		return ERROR;
	}
	v->id = id;
	v->next = s->head;
	s->head = v;
	s->size++;

	return OK;
}

STATUS 	set_delete(Set* s, Id id) {
	if (s == NULL || set_is_empty(s))
		return ERROR;

	Vector* v1 = s->head;
	Vector* v2 = v1->next;
	if (v1->id == id) {
		free(v1);
		s->head = v2;
		s->size -= 1;
		return OK;
	}
	for(int i=0; i < (set_get_size(s) - 1); i++) {
		if (v2->id == id) {
			v1->next = v2->next;
			free(v2);
			s->size -= 1;
			return OK; 
		} else {
			v1 = v2;
			v2 = v2->next;
		}
	}
	return ERROR;
}

void set_print(Set* s, FILE* fp) {
	if (s == NULL || fp == NULL) 
		return;

	if (set_is_empty(s)) {
		fprintf(fp, "Size 0: {}\n");
	} else {
		Vector* v = s->head;
		fprintf(fp, "Size %d: {%ld", set_get_size(s), v->id);
		v = v->next;
		while (v != NULL) {
			fprintf(fp, ", %ld", v->id);
			v = v->next;
		}
		fprintf(fp, "}\n");
	}
}

Id* set_get_elements(Set* s) {
	Id* elems = (Id*)malloc(sizeof(Id)*set_get_size(s));
	if(elems == NULL || set_is_empty(s))
		return NULL;

	Vector* v = s->head;
	for (int i = 0; (i < set_get_size(s) && v != NULL); i++) {
		elems[i] = v->id;
		v = v->next;
	}
	return elems;
}






