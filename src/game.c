/** 
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 * 
 * @file game.c
 * @author Eva Moresova
 * @version 2.0 
 * @date 01-03-2021 
 * @copyright GNU Public License
 */

#include "../include/game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct _Game {
    Player *player;
    Object *objects[MAX_OBJECTS];
    Space *spaces[MAX_SPACES + 1];
    T_Command last_cmd;
    Dice *dice;
    FILE *log;
    char description[50];
};

#define N_CALLBACK 13

/**
   Define the function type for the callbacks
*/
typedef STATUS (*callback_fn)(Game *game);

/**
   List of callbacks for each command in the game 
*/

STATUS game_callback_unknown(Game *game);
STATUS game_callback_exit(Game *game);
STATUS game_callback_next(Game *game);
STATUS game_callback_back(Game *game);

/**
 * @brief take command, object from space, where player is, is taken. 
 * If player already has an object, it is dropped and the new object is taken.
 *
 * @author Eva Moresova
 * @date 17-02-2021
 * 
 * @param game pointer to game
 */
STATUS game_callback_take(Game *game);

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
STATUS game_callback_drop(Game *game);

/**
 * @brief callback for roll command, player is able to move to left if possible.
 *
 * @author Jiri Zak
 * @date 01-03-2021
 * 
 * @param game pointer to game
 */
STATUS game_callback_roll(Game *game);

/**
 * @brief callback for left command, player is able to move to left if possible.
 *
 * @author Jiri Zak
 * @date 01-03-2021
 * 
 * @param game pointer to game
 */
STATUS game_callback_left(Game *game);

/**
 * @brief callback for left command, player is able to move to left if possible.
 *
 * @author Jiri Zak
 * @date 01-03-2021
 * 
 * @param game pointer to game
 */
STATUS game_callback_right(Game *game);

STATUS game_callback_move(Game *game);

STATUS game_callback_inspect(Game *game);

STATUS game_callback_turn_on(Game *game);

STATUS game_callback_turn_off(Game *game);

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_next,
    game_callback_back,
    game_callback_take,
    game_callback_drop,
    game_callback_roll,
    game_callback_left,
    game_callback_right,
    game_callback_move,
    game_callback_inspect,
    game_callback_turn_on,
    game_callback_turn_off};

/**
   Private functions prototypes
*/

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
STATUS game_set_player_location(Game *game, Id id);

/**
   Game interface implementation
*/

Game *game_init() {
    Game *g = malloc(sizeof(Game));
    if (g == NULL)
        return NULL;
    return g;
}

STATUS game_create(Game *game) {
    for (int i = 0; i < MAX_SPACES; i++) {
        game->spaces[i] = NULL;
    }
    for (int i = 0; i < MAX_OBJECTS; i++) {
        game->objects[i] = NULL;
    }
    game->log = NULL;
    game->last_cmd = NO_CMD;
    game->dice = dice_create(1, 6);
    memset(game->description, '\0', 50);

    return OK;
}

STATUS game_create_from_file(Game *game, char *filename) {
    if (game_create(game) == ERROR)
        return ERROR;

    if (game_load_game(game, filename) == ERROR)
        return ERROR;

    return OK;
}

STATUS game_destroy(Game *game) {
    for (int i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
        space_destroy(game->spaces + i);
    }

    if (game_logfile_exist(game))
        fclose(game->log);

    free(game);

    return OK;
}

Space *game_get_space(Game *game, Id id) {
    if (id == NO_ID) {
        return NULL;
    }

    for (int i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        if (id == space_get_id(game->spaces[i])) {
            return game->spaces[i];
        }
    }

    return NULL;
}

Object *game_get_object(Game *game, Id id) {
    if (id == NO_ID) {
        return NULL;
    }

    for (int i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
        if (id == object_get_id(game->objects[i])) {
            return game->objects[i];
        }
    }
    return NULL;
}

