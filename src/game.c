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

struct _Game
{
    Player *player;
    Object *objects[MAX_OBJECTS];
    Space *spaces[MAX_SPACES + 1];
    T_Command last_cmd;
    T_Command prev_cmd;
    Dice *dice;
    FILE *log;
    char description[50];
    char *argument; //Argument used after a command
};

#define N_CALLBACK 16

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

STATUS game_callback_open_link_with_obj(Game *game);

STATUS game_callback_save(Game *game);

STATUS game_callback_load(Game *game);

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
    game_callback_turn_off,
    game_callback_open_link_with_obj,
    game_callback_save,
    game_callback_load};

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



void game_drop_object(Game *game, Space *space, Object *obj);

/**
   Game interface implementation
*/

Game *game_init()
{
    Game *g = malloc(sizeof(Game));
    if (g == NULL)
        return NULL;
    return g;
}

STATUS game_create(Game *game)
{
    for (int i = 0; i < MAX_SPACES; i++)
    {
        game->spaces[i] = NULL;
    }
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        game->objects[i] = NULL;
    }
    game->log = NULL;
    game->last_cmd = NO_CMD;
    game->prev_cmd = NO_CMD;
    game->dice = dice_create(1, 6);
    game->argument = (char *)malloc(sizeof(char) * 21);
    if (game->argument == NULL)
        return ERROR;
    memset(game->description, '\0', 50);

    return OK;
}

STATUS game_create_from_file(Game *game, char *filename)
{
    if (game_create(game) == ERROR)
        return ERROR;

    if (game_management_load(filename, game) == ERROR)
        return ERROR;

    return OK;
}

STATUS game_destroy(Game *game)
{
    for (int i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++)
    {
        space_destroy(game->spaces + i);
    }

    if (game_logfile_exist(game))
        fclose(game->log);

    free(game->argument);
    free(game);

    return OK;
}

STATUS game_clear(Game *game)
{
    player_destroy(&game->player);
    for (int i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++)
    {
        space_destroy(game->spaces + i);
        game->spaces[i] = NULL;
    }
    for (int i = 0; (i < MAX_OBJECTS) && (game->objects[i] != NULL); i++)
    {
        object_destroy(game->objects + i);
        game->objects[i] = NULL;
    }
    dice_destroy(&game->dice);
    game->description[0] = '\0';

    if (game_logfile_exist(game))
    {
        fclose(game->log);
        game->log = NULL;
    }
    return OK;
}

