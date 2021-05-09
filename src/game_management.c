/** 
 * @brief It implements the game management interface for loading and saving the state of game.
 * 
 * @file game_reader.c
 * @author Eva Moresova
 * @version 4.0 
 * @date 26-04-2021 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/game.h"

// Private functions
/**
 * @brief load space string description, add it to game
 *
 * @author Eva Moresova
 * @date 08-03-2021
 * 
 * @param game pointer to game
 * @param line string with space description
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_load_space(Game* game, char* line);

/**
 * @brief load object string description, add it to game
 *
 * @author Eva Moresova
 * @date 08-03-2021
 * 
 * @param game pointer to game
 * @param line string with object description
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_load_object(Game* game, char* line);

/**
 * @brief load player string description, add it to game
 *
 * @author Eva Moresova
 * @date 22-03-2021
 * 
 * @param game pointer to game
 * @param line string with player description
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_load_player(Game* game, char* line);

/**
 * @brief load link string description, add it to game
 *
 * @author Eva Moresova
 * @date 19-04-2021
 * 
 * @param game pointer to game
 * @param line string with link description
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_load_links(Game* game, char* line);

STATUS game_management_load_inventory(Game* game, char* line);
STATUS game_management_load_dice(Game* game, char* line);

// Implementation
STATUS game_management_load(char* filename, Game* game) {
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
            game_load_space(game, line);
        } else if (strncmp("#o:", line, 3) == 0) {
            game_load_object(game, line);
        } else if (strncmp("#p:", line, 3) == 0) {
            game_load_player(game, line);
        } else if (strncmp("#l:", line, 3) == 0) {
            game_load_links(game, line);
        } else if (strncmp("#i", line, 2) == 0) {
			game_management_load_inventory(game, line);
		} else if (strncmp("#d", line, 2) == 0) {
			game_management_load_dice(game, line);
		}
    }

    if (ferror(file)) {
        status = ERROR;
    }

    fclose(file);

    return status;
}

STATUS game_management_save(char* filename, Game* game) {
	FILE* out = fopen(filename, "w");
	if (out == NULL) return ERROR;
	
	game_save(out, game);

	fflush(out);
	fclose(out);
	return OK;
}

STATUS game_load_space(Game* game, char* line) {
    char name[WORD_SIZE] = "";
    char* toks = NULL;
    char first[8], second[8], third[8];
    memset(first, '\0', 8);
    memset(second, '\0', 8);
    memset(third, '\0', 8);
    Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
    Space* space = NULL;
    Link* link = NULL;
    char description[WORD_SIZE+1];
    char detailed_description[WORD_SIZE+1];

    toks = strtok(line + 3, "|");
    id = atol(toks);
    toks = strtok(NULL, "|");
    strcpy(name, toks);
    toks = strtok(NULL, "|");
    strcpy(description, toks);
    toks = strtok(NULL, "|");
    strcpy(detailed_description, toks);
    toks = strtok(NULL, "|");
    north = atol(toks);
    toks = strtok(NULL, "|");
    east = atol(toks);
    toks = strtok(NULL, "|");
    south = atol(toks);
    toks = strtok(NULL, "|");
    west = atol(toks);
    toks = strtok(NULL, "|");
    if (toks != NULL) {
        strncpy(first, toks, 7);
        toks = strtok(NULL, "|");
        strncpy(second, toks, 7);
        toks = strtok(NULL, "|");
        strncpy(third, toks, 7);
    }

    space = space_create(id);
    if (space != NULL) {
        space_set_name(space, name);
        space_set_description(space,description);
        space_set_detailed_description(space,detailed_description);
        if (north != NO_ID) {
            link = link_create();
            if (link == NULL)
                return ERROR;
            link_set_first_space(link, id);
            link_set_second_space(link, north);
			space_set_north(space, link);
        }
		if (east != NO_ID) {
            link = link_create();
            if (link == NULL)
                return ERROR;
            link_set_first_space(link, id);
            link_set_second_space(link, east);
			space_set_east(space, link);
        }
		if (south != NO_ID) {
            link = link_create();
            if (link == NULL)
                return ERROR;
            link_set_first_space(link, id);
            link_set_second_space(link, south);
			space_set_south(space, link);
		}
		if (west != NO_ID) {
            link = link_create();
            if (link == NULL)
                return ERROR;
            link_set_first_space(link, id);
            link_set_second_space(link, west);
			space_set_west(space, link);
		}
        if (toks != NULL) {
            space_set_gdesc(space, 0, first);
            space_set_gdesc(space, 1, second);
            space_set_gdesc(space, 2, third);
        }
        game_add_space(game, space);
    }
    return OK;
}

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
STATUS game_load_object(Game* game, char* line) {
    char* toks = NULL;
    char name[WORD_SIZE] = "";
	char description[4*WORD_SIZE] = "";
    Id id = NO_ID;
    Id space = NO_ID;

    toks = strtok(line + 3, "|");
    id = atol(toks);
    toks = strtok(NULL, "|");
    strcpy(name, toks);
	toks = strtok(NULL, "|");
    strcpy(description, toks);
    toks = strtok(NULL, "|");
    space = atol(toks);

    Object* obj = object_create(id);
    object_set_name(obj, name);
    object_set_location(obj, space);
	object_set_description(obj, description);
	
/*	toks = strtok(NULL, "|");
	id = atol(toks);
	object_set_dependency(obj, id);
	toks = strtok(NULL, "|");
	id = atol(toks);
	object_set_openLink(obj, id);
	
	toks = strtok(NULL, "|");
	if (atoi(toks) == 1)
		object_set_movable(obj, TRUE);
	else
		object_set_movable(obj, FALSE);

	toks = strtok(NULL, "|");
	if (atoi(toks) == 1)
		object_set_illuminate(obj, TRUE);
	else
		object_set_illuminate(obj, FALSE);

	toks = strtok(NULL, "|");
	if (atoi(toks) == 1)
		object_set_turnedOn(obj, TRUE);
	else
		object_set_turnedOn(obj, FALSE);*/

    return game_add_object(game, obj);
}

