
#include "../include/space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "../include/set.h"

struct _Space
{
    Id id;
    char name[WORD_SIZE + 1];
    Link *north;
    Link *south;
    Link *east;
    Link *west;
    Link *up;
    Link *down;
    Set *objects;
    char gdesc[3][8];
    char description[WORD_SIZE + 1];
    char detailed_description[WORD_SIZE + 1];
    BOOL illuminated;
};

Space *space_create(Id id)
{
    Space *newSpace = NULL;

    if (id == NO_ID)
        return NULL;

    newSpace = (Space *)malloc(sizeof(Space));

    if (newSpace == NULL)
    {
        return NULL;
    }
    newSpace->id = id;

    newSpace->name[0] = '\0';

    newSpace->north = NULL;
    newSpace->south = NULL;
    newSpace->east = NULL;
    newSpace->west = NULL;
    newSpace->up = NULL;
    newSpace->down = NULL;

    newSpace->objects = set_create();
    memset(newSpace->gdesc[0], ' ', 7);
    memset(newSpace->gdesc[1], ' ', 7);
    memset(newSpace->gdesc[2], ' ', 7);
    newSpace->gdesc[0][7] = '\0';
    newSpace->gdesc[1][7] = '\0';
    newSpace->gdesc[2][7] = '\0';
    memset(newSpace->description, '\0', WORD_SIZE + 1);

    newSpace->illuminated = TRUE;

    return newSpace;
}

