/**
 * @file dialogue.c
 * @author Ivan del Horno Sotillo
 * @brief Defines the Dialogue interface
 * @version 0.1
 * @date 2021-04-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../include/dialogue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************************
 **      Private Function Declaration      **
 ********************************************/

/* Private definiton for each of the command */

char *_dialogue_nocmd();
char *_dialogue_unknown();
char *_dialogue_exit();
char *_dialogue_next(STATUS st);
char *_dialogue_back(STATUS st);
char *_dialogue_take(STATUS st, Game *game);
char *_dialogue_drop(STATUS st, Game *game);
char *_dialogue_roll(STATUS st, Game *game);
char *_dialogue_left(STATUS st);
char *_dialogue_right(STATUS st);
char *_dialogue_move(STATUS st, Game *game);
char *_dialogue_inspect(STATUS st, Game *game);
char *_dialogue_turnon(STATUS st);
char *_dialogue_turnoff(STATUS st);
char *_dialogue_open(STATUS st);

/******************************************
 **      Public Function Definition      **
 ******************************************/

//I need a way of ppassing the input/argument inside here
char *dialogue_print(T_Command cmd, STATUS st, Game *game)
{
    char *result = NULL;

    if (game == NULL)
        return NULL;

    if (st != OK && st != ERROR)
        return NULL;

    // Compares the previous command to the actual one, we dont want to print this if there was no command
    if (game_get_prev_command(game) == cmd && game_get_prev_command(game) != NO_CMD)
    {
        // If they are the same and there is an error, message is shown
        if (st == ERROR)
        {
            result = malloc(sizeof(char) * 300);
            strcpy(result, "You have done this before without success.");
            return result;
        }
    }

    // If there is an error we keep the command
    if (st == ERROR)
    {
        game_set_prev_command(game, cmd);
    }
    else
    {
        // If there was no error we set it to NO_CMD so there are no errors when comparing them
        game_set_prev_command(game, NO_CMD);
    }
    /* Based on the introduced command, calls the needed function with the needed arguments */
    switch (cmd)
    {
    case NO_CMD:
        return _dialogue_nocmd();
        break;

    case UNKNOWN:
        return _dialogue_unknown(st);
        break;

    case EXIT:
        return _dialogue_exit();
        break;

    case TAKE:
        return _dialogue_take(st, game);
        break;

    case DROP:
        return _dialogue_drop(st, game);
        break;

    case ROLL:
        return _dialogue_roll(st, game);
        break;

    case MOVE:
        return _dialogue_move(st, game);
        break;

    case INSPECT:
        return _dialogue_inspect(st, game);
        break;

    case TURNON:
        return _dialogue_turnon(st);
        break;

    case TURNOFF:
        return _dialogue_turnoff(st);
        break;

    case OPEN:
        return _dialogue_open(st);
        break;

    default:

        result = malloc(sizeof(char) * 300);
        strcpy(result, "QUEEEEEE");
        return result;
        break;
    }
}

/******************************************
 **      Private Function Defintion      **
 ******************************************/

char *_dialogue_nocmd()
{
    char *result;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    strcpy(result, "Introduce a command: ");
    return result;
}

char *_dialogue_unknown()
{
    char *result;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    strcpy(result, "This is not a valid action. Try again.");
    return result;
}
char *_dialogue_exit()
{
    char *result;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    strcpy(result, "Bye Bye!");
    return result;
}
char *_dialogue_next(STATUS st)
{
    char *result;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    if (st == OK)
    {
        strcpy(result, "You moved to the next space");
        return result;
    }

    strcpy(result, "You cannot advance to the next space");
    return result;
}
char *_dialogue_back(STATUS st)
{
    char *result;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    if (st == OK)
    {
        strcpy(result, "You moved to the previous space");
        return result;
    }

    strcpy(result, "You cannot go to the previous space");
    return result;
}
char *_dialogue_take(STATUS st, Game *game)
{
    char *result;
    char *arg;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    arg = game_get_argument(game);
    if (!arg)
    {
        free(result);
        return NULL;
    }

    if (st == OK)
    {
        strcpy(result, "You took ");
        strcat(result, arg);
        return result;
    }

    strcpy(result, "You cannot take that ");
    strcat(result, arg);
    return result;
}
char *_dialogue_drop(STATUS st, Game *game)
{
    char *result;
    char *arg;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    arg = game_get_argument(game);
    if (!arg)
    {
        free(result);
        return NULL;
    }

    if (st == OK)
    {
        strcpy(result, "You droped ");
        strcat(result, arg);
        return result;
    }

    strcpy(result, "You cannot drop that ");
    strcat(result, arg);
    return result;
}
char *_dialogue_roll(STATUS st, Game *game)
{
    char *result;
    char num[2];
    int numero;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    numero = (dice_get_last_roll(game_get_dice(game)));
    sprintf(num, "%d", numero);

    if (st == OK)
    {
        strcpy(result, "You rolled dice and got... ");
        strcat(result, num);
        return result;
    }

    strcpy(result, "Something went wrong with the dice");
    return result;
}
char *_dialogue_left(STATUS st)
{
    char *result;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    if (st == OK)
    {
        strcpy(result, "You moved to the left");
        return result;
    }

    strcpy(result, "You cannot go to the left");
    return result;
}
char *_dialogue_right(STATUS st)
{
    char *result;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    if (st == OK)
    {
        strcpy(result, "You moved to the right");
        return result;
    }

    strcpy(result, "You cannot go to the right");
    return result;
}

