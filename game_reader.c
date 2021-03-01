/** 
 * @brief It implements the game reader interface
 * 
 * @file game_reader.c
 * @author Eva Moresova
 * @version 1.0 
 * @date 10-02-2021 
 * @copyright GNU Public License
 */

#include "game_reader.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Private functions
/**
 * @brief add space to game
 *
 * @author Eva Moresova
 * @date 10-02-2021
 * 
 * @param game pointer to game, where we add space
 * @param space pointer to space, which is added to game
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_add_space(Game* game, Space* space);
STATUS game_add_object(Game* game, Object* obj);

STATUS game_load_spaces (Game* game, char* line);
STATUS game_load_objects (Game* game, char* line);

STATUS game_load_game(Game* game, char* filename) {
    FILE* file = NULL;
    char line[WORD_SIZE] = "";
    STATUS status = OK;

    if (!filename) {
        return ERROR;
    }

    file = fopen(filename, "r");
    if (file == NULL) {
        return ERROR;
    }

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#s:", line, 3) == 0) {
			game_load_spaces(game, line);
        } else if (strncmp("#o:", line, 3) == 0) {
			game_load_objects(game, line);
		}
    }

    if (ferror(file)) {
        status = ERROR;
    }

    fclose(file);

    return status;
}

STATUS game_load_spaces(Game* game, char* line) {
	char name[WORD_SIZE] = "";
    char* toks = NULL;
	char first[7], second[7], third[7];
    Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
    Space* space = NULL;

	toks = strtok(line + 3, "|");
	id = atol(toks);
	toks = strtok(NULL, "|");
	strcpy(name, toks);
	toks = strtok(NULL, "|");
	north = atol(toks);
	toks = strtok(NULL, "|");
	east = atol(toks);
	toks = strtok(NULL, "|");
	south = atol(toks);
	toks = strtok(NULL, "|");
	west = atol(toks);
	toks = strtok(NULL, "|");
	if(toks != NULL){
		strncpy(first, toks, 7);
		toks = strtok(NULL, "|");
		strncpy(second, toks, 7);
		toks = strtok(NULL, "|");
		strncpy(third, toks, 7);
	}
	
	space = space_create(id);
	if (space != NULL) {
		space_set_name(space, name);
		space_set_north(space, north);
		space_set_east(space, east);
		space_set_south(space, south);
		space_set_west(space, west);
		game_add_space(game, space);
	}
	if(toks != NULL){
		space_set_gdesc(space, 0, first);
		space_set_gdesc(space, 1, second);
		space_set_gdesc(space, 2, third);
	}
	return OK;
}

STATUS game_load_objects(Game* game, char* line) {
	char* toks = NULL;
	char name[WORD_SIZE] = "";
    Id id = NO_ID;
	Id space = NO_ID;

	toks = strtok(line + 3, "|");
	id = atol(toks);
	toks = strtok(NULL, "|");
	strcpy(name, toks);
	toks = strtok(NULL, "|");
	space = atol(toks);

	Object* obj = object_create(id);
	object_set_name(obj, name);
	object_set_location(obj, space);
	
	return game_add_object(game, obj);
}

STATUS game_add_space(Game* game, Space* space) {
    int i = 0;

    if (space == NULL) {
        return ERROR;
    }

    while ((i < MAX_SPACES) && (game->spaces[i] != NULL)) {
        i++;
    }

    if (i >= MAX_SPACES) {
        return ERROR;
    }

    game->spaces[i] = space;

    return OK;
}

STATUS game_add_object(Game* game, Object* obj) {

	Space* space = game_get_space(game, object_get_location(obj));
	space_add_object(space, object_get_id(obj));
    
    for (int i=0; i < MAX_OBJECTS; i++) {
		if (game->objects[i] == NULL) {
			game->objects[i] = obj;
			return OK;
		}
	}
	return ERROR;
}