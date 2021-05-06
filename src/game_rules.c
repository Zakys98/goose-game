/**
 * @file game_rules.c
 * @author Ivan del Horno Sotillo
 * @brief Implementation for game rules module
 * @version 0.1
 * @date 2021-05-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../include/game_rules.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @todo Write links to open/close when we have the data file
 * @todo Write rooms to turn on/off when we have the data file
 * @todo Maybe instead of take first object we can put a concrete object in the inventory (a Torch or something)
 */

/*******************************************
 *      Private Functions Declaration      *
 *******************************************/

/**
 * @brief Takes the first object in that space and sets it to the player's inventory
 * 
 * @param game Pointer to the game
 * @return STATUS 
 */
STATUS _game_rules_take_first_object(Game *game);

/**
 * @brief Kills the player randomly, aka, moves him to the first space
 * 
 * @param game Pointer to the game
 * @return STATUS 
 */
STATUS _game_rules_die(Game *game);

/**
 * @brief Drops the first object in the player's inventory
 * 
 * @param game Pointer to the game
 * @return STATUS 
 */
STATUS _game_rules_drop_first_object(Game *game);

/**
 * @brief Suddenly closes the links at a specific room
 * 
 * @param game Pointer to game
 * @return STATUS 
 */
STATUS _game_rules_close_link(Game *game);

/**
 * @brief Suddenly closes the links at a specific room
 * 
 * @param game Pointer to game
 * @return STATUS 
 */
STATUS _game_rules_open_link(Game *game);

/**
 * @brief Suddenly turns on the light of current/specific room
 * 
 * @param game Pointer to game
 * @return STATUS 
 */
STATUS _game_rules_onlight_room(Game *game);

/**
 * @brief Suddenly turns off the light of current/specific room
 * 
 * @param game Pointer to game
 * @return STATUS 
 */
STATUS _game_rules_offlight_room(Game *game);

/**********************************
 *        Public Functions        *
 *********************************/

STATUS game_rules_random_command(Game *game)
{
    Dice *dice = NULL;
    int num;

    if (!game)
        return ERROR;

    if (game_get_last_command(game) == EXIT)
        return OK;

    // Create a dice to select the random command
    dice = dice_create(0, 50);
    if (!dice)
        return ERROR;

    num = dice_roll(dice);

    if (num >= 0 && num <= 10)
    {
        // We could change this to a exact object when we have the story written
        // Prob: 10/50 = 20%

        dice_destroy(&dice);
        return _game_rules_take_first_object(game);
    }
    else if (num == 11)
    {
        // Randomly moves the player to the beginning aka dies
        // Prob: 1/50: 2%

        dice_destroy(&dice);
        return _game_rules_die(game);
    }
    else if (num > 11 && num <= 20)
    {
        // Drops object from player's inventory
        // Prob: 9/50: 18%

        dice_destroy(&dice);
        return _game_rules_drop_first_object(game);
    }
    else if (num > 20 && num <= 25)
    {
        // Closes Links
        // Prob: 5/50: 10%

        dice_destroy(&dice);
        return _game_rules_close_link(game);
    }
    else if (num > 25 && num <= 30)
    {
        // Opens Links
        // Prob: 5/50: 10%

        dice_destroy(&dice);
        return _game_rules_open_link(game);
    }
    else if (num > 30 && num <= 35)
    {
        // Turns on light
        // Prob: 5/50: 10%

        dice_destroy(&dice);
        return _game_rules_onlight_room(game);
    }
    else if (num > 35 && num <= 40)
    {
        // Turns off the light
        // Prob: 5/50: 10%

        dice_destroy(&dice);
        return _game_rules_offlight_room(game);
    }
    else
    {
        //Default will be no command so that there is not a random thing ocurring constantly
        dice_destroy(&dice);
        return OK;
    }

    //Default will be no command so that there is not a random thing ocurring constantly
    dice_destroy(&dice);
    return OK;
}

/******************************************
 *      Private Functions Definition      *
 ******************************************/

STATUS _game_rules_take_first_object(Game *game)
{

    Space *space = NULL;
    Player *player = NULL;
    Id *ids = NULL;
    Id id = NO_ID;
    Inventory *inv = NULL;

    space = game_get_space(game, game_get_player_location(game));

    if (!space)
        return ERROR;

    player = game_get_player(game);
    if (!player)
        return ERROR;

    if ((space_objects_count(space) > 0) && (player_inventory_full(player) == FALSE))
    {
        // Gets set of IDS in the space
        ids = space_get_objects(space);
        if (!ids)
        {
            return ERROR;
        }
        id = ids[0];

        // If the ID is NO_ID there's a problem
        if (id == NO_ID)
        {
            free(ids);
            return ERROR;
        }

        // Gets the inventory of the player
        inv = player_get_inventory(player);
        if (!inv)
        {
            free(ids);
            return ERROR;
        }

        // This was creating some mistakes

        // If the inventory is not empty, checks if it has the object
        // if (inventory_isEmpty(inv) == FALSE)
        // {
        //     if (inventory_has_id(inv, id) == TRUE)
        //     {
        //         free(ids);
        //         return OK;
        //     }
        // }
    }

    if (space_remove_object(space, id) == ERROR)
    {
        free(ids);
        return ERROR;
    }

    if (inventory_add_id(inv, id) == ERROR)
    {
        free(ids);
        return ERROR;
    }

    free(ids);
    return OK;
}

STATUS _game_rules_die(Game *game)
{
    Player *player = NULL;

    player = game_get_player(game);
    if (!player)
        return ERROR;

    return player_set_location(player, 1);
}

STATUS _game_rules_drop_first_object(Game *game)
{
    Space *space = NULL;
    Player *player = NULL;
    Id *ids = NULL;
    Id id = NO_ID;
    Inventory *inv = NULL;

    space = game_get_space(game, game_get_player_location(game));

    if (!space)
        return ERROR;

    player = game_get_player(game);
    if (!player)
        return ERROR;

    inv = player_get_inventory(player);
    if (!inv)
        return ERROR;

    if (inventory_isEmpty(inv) == FALSE)
    {
        ids = inventory_get_elements(inv);
        if (!ids)
        {
            return ERROR;
        }
        id = ids[0];

        if (id != NO_ID)
        {
            free(ids);
            if (space_add_object(space, id) == ERROR)
                return ERROR;
            if (inventory_del_id(inv, id) == ERROR)
                return ERROR;

            return OK;
        }

        free(ids);
        return ERROR;
    }

    return ERROR;
}

STATUS _game_rules_close_link(Game *game)
{
    // We must set this to a custom room after we write the data with the story.
    Link *link = game_get_link_by_name(game, "Link1");
    if (!link)
        return ERROR;

    return link_set_opened(link, FALSE);
}

STATUS _game_rules_open_link(Game *game)
{
    // We must set this to a custom room after we write the data with the story.
    Link *link = game_get_link_by_name(game, "Link1");
    if (!link)
        return ERROR;

    return link_set_opened(link, TRUE);
}

STATUS _game_rules_onlight_room(Game *game)
{
    //I need to know how does turn on and off work to make these two
    return OK;
}

STATUS _game_rules_offlight_room(Game *game)
{
    //I need to know how does turn on and off work to make these two
    return OK;
}
