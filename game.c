/** 
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 * 
 * @file game.c
 * @author Eva Moresova
 * @version 1.0 
 * @date 17-02-2021 
 * @copyright GNU Public License
 */

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_CALLBACK 6

/**
   Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game* game);

/**
   List of callbacks for each command in the game 
*/

void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_next(Game* game);
void game_callback_back(Game* game);

/**
 * @brief take command, object from space, where player is, is taken. 
 * If player already has an object, it is dropped and the new object is taken.
 *
 * @author Eva Moresova
 * @date 17-02-2021
 * 
 * @param game pointer to game
 */
void game_callback_take(Game* game);

/**
 * @brief callback for drop command, player's object is dropped.
 * The object can only be dropped if there is no object in the space it should
 * be dropped to.
 *
 * @author Jiri Zak
 * @date 17-02-2021
 * 
 * @param game pointer to game
 */
void game_callback_drop(Game* game);

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_next,
    game_callback_back,
	game_callback_take,
	game_callback_drop};

/**
   Private functions prototypes
*/

/**
 * @brief space getter from position
 *
 * @author Eva Moresova
 * @date 12-02-2021
 * 
 * @param game pointer to game 
 * @param position index of position in position array
 * @return Id of the space at position
 */
Id game_get_space_id_at(Game* game, int position);

/**
 * @brief player location setter 
 *
 * @author Eva Moresova
 * @date 12-02-2021
 * 
 * @param game pointer to game
 * @param id id of player
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_set_player_location(Game* game, Id id);

/**
 * @brief object location setter 
 *
 * @author Eva Moresova
 * @date 12-02-2021
 * 
 * @param game pointer to game
 * @param id id of object
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS game_set_object_location(Game* game, Id id);

/**
   Game interface implementation
*/

STATUS game_create(Game* game) {
    for (int i = 0; i < MAX_SPACES; i++) {
        game->spaces[i] = NULL;
    }
    game->player = player_create(NO_ID);
    player_set_location(game->player, NO_ID);
    game->obj = object_create(NO_ID);
    object_set_location(game->obj, NO_ID);
    game->last_cmd = NO_CMD;

    return OK;
}

STATUS game_create_from_file(Game* game, char* filename) {
    if (game_create(game) == ERROR)
        return ERROR;

    if (game_load_spaces(game, filename) == ERROR)
        return ERROR;

    game_set_player_location(game, game_get_space_id_at(game, 0));
    game_set_object_location(game, game_get_space_id_at(game, 0));
    Space *s = game_get_space(game, game_get_space_id_at(game, 0));
    space_set_object(s, game->obj);

    return OK;
}

STATUS game_destroy(Game* game) {
    int i = 0;

    for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
        space_destroy(game->spaces + i);
    }

    return OK;
}

Id game_get_space_id_at(Game* game, int position) {
    if (position < 0 || position >= MAX_SPACES) {
        return NO_ID;
    }

    return space_get_id(game->spaces[position]);
}

Space* game_get_space(Game* game, Id id) {
    int i = 0;

    if (id == NO_ID) {
        return NULL;
    }

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        if (id == space_get_id(game->spaces[i])) {
            return game->spaces[i];
        }
    }

    return NULL;
}

STATUS game_set_player_location(Game* game, Id s) {
    return player_set_location(game->player, s);
}

STATUS game_set_object_location(Game* game, Id s) {
	return object_set_location(game->obj, s);
}

Id game_get_player_location(Game* game) {
    return player_get_location(game->player);
}

Id game_get_object_location(Game* game) {
    return object_get_location(game->obj);
}

STATUS game_update(Game* game, T_Command cmd) {
    game->last_cmd = cmd;
    (*game_callback_fn_list[cmd])(game);
    return OK;
}

T_Command game_get_last_command(Game* game) {
    return game->last_cmd;
}

void game_print_data(Game* game) {
    int i = 0;

    printf("\n\n-------------\n\n");

    printf("=> Spaces: \n");
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        space_print(game->spaces[i]);
    }

    printf("=> Object location: %ld\n", game_get_object_location(game));
    printf("=> Player location: %ld\n", game_get_player_location(game));
    printf("prompt:> ");
}

BOOL game_is_over(Game* game) {
	(void)game;
    return FALSE;
}

/**
   Callbacks implementation for each action 
*/

void game_callback_unknown(Game* game) {
    (void)game;
}

void game_callback_exit(Game* game) {
    free(game->obj);
    free(game->player);
}

void game_callback_next(Game* game) {
    int i = 0;
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    space_id = game_get_player_location(game);
    if (space_id == NO_ID) {
        return;
    }

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        current_id = space_get_id(game->spaces[i]);
        if (current_id == space_id) {
            current_id = space_get_south(game->spaces[i]);
            if (current_id != NO_ID) {
                game_set_player_location(game, current_id);
            }
            return;
        }
    }
}

void game_callback_back(Game* game) {
    int i = 0;
    Id current_id = NO_ID;
    Id space_id = NO_ID;

    space_id = game_get_player_location(game);

    if (NO_ID == space_id) {
        return;
    }

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        current_id = space_get_id(game->spaces[i]);
        if (current_id == space_id) {
            current_id = space_get_north(game->spaces[i]);
            if (current_id != NO_ID) {
                game_set_player_location(game, current_id);
            }
            return;
        }
    }
}

void game_callback_take(Game* game) {
	Space* location = game_get_space(game, game_get_player_location(game));

	Object* space_obj = space_get_object(location);
	if (space_obj == NULL) 
		return;

	Object* player_obj = player_get_object(game->player);
	if (player_obj != NULL) {
		space_set_object(location, NULL);
		game_callback_drop(game);
	}
	
	player_set_object(game->player, space_obj);
	object_set_location(space_obj, NO_ID);
}

void game_callback_drop(Game* game) {
    Space *s = game_get_space(game, game_get_player_location(game));
	if(!object_exist(game->player->obj) || space_get_object(s) != NULL)
        return;

    space_set_object(s, game->player->obj);
    object_set_location(game->player->obj, space_get_id(s));
    game->player->obj = NULL;
}