Object *game_get_object_at_position(Game *game, int id) {
    if (game == NULL || id < 0 || id >= MAX_OBJECTS)
        return NULL;

    return game->objects[id];
}

Player *game_get_player(Game *game) {
    return game != NULL ? game->player : NULL;
}

Dice *game_get_dice(Game *game) {
    return game != NULL ? game->dice : NULL;
}

Object *game_get_object_by_name(Game *game, char *name) {
    if (name == NULL) {
        return NULL;
    }

    for (int i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
        if (strcmp(name, object_get_name(game->objects[i])) == 0) {
            return game->objects[i];
        }
    }
    return NULL;
}

STATUS game_set_player_location(Game *game, Id s) {
    return player_set_location(game->player, s);
}

Id game_get_player_location(Game *game) {
    return player_get_location(game->player);
}

STATUS game_update(Game *game, T_Command cmd) {
    game->last_cmd = cmd;
    return (*game_callback_fn_list[cmd])(game);
}

T_Command game_get_last_command(Game *game) {
    return game->last_cmd;
}

STATUS game_add_space(Game *game, Space *space) {
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

STATUS game_add_object(Game *game, Object *obj) {
    Space *space = game_get_space(game, object_get_location(obj));
    space_add_object(space, object_get_id(obj));

    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (game->objects[i] == NULL) {
            game->objects[i] = obj;
            return OK;
        }
    }
    return ERROR;
}

STATUS game_set_player(Game *game, Player *p) {
    if (game == NULL || p == NULL)
        return ERROR;

    game->player = p;
    return OK;
}

void game_print_data(Game *game) {
    int i = 0;

    printf("\n\n-------------\n\n");

    printf("=> Spaces: \n");
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
        space_print(game->spaces[i]);
    }

    printf("=> Player location: %ld\n", game_get_player_location(game));
    printf("prompt:> ");
}

int game_get_number_object(Game *game) {
    if (game == NULL)
        return -1;
    int counter = 0;
    while ((counter < MAX_OBJECTS) && (game->objects[counter] != NULL)) {
        counter++;
    }
    return counter;
}

char *game_get_description(Game *game) {
    if (game == NULL || game->description[0] == '\0') return NULL;
    return game->description;
}

void game_open_log_file(Game *game, char *filename) {
    if (game == NULL || filename == NULL)
        return;
    game->log = fopen(filename, "w");
}

FILE *game_get_log_file(Game *game) {
    return game != NULL ? game->log : NULL;
}

BOOL game_logfile_exist(Game *game) {
    return game->log != NULL ? TRUE : FALSE;
}

BOOL game_is_over(Game *game) {
    (void)game;
    return FALSE;
}

/**
   Callbacks implementation for each action 
*/

STATUS game_callback_unknown(Game *game) {
    (void)game;
    return OK;
}

STATUS game_callback_exit(Game *game) {
    for (int i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
        object_destroy(&game->objects[i]);
    }
    player_destroy(&game->player);
    dice_destroy(&game->dice);
    return OK;
}

STATUS game_callback_next(Game *game) {
    Space *location = game_get_space(game, game_get_player_location(game));
    Id next_location = link_get_second_space(space_get_south(location));
    if (next_location == NO_ID)
        return ERROR;
    game_set_player_location(game, next_location);
    return OK;
}

STATUS game_callback_back(Game *game) {
    Space *location = game_get_space(game, game_get_player_location(game));
    Id next_location = link_get_second_space(space_get_north(location));
    if (next_location == NO_ID)
        return ERROR;
    game_set_player_location(game, next_location);
    return OK;
}

STATUS game_callback_take(Game *game) {
    char input[20];
    Space *location = game_get_space(game, game_get_player_location(game));

    if (space_objects_count(location) == 0)
        return ERROR;

    if (scanf("%s", input) > 0) {
        if (player_inventory_full(game->player)) {
            return ERROR;
        }
        Object *obj = game_get_object_by_name(game, input);
        if (obj == NULL)
            return ERROR;

        if (space_remove_object(location, object_get_id(obj)) == ERROR)
            return ERROR;

        player_add_object(game->player, obj);
    }
    return OK;
}