char *_dialogue_move(STATUS st, Game *game)
{
    char *arg;
    char *desc;
    char *result;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    desc = malloc(sizeof(char) * 300);
    if (!desc)
        return NULL;

    arg = game_get_argument(game);

    // The same it is done in inspect command
    strcpy(desc, "space - ");
    char temp[10] = {0};
    sprintf(temp,"%ld", space_get_id(game_get_space(game, game_get_player_location(game))));
    strcat(desc, temp);
    
    if (desc == NULL)
    {
        strcpy(result, "There was an error getting the description of the space");
    }
    if (st == OK)
    {
        if (strcmp(arg, "north") == 0 || strcmp(arg, "n") == 0)
        {
            strcpy(result, "You moved to the north. Now you are in ");
        }
        else if (strcmp(arg, "south") == 0 || strcmp(arg, "s") == 0)
        {
            strcpy(result, "You moved to the south. Now you are in ");
        }
        else if (strcmp(arg, "west") == 0 || strcmp(arg, "w") == 0)
        {
            strcpy(result, "You moved to the west. Now you are in ");
        }
        else if (strcmp(arg, "east") == 0 || strcmp(arg, "e") == 0)
        {
            strcpy(result, "You moved to the east. Now you are in ");
        }
        else
        {
            strcpy(result, "You moved to somewhere. Now you are in ");
        }
        strcat(result, desc);
        free(desc);
        return result;
    }

    if (st == ERROR)
    {
        if (strcmp(arg, "north") == 0 || strcmp(arg, "n") == 0)
        {
            strcpy(result, "You can't move to the north here");
        }
        else if (strcmp(arg, "south") == 0 || strcmp(arg, "s") == 0)
        {
            strcpy(result, "You can't move to the south here");
        }
        else if (strcmp(arg, "west") == 0 || strcmp(arg, "w") == 0)
        {
            strcpy(result, "You can't move to the west here");
        }
        else if (strcmp(arg, "east") == 0 || strcmp(arg, "e") == 0)
        {
            strcpy(result, "You can't move to the east here");
        }
        else
        {
            strcpy(result, "What was that direction?");
        }
        free(desc);
        return result;
    }
    return NULL;
}
char *_dialogue_inspect(STATUS st, Game *game)
{
    char *desc;
    char *result;

    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    desc = game_get_description(game);

    if (desc == NULL)
    {
        strcpy(result, "There was an error inspecting the object");
        return result;
    }

    if (st == OK)
    {
        strcpy(result, "Inspecting ");
        strcat(result, desc);
        return result;
    }

    strcpy(result, "You cannot inspect that");
    return result;
}
char *_dialogue_turnon(STATUS st)
{
    char *result;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    if (st == OK)
    {
        strcpy(result, "Turnt on");
        return result;
    }

    strcpy(result, "Couldn't be turnt on");
    return result;

}
char *_dialogue_turnoff(STATUS st)
{
    char *result;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    if (st == OK)
    {
        strcpy(result, "Turnt off");
        return result;
    }

    strcpy(result, "Couldn't be turnt off");
    return result;

}
char *_dialogue_open(STATUS st)
{
    char *result;
    result = malloc(sizeof(char) * 300);
    if (!result)
        return NULL;

    if (st == OK)
    {
        strcpy(result, "Opened");
        return result;
    }

    strcpy(result, "Couldn't be turnt opened");
    return result;
}