STATUS game_load_player(Game* game, char* line) {
    char* toks = NULL;
    char name[WORD_SIZE] = "";
    Id id = NO_ID;
    Id space = NO_ID;
    int cap = 0;

    toks = strtok(line + 3, "|");
    id = atol(toks);
    toks = strtok(NULL, "|");
    strcpy(name, toks);
    toks = strtok(NULL, "|");
    space = atol(toks);
    toks = strtok(NULL, "|");
    cap = atoi(toks);

    Player* p = player_create(id, cap);
    player_set_name(p, name);
    player_set_location(p, space);

    return game_set_player(game, p);
}

void modify_link(Link* link, Id id, char* name, int open) {
	link_set_id(link, id);
	link_set_name(link, name);
	if (open == 0) 
		link_set_opened(link, TRUE);
	else 
		link_set_opened(link, FALSE);
}

BOOL cmp_link(Id id1, Id id2, Link* link) {
	if ((link_get_first_space(link) == id1 && link_get_second_space(link) == id2)
		|| (link_get_first_space(link) == id2 && link_get_second_space(link) == id1)) {
			return TRUE;
	}
	return FALSE;
}

void complete_links(Space* space, Id id1, Id id2, Id id, char* name, int open) {
	if (cmp_link(id1, id2, space_get_north(space)) == TRUE) {
		modify_link(space_get_north(space), id, name, open);
	}
	if (cmp_link(id1, id2, space_get_west(space)) == TRUE) {
		modify_link(space_get_west(space), id, name, open);
	}
	if (cmp_link(id1, id2, space_get_south(space)) == TRUE) {
		modify_link(space_get_south(space), id, name, open);
	}
	if (cmp_link(id1, id2, space_get_east(space)) == TRUE) {
		modify_link(space_get_east(space), id, name, open);
	}
}

STATUS game_load_links(Game* game, char* line) {
	char* toks = NULL;
    char name[WORD_SIZE] = "";
    Id id = NO_ID, firstId = NO_ID, secondId = NO_ID;
	int open = -1;

	toks = strtok(line + 3, "|");
	id = atol(toks);
	// if (id == 31) {
	// 	printf("hehe");
	// }
	toks = strtok(NULL, "|");
	strcpy(name, toks);
    toks = strtok(NULL, "|");
	firstId = atol(toks);
	toks = strtok(NULL, "|");
	secondId = atol(toks);
	toks = strtok(NULL, "|");
	open = atoi(toks);

	Space* firstSpace = game_get_space(game, firstId);
	Space* secondSpace = game_get_space(game, secondId);
	if (firstSpace == NULL || secondSpace == NULL) return ERROR;

	complete_links(firstSpace, firstId, secondId, id, name, open);
	complete_links(secondSpace, firstId, secondId, id, name, open);

    return OK;
}

STATUS game_management_load_inventory(Game* game, char* line) {
	char* toks = NULL;
    Id id = NO_ID;

	toks = strtok(line + 3, "|");
	while (toks != NULL) {
		id = atol(toks);
		player_add_object(game_get_player(game), game_get_object(game, id));
		toks = strtok(NULL, "|");
	}
	return OK;
}

STATUS game_management_load_dice(Game* game, char* line) {
	char* toks = NULL;
	int last_roll = -1;
    int min = 0;
	int max = 0;

	toks = strtok(line + 3, "|");
	last_roll = atoi(toks);
	toks = strtok(NULL, "|");
	min = atoi(toks);
	toks = strtok(NULL, "|");
	max = atoi(toks);

	Dice* dice = dice_create(min, max);
	dice_set_last_roll(dice, last_roll);
	if (dice != NULL) game_set_dice(game, dice);
	return OK;
}