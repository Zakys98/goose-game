
#include "../include/space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/set.h"

struct _Space {
    Id id;
    char name[WORD_SIZE + 1];
    Link* north;
    Link* south;
    Link* east;
    Link* west;
    Set* objects;
    char gdesc[3][8];
    char description[WORD_SIZE + 1];
};

Space* space_create(Id id) {
    Space* newSpace = NULL;

    if (id == NO_ID)
        return NULL;

    newSpace = (Space*)malloc(sizeof(Space));

    if (newSpace == NULL) {
        return NULL;
    }
    newSpace->id = id;

    newSpace->name[0] = '\0';

    newSpace->north = NULL;
    newSpace->south = NULL;
    newSpace->east = NULL;
    newSpace->west = NULL;

    newSpace->objects = set_create();
    memset(newSpace->gdesc[0], ' ', 7);
    memset(newSpace->gdesc[1], ' ', 7);
    memset(newSpace->gdesc[2], ' ', 7);
    newSpace->gdesc[0][7] = '\0';
    newSpace->gdesc[1][7] = '\0';
    newSpace->gdesc[2][7] = '\0';

    return newSpace;
}

STATUS space_destroy(Space** space) {
    if (*space == NULL) {
        return ERROR;
    }

    if ((*space)->east != NULL)
        link_destroy(&(*space)->east);
    if ((*space)->west != NULL)
        link_destroy(&(*space)->west);
    if ((*space)->north != NULL)
        link_destroy(&(*space)->north);
    if ((*space)->south != NULL)
        link_destroy(&(*space)->south);
    set_destroy(&(*space)->objects);
    free(*space);
    *space = NULL;

    return OK;
}

STATUS space_set_name(Space* space, char* name) {
    if (!space || !name) {
        return ERROR;
    }

    if (!strcpy(space->name, name)) {
        return ERROR;
    }

    return OK;
}

STATUS space_set_north(Space* space, Link* l) {
    if (!space || l == NULL) {
        return ERROR;
    }
    space->north = l;
    return OK;
}

STATUS space_set_south(Space* space, Link* l) {
    if (!space || l == NULL) {
        return ERROR;
    }
    space->south = l;
    return OK;
}

STATUS space_set_east(Space* space, Link* l) {
    if (!space || l == NULL) {
        return ERROR;
    }
    space->east = l;
    return OK;
}

STATUS space_set_west(Space* space, Link* l) {
    if (!space || l == NULL) {
        return ERROR;
    }
    space->west = l;
    return OK;
}

STATUS space_add_object(Space* space, Id id) {
    if (!space) {
        return ERROR;
    }
    set_add(space->objects, id);
    return OK;
}

STATUS space_set_gdesc(Space* space, int line, char* name) {
    if (!space || !name || line > 2) {
        return ERROR;
    }

    if (!strcpy(space->gdesc[line], name)) {
        return ERROR;
    }

    return OK;
}

const char* space_get_name(Space* space) {
    if (!space) {
        return NULL;
    }
    return space->name;
}

Id space_get_id(Space* space) {
    if (!space) {
        return NO_ID;
    }
    return space->id;
}

Link* space_get_north(Space* space) {
    if (!space) {
        return NULL;
    }
    return space->north;
}

Link* space_get_south(Space* space) {
    if (!space) {
        return NULL;
    }
    return space->south;
}

Link* space_get_east(Space* space) {
    if (!space) {
        return NULL;
    }
    return space->east;
}

Link* space_get_west(Space* space) {
    if (!space) {
        return NULL;
    }
    return space->west;
}

STATUS space_remove_object(Space* space, Id id) {
    if (!space) {
        return ERROR;
    }
    return set_delete(space->objects, id);
}

char* space_get_gdesc(Space* space, int line) {
    if (!space) {
        return NULL;
    }
    return space->gdesc[line];
}

Id* space_get_objects(Space* s) {
    return s != NULL ? set_get_elements(s->objects) : NULL;
}

int space_objects_count(Space* s) {
    return set_get_size(s->objects);
}

STATUS space_print(Space* space) {
    Id idaux = NO_ID;

    if (!space) {
        return ERROR;
    }

    fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

    idaux = link_get_second_space(space_get_north(space));
    if (NO_ID != idaux) {
        fprintf(stdout, "---> North link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No north link.\n");
    }

    idaux = link_get_second_space(space_get_south(space));
    if (NO_ID != idaux) {
        fprintf(stdout, "---> South link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No south link.\n");
    }

    idaux = link_get_second_space(space_get_east(space));
    if (NO_ID != idaux) {
        fprintf(stdout, "---> East link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No east link.\n");
    }

    idaux = link_get_second_space(space_get_west(space));
    if (NO_ID != idaux) {
        fprintf(stdout, "---> West link: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> No west link.\n");
    }

    return OK;
}

BOOL space_hasObject(Space *space, Id id)
{
    Id *objects = space_get_objects(space);

    for(int i=0;i<space_objects_count(space);i++)
    {
        if(objects[i]== id)
        {
            return TRUE;
        }
    }
    return FALSE;
}

const char *space_get_description(Space *space)
{
    if (!space) {
    return NULL;
  }
  return space->description;
}