STATUS space_destroy(Space **space)
{
    if (*space == NULL)
    {
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
    if ((*space)->up != NULL)
        link_destroy(&(*space)->up);
    if ((*space)->down != NULL)
        link_destroy(&(*space)->down);
    set_destroy(&(*space)->objects);
    free(*space);
    *space = NULL;

    return OK;
}

STATUS space_set_name(Space *space, char *name)
{
    if (!space || !name)
    {
        return ERROR;
    }

    if (!strcpy(space->name, name))
    {
        return ERROR;
    }

    return OK;
}


STATUS space_set_description(Space *space, char *description)
{
    if (!space || !description)
    {
        return ERROR;
    }

    if (!strcpy(space->description, description))
    {
        return ERROR;
    }

    return OK;
}

STATUS space_set_detailed_description(Space *space, char *detailed_description)
{
    if (!space || !detailed_description)
    {
        return ERROR;
    }

    if (!strcpy(space->detailed_description, detailed_description))
    {
        return ERROR;
    }

    return OK;
}


STATUS space_set_north(Space *space, Link *l)
{
    if (!space || l == NULL)
    {
        return ERROR;
    }
    space->north = l;
    return OK;
}

STATUS space_set_south(Space *space, Link *l)
{
    if (!space || l == NULL)
    {
        return ERROR;
    }
    space->south = l;
    return OK;
}

STATUS space_set_east(Space *space, Link *l)
{
    if (!space || l == NULL)
    {
        return ERROR;
    }
    space->east = l;
    return OK;
}

STATUS space_set_west(Space *space, Link *l)
{
    if (!space || l == NULL)
    {
        return ERROR;
    }
    space->west = l;
    return OK;
}

STATUS space_set_up(Space *space, Link *l)
{
    if (!space || l == NULL)
    {
        return ERROR;
    }
    space->up = l;
    return OK;
}

STATUS space_set_down(Space *space, Link *l)
{
    if (!space || l == NULL)
    {
        return ERROR;
    }
    space->down = l;
    return OK;
}

STATUS space_add_object(Space *space, Id id)
{
    if (!space)
    {
        return ERROR;
    }
    set_add(space->objects, id);
    return OK;
}

STATUS space_set_gdesc(Space *space, int line, char *name)
{
    if (!space || !name || line > 2)
    {
        return ERROR;
    }

    if (!strcpy(space->gdesc[line], name))
    {
        return ERROR;
    }

    return OK;
}

const char *space_get_name(Space *space)
{
    if (!space)
    {
        return NULL;
    }
    return space->name;
}

Id space_get_id(Space *space)
{
    if (!space)
    {
        return NO_ID;
    }
    return space->id;
}

Link *space_get_north(Space *space)
{
    if (!space)
    {
        return NULL;
    }
    return space->north;
}

Link *space_get_south(Space *space)
{
    if (!space)
    {
        return NULL;
    }
    return space->south;
}

Link *space_get_east(Space *space)
{
    if (!space)
    {
        return NULL;
    }
    return space->east;
}

Link *space_get_west(Space *space)
{
    if (!space)
    {
        return NULL;
    }
    return space->west;
}

Link *space_get_up(Space *space)
{
    if (!space)
    {
        return NULL;
    }
    return space->up;
}

Link *space_get_down(Space *space)
{
    if (!space)
    {
        return NULL;
    }
    return space->down;
}

STATUS space_remove_object(Space *space, Id id)
{
    if (!space)
    {
        return ERROR;
    }
    return set_delete(space->objects, id);
}

char *space_get_gdesc(Space *space, int line)
{
    if (!space)
    {
        return NULL;
    }
    return space->gdesc[line];
}

Id *space_get_objects(Space *s)
{
    return s != NULL ? set_get_elements(s->objects) : NULL;
}

int space_objects_count(Space *s)
{
    return set_get_size(s->objects);
}

STATUS space_set_illumination(Space *space, BOOL illumination)
{

    if (!space)
    {
        return ERROR;
    }
    space->illuminated = illumination;

    return OK;
}

BOOL space_get_illumination(Space *space)
{

    if (!space)
        return FALSE;

    return space->illuminated;
}

STATUS space_print(Space *space)
{
    Id idaux = NO_ID;
    BOOL illumination;

    if (!space)
    {
        return ERROR;
    }

    fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

    idaux = link_get_second_space(space_get_north(space));
    if (NO_ID != idaux)
    {
        fprintf(stdout, "---> North link: %ld.\n", idaux);
    }
    else
    {
        fprintf(stdout, "---> No north link.\n");
    }

    idaux = link_get_second_space(space_get_south(space));
    if (NO_ID != idaux)
    {
        fprintf(stdout, "---> South link: %ld.\n", idaux);
    }
    else
    {
        fprintf(stdout, "---> No south link.\n");
    }

    idaux = link_get_second_space(space_get_east(space));
    if (NO_ID != idaux)
    {
        fprintf(stdout, "---> East link: %ld.\n", idaux);
    }
    else
    {
        fprintf(stdout, "---> No east link.\n");
    }

    idaux = link_get_second_space(space_get_west(space));
    if (NO_ID != idaux)
    {
        fprintf(stdout, "---> West link: %ld.\n", idaux);
    }
    else
    {
        fprintf(stdout, "---> No west link.\n");
    }

    idaux = link_get_second_space(space_get_up(space));
    if (NO_ID != idaux)
    {
        fprintf(stdout, "---> Up link: %ld.\n", idaux);
    }
    else
    {
        fprintf(stdout, "---> No up link.\n");
    }

    idaux = link_get_second_space(space_get_down(space));
    if (NO_ID != idaux)
    {
        fprintf(stdout, "---> Down link: %ld.\n", idaux);
    }
    else
    {
        fprintf(stdout, "---> No down link.\n");
    }

    illumination = space_get_illumination(space);
    if (FALSE != illumination)
    {
        fprintf(stdout, "---> The space is illuminated\n");
    }
    else
    {
        fprintf(stdout, "--->The space is not illuminated\n");
    }

    return OK;
}

BOOL space_hasObject(Space *space, Id id)
{
    Id *objects = space_get_objects(space);

    for (int i = 0; i < space_objects_count(space); i++)
    {
        if (objects[i] == id)
        {
            free(objects);
            return TRUE;
        }
    }
    free(objects);
    return FALSE;
}

const char *space_get_description(Space *space)
{
    if (!space)
    {
        return NULL;
    }
    return space->description;
}

const char *space_get_detailed_description(Space *space)
{
    if (!space)
    {
        return NULL;
    }
    return space->detailed_description;
}

Link* space_get_link_by_name(Space* s, char* name) {
    if(s->north != NULL)
	    if (strcasecmp(link_get_name(s->north), name) == 0)
		    return s->north;
	
    if(s->east != NULL)
	    if (strcasecmp(link_get_name(s->east), name) == 0)
		    return s->east;

    if(s->south != NULL)
	    if (strcasecmp(link_get_name(s->south), name) == 0)
		    return s->south;

    if(s->west != NULL)
	    if (strcasecmp(link_get_name(s->west), name) == 0)
		    return s->west;

    if(s->up != NULL)
	    if (strcasecmp(link_get_name(s->up), name) == 0)
		    return s->up;
	
    if(s->down != NULL)
	    if (strcasecmp(link_get_name(s->down), name) == 0)
		    return s->down;

	return NULL;
}

STATUS space_save(FILE *fp, Space *s)
{
    if (s == NULL || fp == NULL)
        return ERROR;

    //#s:1|Tile 1|-1|-1|2|-1
    Link *l = space_get_north(s);
    link_save(fp, l);
    Id north = link_get_first_space(l) == s->id ? link_get_second_space(l) : link_get_first_space(l);
    l = space_get_south(s);
    link_save(fp, l);
    Id south = link_get_first_space(l) == s->id ? link_get_second_space(l) : link_get_first_space(l);
    l = space_get_east(s);
    link_save(fp, l);
    Id east = link_get_first_space(l) == s->id ? link_get_second_space(l) : link_get_first_space(l);
    l = space_get_west(s);
    link_save(fp, l);
    Id west = link_get_first_space(l) == s->id ? link_get_second_space(l) : link_get_first_space(l);
    fprintf(fp, "#s:%ld|%s|%ld|%ld|%ld|%ld|%s|%s|%s\n", s->id, s->name, north, east, south, west, s->gdesc[0], s->gdesc[1], s->gdesc[2]);

    return OK;
}