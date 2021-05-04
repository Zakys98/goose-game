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

/*******************************************
 *      Private Functions Declaration      *
 *******************************************/

STATUS _game_rules_take_first_object(Game *game);

/**********************************
 *        Public Functions        *
 *********************************/

STATUS game_rules_random_command(Game *game)
{
    Dice *dice = NULL;
    int num;

    if (!game)
        return ERROR;

    // Create a dice to select the random command
    dice = dice_create(0, 6);
    if (!dice)
        return ERROR;

    num = dice_roll(dice);

    switch (num)
    {
    case 1:
        // We could change this to a exact object when we have the story written
        dice_destroy(&dice);
        return _game_rules_take_first_object(game);

        break;

    default:
        //Default will be no command so that there is not a random thing ocurring constantly
        dice_destroy(&dice);
        return OK;
        break;
    }

    return ERROR;
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

    if (space_objects_count(space) > 0 && player_inventory_full(player) == FALSE)
    {
        ids = space_get_objects(space);
        if (!ids)
        {
            return ERROR;
        }
        id = ids[0];

        if (id != NO_ID)
        {
            inv = player_get_inventory(player);
            if (!inv)
            {
                free(ids);
                return ERROR;
            }

            if (inventory_has_id(inv, id) == TRUE)
            {
                free(ids);
                return OK;
            }
        }

        if (space_remove_object(space, id) == ERROR)
        {
            free(ids);
            return ERROR;
        }
        if (inventory_add_id(player_get_inventory(player), id) == ERROR)
        {
            free(ids);
            return ERROR;
        }

        free(ids);
        return OK;
    }

    return OK;
}