Space *game_get_space(Game *game, Id id)
{
    if (id == NO_ID)
    {
        return NULL;
    }

    for (int i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    {
        if (id == space_get_id(game->spaces[i]))
        {
            return game->spaces[i];
        }
    }

    return NULL;
}

Object *game_get_object(Game *game, Id id)
{
    if (id == NO_ID)
    {
        return NULL;
    }

    for (int i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    {
        if (id == object_get_id(game->objects[i]))
        {
            return game->objects[i];
        }
    }
    return NULL;
}

Object *game_get_object_at_position(Game *game, int id)
{
    if (game == NULL || id < 0 || id >= MAX_OBJECTS)
        return NULL;

    return game->objects[id];
}

Player *game_get_player(Game *game)
{
    return game != NULL ? game->player : NULL;
}

Dice *game_get_dice(Game *game)
{
    return game != NULL ? game->dice : NULL;
}

Object *game_get_object_by_name(Game *game, char *name)
{
    if (name == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    {
        if (strcmp(name, object_get_name(game->objects[i])) == 0)
        {
            return game->objects[i];
        }
    }
    return NULL;
}

STATUS game_set_player_location(Game *game, Id s)
{
    return player_set_location(game->player, s);
}

Link *game_get_link_by_name(Game *game, const char *name)
{
    if (game == NULL || name == NULL)
        return NULL;
    for (int i = 0; i < 101 && game->spaces[i] != NULL; i++)
    {
        Link *east = space_get_east(game->spaces[i]);
        if (east != NULL)
        {
            if (strcmp(link_get_name(east), name) == 0)
                return east;
        }
        Link *west = space_get_west(game->spaces[i]);
        if (west != NULL)
        {
            if (strcmp(link_get_name(west), name) == 0)
                return west;
        }
        Link *north = space_get_north(game->spaces[i]);
        if (north != NULL)
        {
            if (strcmp(link_get_name(north), name) == 0)
                return north;
        }
        Link *south = space_get_south(game->spaces[i]);
        if (south != NULL)
        {
            if (strcmp(link_get_name(south), name) == 0)
                return south;
        }
    }
    return NULL;
}

void game_drop_object(Game *game, Space *space, Object *obj)
{
    if (game == NULL || space == NULL || obj == NULL)
        return;

    if (object_get_dependency(obj) != NO_ID)
    {
        game_drop_object(game, space, game_get_object(game, object_get_dependency(obj)));
    }

    space_add_object(space, object_get_id(obj));
    object_set_location(obj, space_get_id(space));
}

Id game_get_player_location(Game *game)
{
    return player_get_location(game->player);
}

STATUS game_update(Game *game, T_Command cmd)
{
    game->last_cmd = cmd;
    return (*game_callback_fn_list[cmd])(game);
}

T_Command game_get_last_command(Game *game)
{
    return game->last_cmd;
}

T_Command game_get_prev_command(Game *game)
{
    return game->prev_cmd;
}

STATUS game_set_prev_command(Game *game, T_Command cmd)
{
    if (game == NULL)
        return ERROR;

    game->prev_cmd = cmd;
    return OK;
}

STATUS game_add_space(Game *game, Space *space)
{
    int i = 0;

    if (space == NULL)
    {
        return ERROR;
    }

    while ((i < MAX_SPACES) && (game->spaces[i] != NULL))
    {
        i++;
    }

    if (i >= MAX_SPACES)
    {
        return ERROR;
    }

    game->spaces[i] = space;

    return OK;
}

STATUS game_add_object(Game *game, Object *obj)
{
    Space *space = game_get_space(game, object_get_location(obj));
    space_add_object(space, object_get_id(obj));

    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (game->objects[i] == NULL)
        {
            game->objects[i] = obj;
            return OK;
        }
    }
    return ERROR;
}

STATUS game_set_player(Game *game, Player *p)
{
    if (game == NULL || p == NULL)
        return ERROR;

    game->player = p;
    return OK;
}

STATUS game_set_dice(Game *game, Dice *dice)
{
    if (game == NULL || dice == NULL)
        return ERROR;
    game->dice = dice;
    return OK;
}

void game_print_data(Game *game)
{
    int i = 0;

    printf("\n\n-------------\n\n");

    printf("=> Spaces: \n");
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    {
        space_print(game->spaces[i]);
    }

    printf("=> Player location: %ld\n", game_get_player_location(game));
    printf("prompt:> ");
}

int game_get_number_object(Game *game)
{
    if (game == NULL)
        return -1;
    int counter = 0;
    while ((counter < MAX_OBJECTS) && (game->objects[counter] != NULL))
    {
        counter++;
    }
    return counter;
}

char *game_get_argument(Game *game)
{
    if (game == NULL)
        return NULL;

    return game->argument;
}

char *game_get_description(Game *game)
{
    if (game == NULL || game->description[0] == '\0')
        return NULL;
    return game->description;
}

void game_open_log_file(Game *game, char *filename)
{
    if (game == NULL || filename == NULL)
        return;
    game->log = fopen(filename, "w");
}

FILE *game_get_log_file(Game *game)
{
    return game != NULL ? game->log : NULL;
}

BOOL game_logfile_exist(Game *game)
{
    return game->log != NULL ? TRUE : FALSE;
}

BOOL game_is_over(Game *game)
{
    (void)game;
    return FALSE;
}

STATUS game_save(FILE *fp, Game *g)
{
    if (g == NULL || fp == NULL)
        return ERROR;

    for (int i = 0; i < MAX_SPACES; i++)
    {
        if (g->spaces[i] != NULL)
            space_save(fp, g->spaces[i]);
        else
            break;
    }
    dice_save(fp, g->dice);
    for (int i = 0; i < game_get_number_object(g); i++)
    {
        object_save(fp, g->objects[i]);
    }
    player_save(fp, g->player);
    return OK;
}

/**
   Callbacks implementation for each action 
*/

STATUS game_callback_unknown(Game *game)
{
    (void)game;
    return OK;
}

STATUS game_callback_exit(Game *game)
{
    for (int i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    {
        object_destroy(&game->objects[i]);
    }
    player_destroy(&game->player);
    dice_destroy(&game->dice);
    return OK;
}

STATUS game_callback_next(Game *game)
{
    Space *location = game_get_space(game, game_get_player_location(game));
    Id next_location = link_get_second_space(space_get_south(location));
    if (next_location == NO_ID)
        return ERROR;
    game_set_player_location(game, next_location);
    return OK;
}

STATUS game_callback_back(Game *game)
{
    Space *location = game_get_space(game, game_get_player_location(game));
    Id next_location = link_get_second_space(space_get_north(location));
    if (next_location == NO_ID)
        return ERROR;
    game_set_player_location(game, next_location);
    return OK;
}

STATUS game_callback_take(Game *game)
{
    char input[20];
    Space *location = game_get_space(game, game_get_player_location(game));

    if (space_objects_count(location) == 0)
        return ERROR;

    if (scanf("%s", input) > 0)
    {
        strcpy(game->argument, input);
        if (player_inventory_full(game->player))
            return ERROR;

        Object *obj = game_get_object_by_name(game, input);
        if (obj == NULL || object_get_movable(obj) == FALSE)
            return ERROR;

        if (object_get_dependency(obj) != NO_ID)
        {
            if (inventory_has_id(player_get_inventory(game->player), object_get_dependency(obj)) == FALSE)
                return ERROR;
        }

        if (space_remove_object(location, object_get_id(obj)) == ERROR)
            return ERROR;

        player_add_object(game->player, obj);
    }
    return OK;
}

STATUS game_callback_drop(Game *game)
{
    char input[20];
    if (scanf("%s", input) > 0)
    {
        strcpy(game->argument, input);
        Object *obj = game_get_object_by_name(game, input);
        if (obj == NULL)
            return ERROR;

        Space *s = game_get_space(game, game_get_player_location(game));
        if (player_delete_object(game->player, obj) == ERROR)
            return ERROR;

        game_drop_object(game, s, obj);
    }
    return OK;
}

STATUS game_callback_roll(Game *game)
{
    dice_roll(game->dice);
    return OK;
}

STATUS game_callback_left(Game *game)
{
    Space *location = game_get_space(game, game_get_player_location(game));
    Id next_location = link_get_second_space(space_get_west(location));
    if (next_location == NO_ID)
        return ERROR;
    game_set_player_location(game, next_location);
    return OK;
}

STATUS game_callback_right(Game *game)
{
    Space *location = game_get_space(game, game_get_player_location(game));
    Id next_location = link_get_second_space(space_get_east(location));
    if (next_location == NO_ID)
        return ERROR;
    game_set_player_location(game, next_location);
    return OK;
}

STATUS game_callback_move(Game *game)
{
    char input[20];

    if (scanf("%s", input) <= 0)
        return ERROR;

    strcpy(game->argument, input);
    if (strcmp(input, "north") == 0 || strcmp(input, "n") == 0)
    {
        return game_callback_back(game);
    }
    else if (strcmp(input, "south") == 0 || strcmp(input, "s") == 0)
    {
        return game_callback_next(game);
    }
    else if (strcmp(input, "west") == 0 || strcmp(input, "w") == 0)
    {
        return game_callback_left(game);
    }
    else if (strcmp(input, "east") == 0 || strcmp(input, "e") == 0)
    {
        return game_callback_right(game);
    }

    return ERROR;
}

STATUS game_callback_inspect(Game *game)
{
    char input[20];
    memset(game->description, '\0', 50);

    Space *space = game_get_space(game, game_get_player_location(game));

    if (scanf("%s", input) > 0)
    {
        strcpy(game->argument, input);
        if (strcasecmp(input, "s") == 0 || strcasecmp(input, "space") == 0)
        {
            strcat(game->description, "space - ");
            strcat(game->description, space_get_description(space));
            return OK;
        }
        else
        {
            Object *obj = game_get_object_by_name(game, input);
            if (obj == NULL)
                return ERROR;

            if (space_hasObject(space, object_get_id(obj)) == TRUE || player_search_inventory(game->player, obj) == TRUE)
            {
                strcat(game->description, object_get_name(obj));
                strcat(game->description, " - ");
                strcat(game->description, object_get_description(obj));
                return OK;
            }
        }
    }
    return ERROR;
}

STATUS game_callback_turn_on(Game *game)
{
    char input[20];

    if (scanf("%s", input) > 0)
    {
        strcpy(game->argument, input);
        Object *obj = game_get_object_by_name(game, input);
        if (obj == NULL || object_get_illuminate(obj) == FALSE)
            return ERROR;

        Space *playerLocation = game_get_space(game, game_get_player_location(game));
        if (space_hasObject(playerLocation, object_get_id(obj)) == TRUE || player_search_inventory(game->player, obj) == TRUE)
        {
            object_set_turnedOn(obj, TRUE);
            return OK;
        }
    }

    return ERROR;
}

STATUS game_callback_turn_off(Game *game)
{
    char input[20];

    if (scanf("%s", input) > 0)
    {
        strcpy(game->argument, input);
        Object *obj = game_get_object_by_name(game, input);
        if (obj == NULL || object_get_illuminate(obj) == FALSE)
            return ERROR;

        Space *playerLocation = game_get_space(game, game_get_player_location(game));
        if (space_hasObject(playerLocation, object_get_id(obj)) == TRUE || player_search_inventory(game->player, obj) == TRUE)
        {
            object_set_turnedOn(obj, FALSE);
            return OK;
        }
    }

    return ERROR;
}

STATUS game_callback_open_link_with_obj(Game *game)
{
    char input[20] = {0};

    scanf("%s", input);
    Link *link = game_get_link_by_name(game, input);
    if (link == NULL || player_get_location(game->player) != link_get_first_space(link))
        return ERROR;

    scanf("%s", input);
    if (strcmp(input, "with") != 0)
        return ERROR;

    scanf("%s", input);
    Object *object = game_get_object_by_name(game, input);
    if (object == NULL || player_search_inventory(game->player, object) == FALSE || object_get_openLink(object) != link_get_id(link))
        return ERROR;

    link_set_opened(link, TRUE);

    return ERROR;
}

STATUS game_callback_save(Game *game)
{
    char input[20] = {0};

    if (scanf("%s", input) > 0)
    {
        return game_management_save(input, game);
    }
    return ERROR;
}

STATUS game_callback_load(Game *game)
{
    char input[20] = {0};

    game_clear(game);

    if (scanf("%s", input) > 0)
    {
        return game_management_load(input, game);
    }
    return ERROR;
}