STATUS game_callback_drop(Game *game) {
    char input[20];
    if (scanf("%s", input) > 0) {
        Object *obj = game_get_object_by_name(game, input);
        if (obj == NULL)
            return ERROR;

        Space *s = game_get_space(game, game_get_player_location(game));
        if (player_delete_object(game->player, obj) == ERROR)
            return ERROR;

        space_add_object(s, object_get_id(obj));
        object_set_location(obj, space_get_id(s));
    }
    return OK;
}

STATUS game_callback_roll(Game *game) {
    dice_roll(game->dice);
    return OK;
}

STATUS game_callback_left(Game *game) {
    Space *location = game_get_space(game, game_get_player_location(game));
    Id next_location = link_get_second_space(space_get_west(location));
    if (next_location == NO_ID)
        return ERROR;
    game_set_player_location(game, next_location);
    return OK;
}

STATUS game_callback_right(Game *game) {
    Space *location = game_get_space(game, game_get_player_location(game));
    Id next_location = link_get_second_space(space_get_east(location));
    if (next_location == NO_ID)
        return ERROR;
    game_set_player_location(game, next_location);
    return OK;
}

STATUS game_callback_move(Game *game) {
    char input[20];

    if (scanf("%s", input) <= 0)
        return ERROR;

    if (strcmp(input, "north") == 0 || strcmp(input, "n") == 0) {
        return game_callback_back(game);
    } else if (strcmp(input, "south") == 0 || strcmp(input, "s") == 0) {
        return game_callback_next(game);
    } else if (strcmp(input, "west") == 0 || strcmp(input, "w") == 0) {
        return game_callback_left(game);
    } else if (strcmp(input, "east") == 0 || strcmp(input, "e") == 0) {
        return game_callback_right(game);
    }

    return ERROR;
}

STATUS game_callback_inspect(Game *game) {
    char input[20]; 
    memset(game->description, '\0', 50);

    Space *space = game_get_space(game, game_get_player_location(game));

    if (scanf("%s", input) > 0) {
        if (strcasecmp(input, "s") == 0 || strcasecmp(input, "space") == 0) {
            strcat(game->description, "space - ");
            strcat(game->description, space_get_description(space));
            return OK;
        } else {
            Object *obj = game_get_object_by_name(game, input);
            if (obj == NULL)
                return ERROR;

            if (space_hasObject(space, object_get_id(obj)) == TRUE || player_search_inventory(game->player, obj) == TRUE) {
                strcat(game->description, object_get_name(obj));
                strcat(game->description, " - ");
                strcat(game->description, object_get_description(obj));
                return OK;
            }
        }
    }
    return ERROR;
}

STATUS game_callback_turn_on(Game *game) {
    char input[20];

    if (scanf("%s", input) > 0) {
        Object *obj = game_get_object_by_name(game, input);
        if (obj == NULL || object_get_illuminate(obj) == FALSE)
            return ERROR;

        Space *playerLocation = game_get_space(game, game_get_player_location(game));
        if (space_hasObject(playerLocation, object_get_id(obj)) == TRUE || player_search_inventory(game->player, obj) == TRUE) {
            object_set_turnedOn(obj, TRUE);
            return OK;
        }
    }

    return ERROR;
}

STATUS game_callback_turn_off(Game *game) {
    char input[20];

    if (scanf("%s", input) > 0) {
        Object *obj = game_get_object_by_name(game, input);
        if (obj == NULL || object_get_illuminate(obj) == FALSE)
            return ERROR;

        Space *playerLocation = game_get_space(game, game_get_player_location(game));
        if (space_hasObject(playerLocation, object_get_id(obj)) == TRUE || player_search_inventory(game->player, obj) == TRUE) {
            object_set_turnedOn(obj, FALSE);
            return OK;
        }
    }

    return ERROR;
}