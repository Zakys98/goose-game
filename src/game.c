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
    T_Rules last_rule;
    Dice *dice;
    FILE *log;
    char description[50];
    char *argument; //Argument used after a command
    BOOL rules;
};

typedef enum
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    UP,
    DOWN
} direction;

#define N_CALLBACK 12

/**
   Define the function type for the callbacks
*/
typedef STATUS (*callback_fn)(Game *game);

/**
   List of callbacks for each command in the game 
*/

STATUS game_callback_unknown(Game *game);
STATUS game_callback_exit(Game *game);

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
    game_callback_take,
    game_callback_drop,
    game_callback_roll,
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
 * @brief Selects a random rule and returns it
 * 
 * @return T_Rules 
 */
T_Rules game_random_rule();

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
 * @brief returns id of next space depends on direction
 *
 * @author Jiri Zak
 * @date 7-05-2021
 * 
 * @param game pointer to game
 * @param direction direction
 * @return id of space or NO_ID
 */
Id choose_direction(Game *game, direction dir);

STATUS game_move(Game *game, direction dir);

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
    game->last_rule = NO_RULE;
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

    for (int i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    {
        object_destroy(&game->objects[i]);
    }
    player_destroy(&game->player);
    dice_destroy(&game->dice);

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
    if (game == NULL || name == NULL) {
        return NULL;
	}

	Space* s = game_get_space(game, game_get_player_location(game));
    
	Link *east = space_get_east(s);
	if (east != NULL)
	{
		if (strcasecmp(link_get_name(east), name) == 0)
			return east;
	}
	Link *west = space_get_west(s);
	if (west != NULL)
	{
		if (strcasecmp(link_get_name(west), name) == 0)
			return west;
	}
	Link *north = space_get_north(s);
	if (north != NULL)
	{
		if (strcasecmp(link_get_name(north), name) == 0)
			return north;
	}
	Link *south = space_get_south(s);
	if (south != NULL)
	{
		if (strcasecmp(link_get_name(south), name) == 0)
			return south;
	}
	Link *up = space_get_up(s);
	if (up != NULL)
	{
		if (strcasecmp(link_get_name(up), name) == 0)
			return up;
	}
	Link *down = space_get_down(s);
	if (down != NULL)
	{
		if (strcasecmp(link_get_name(down), name) == 0)
			return down;
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
    game->last_rule = game_random_rule();
    return (*game_callback_fn_list[cmd])(game);
}

T_Rules game_get_last_rule(Game *game)
{
    return game->last_rule;
}

T_Rules game_random_rule()
{
    Dice *dice = NULL;
    int num;

    // Create a dice to select the random command
    dice = dice_create(0, 100);
    if (!dice)
        return NO_RULE;

    num = dice_roll(dice);
    dice_destroy(&dice);

    if (num >= 0 && num < 5)
        return TAKERULE;
    else if (num == 5)
        return DIERULE;
    else if (num > 5 && num <= 10)
        return DROPRULE;
    else if (num > 20 && num <= 25)
        return ONRULE;
    else if (num > 25 && num <= 30)
        return OFFRULE;
    else
        return NO_RULE;

    return NO_RULE;
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

char *game_get_space_description(Game *game)
{
    Id location;
    Space *user_space;

    if (game == NULL)
        return NULL;

    location = player_get_location(game->player);

    for(int i=0; i < MAX_SPACES; i++)
    {
        if(space_get_id(game->spaces[i])== location)
        {
            user_space= game->spaces[i];
            break;
        }
    }

    return (char*)space_get_description(user_space);
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
    Space *location = game_get_space(game, game_get_player_location(game));
    if(space_get_id(location) == 14)
        return TRUE;
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

Id choose_direction(Game *game, direction dir)
{
    Space *location = game_get_space(game, game_get_player_location(game));
    Id direction = NO_ID;
    Link *l = NULL;
    switch (dir)
    {
    case NORTH:
        l = space_get_north(location);
        break;
    case SOUTH:
        l = space_get_south(location);
        break;
    case EAST:
        l = space_get_east(location);
        break;
    case WEST:
        l = space_get_west(location);
        break;
    case UP:
        l = space_get_up(location);
        break;
    case DOWN:
        l = space_get_down(location);
        break;
    default:
        break;
    }
    if (link_get_opened(l) == TRUE)
        direction = link_get_second_space(l);
    return direction;
}

STATUS game_move(Game *game, direction dir)
{
    Id next_location = choose_direction(game, dir);
    if (next_location == NO_ID)
        return ERROR;
    game_set_player_location(game, next_location);
    return OK;
}

BOOL game_player_has_light(Game* game) {
	Id* inventory_ids = inventory_get_elements(player_get_inventory(game->player));
	Object* o = NULL;
	for (int i = 0; i < inventory_get_nObjects(player_get_inventory(game->player)); i++) {
		o = game_get_object(game, inventory_ids[i]);
		if (object_get_illuminate(o) == TRUE && object_get_turnedOn(o) == TRUE) {
			free(inventory_ids);
			return TRUE;
		}
	}
	free(inventory_ids);
	return FALSE;
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
    (void)game;
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

STATUS game_callback_move(Game *game)
{
    char input[20];

    if (scanf("%s", input) <= 0)
        return ERROR;

    strcpy(game->argument, input);
    if (strcmp(input, "north") == 0 || strcmp(input, "n") == 0)
    {
        return game_move(game, NORTH);
    }
    else if (strcmp(input, "south") == 0 || strcmp(input, "s") == 0)
    {
        return game_move(game, SOUTH);
    }
    else if (strcmp(input, "west") == 0 || strcmp(input, "w") == 0)
    {
        return game_move(game, WEST);
    }
    else if (strcmp(input, "east") == 0 || strcmp(input, "e") == 0)
    {
        return game_move(game, EAST);
    }
    else if (strcmp(input, "up") == 0 || strcmp(input, "u") == 0)
    {
        return game_move(game, UP);
    }
    else if (strcmp(input, "down") == 0 || strcmp(input, "d") == 0)
    {
        return game_move(game, DOWN);
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
            if (space_get_illumination(space))
            {
                strcat(game->description, "space - ");
                strcat(game->description, space_get_detailed_description(space));
                return OK;
            }
        }
        else
        {
            if (space_get_illumination(space))
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

		Id dependency = object_get_dependency(obj); 
		if (dependency != NO_ID && !player_has_object(game->player, dependency))
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

void open_link(Game* game, Link* link) {
	link_set_opened(link, TRUE);
	Space* s = game_get_space(game, link_get_second_space(link));
	link_set_opened(space_get_link_by_name(s, (char *)link_get_name(link)), TRUE);
}

STATUS game_callback_open_link_with_obj(Game *game)
{
    char input[20] = {0};

    scanf("%s", input);
    Link *link = game_get_link_by_name(game, input);
    if (link == NULL || player_get_location(game->player) != link_get_first_space(link))
        return ERROR;

    scanf("%s", input);
    if (strcasecmp(input, "with") != 0)
        return ERROR;

    scanf("%s", input);

	if (strcasecmp(link_get_name(link), "SafeDoor") == 0 && strcmp(input, "495") == 0) {
		open_link(game, link);
    	return OK;
	}

    Object *object = game_get_object_by_name(game, input);
    if (object == NULL || player_search_inventory(game->player, object) == FALSE || object_get_openLink(object) != link_get_id(link))
        return ERROR;

    open_link(game, link);
    return OK;
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

void game_rules_sel(Game *game, BOOL bul)
{
    game->rules = bul;
}

BOOL game_rules_get(Game *game)
{
    return game->rules;
}