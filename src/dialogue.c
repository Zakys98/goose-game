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

    case NEXT:
        return _dialogue_next(st);

    case BACK:
        return _dialogue_back(st);
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

    case LEFT:
        return _dialogue_left(st);
        break;

    case RIGHT:
        return _dialogue_right(st);
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

    strcpy(result, "What was that command?");
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

    if (st == ERROR)
    {
        strcpy(result, "You cannot advance to the next space");
        return result;
    }

    return NULL;
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

    if (st == ERROR)
    {
        strcpy(result, "You cannot go to the previous space");
        return result;
    }
    return NULL;
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

    if (st == ERROR)
    {
        strcpy(result, "You cannot take that ");
        strcat(result, arg);
        return result;
    }
    return NULL;
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

    if (st == ERROR)
    {
        strcpy(result, "You cannot drop that ");
        strcat(result, arg);
        return result;
    }
    return NULL;
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

    if (st == ERROR)
    {
        strcpy(result, "Something went wrong with the dice");
        return result;
    }
    return NULL;
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

    if (st == ERROR)
    {
        strcpy(result, "You cannot go to the left");
        return result;
    }
    return NULL;
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

    if (st == ERROR)
    {
        strcpy(result, "You cannot go to the right");
        return result;
    }
    return NULL;
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
    if (!result)
        return NULL;

    arg = game_get_argument(game);

    // The same it is done in inspect command
    strcpy(desc, "space - ");
    strcat(desc, space_get_description(game_get_space(game, game_get_player_location(game))));
    //strcpy(desc, "temp description");
    if (desc == NULL)
    {
        free(desc);
        strcpy(result, "There was an error getting the description of the space");
    }
    if (st == OK)
    {
        if (strcmp(arg, "north") == 0 || strcmp(arg, "n") == 0)
        {
            strcpy(result, "You moved to the north. Now you are in ");
            strcat(result, desc);
            free(desc);
            return result;
        }
        else if (strcmp(arg, "south") == 0 || strcmp(arg, "s") == 0)
        {
            strcpy(result, "You moved to the south. Now you are in ");
            strcat(result, desc);
            free(desc);
            return result;
        }
        else if (strcmp(arg, "west") == 0 || strcmp(arg, "w") == 0)
        {
            strcpy(result, "You moved to the west. Now you are in ");
            strcat(result, desc);
            free(desc);
            return result;
        }
        else if (strcmp(arg, "east") == 0 || strcmp(arg, "e") == 0)
        {
            strcpy(result, "You moved to the east. Now you are in ");
            strcat(result, desc);
            free(desc);
            return result;
        }
        else
        {
            strcpy(result, "You moved to somewhere. Now you are in ");
            strcat(result, desc);
            free(desc);
            return result;
        }
    }

    if (st == ERROR)
    {
        if (strcmp(arg, "north") == 0 || strcmp(arg, "n") == 0)
        {
            strcpy(result, "You can't move to the north here");
            free(desc);
            return result;
        }
        else if (strcmp(arg, "south") == 0 || strcmp(arg, "s") == 0)
        {
            strcpy(result, "You can't move to the south here");
            free(desc);
            return result;
        }
        else if (strcmp(arg, "west") == 0 || strcmp(arg, "w") == 0)
        {
            strcpy(result, "You can't move to the west here");
            free(desc);
            return result;
        }
        else if (strcmp(arg, "east") == 0 || strcmp(arg, "e") == 0)
        {
            strcpy(result, "You can't move to the east here");
            free(desc);
            return result;
        }
        else
        {
            strcpy(result, "What was that direction?");
            free(desc);
            return result;
        }
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
    }

    if (st == OK)
    {
        strcpy(result, "Inspecting ");
        strcat(result, desc);
        return result;
    }

    if (st == ERROR)
    {
        strcpy(result, "You cannot inspect that");
        return result;
    }
    return NULL;
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

    if (st == ERROR)
    {
        strcpy(result, "Couldn't be turnt on");
        return result;
    }
    return NULL;
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

    if (st == ERROR)
    {
        strcpy(result, "Couldn't be turnt off");
        return result;
    }
    return NULL;
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

    if (st == ERROR)
    {
        strcpy(result, "Couldn't be turnt opened");
        return result;
    }
    return NULL;
}