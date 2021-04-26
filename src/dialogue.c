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
char *_dialogue_unknown(STATUS st);
char *_dialogue_exit(STATUS st);
char *_dialogue_next(STATUS st);
char *_dialogue_back(STATUS st);
char *_dialogue_take(STATUS st);
char *_dialogue_drop(STATUS st);
char *_dialogue_roll(STATUS st);
char *_dialogue_left(STATUS st);
char *_dialogue_right(STATUS st);
char *_dialogue_move(STATUS st, Game *game);
char *_dialogue_inspect(STATUS st);
char *_dialogue_turnon(STATUS st);
char *_dialogue_turnoff(STATUS st);
char *_dialogue_open(STATUS st);

/******************************************
 **      Public Function Definition      **
 ******************************************/

//I need a way of ppassing the input/argument inside here
char *dialogue_print(T_Command cmd, STATUS st, Game *game)
{
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
        return _dialogue_exit(st);
        break;

    case NEXT:
        return _dialogue_next(st);

    case BACK:
        return _dialogue_back(st);
        break;

    case TAKE:
        return _dialogue_take(st);
        break;

    case DROP:
        return _dialogue_drop(st);
        break;

    case ROLL:
        return _dialogue_roll(st);
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
        return _dialogue_inspect(st);
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
        return "QUEEEE";
        break;
    }
}

/******************************************
 **      Private Function Defintion      **
 ******************************************/

char *_dialogue_nocmd()
{
    return "Introduce a command:";
}

char *_dialogue_unknown(STATUS st)
{
    return "What was the command?";
}
char *_dialogue_exit(STATUS st)
{
    return "Bye!";
}
char *_dialogue_next(STATUS st)
{
    if (st == OK)
        return "You moved to the next space";

    if (st == ERROR)
        return "You cannot advance to the next space";
}
char *_dialogue_back(STATUS st)
{
    if (st == OK)
        return "You moved to the previous space";

    if (st == ERROR)
        return "You cannot advance to the previous space";
}
char *_dialogue_take(STATUS st)
{
    if (st == OK)
        return "You took an object";

    if (st == ERROR)
        return "You cannot take that";
}
char *_dialogue_drop(STATUS st)
{
    if (st == OK)
        return "You droped an object";

    if (st == ERROR)
        return "You cannot drop an object";
}
char *_dialogue_roll(STATUS st)
{
    if (st == OK)
        return "You rolled the dice";

    if (st == ERROR)
        return "There was an error rolling the dice";
}
char *_dialogue_left(STATUS st)
{
    if (st == OK)
        return "You moved to the left";

    if (st == ERROR)
        return "You cannot move to the left";
}
char *_dialogue_right(STATUS st)
{
    if (st == OK)
        return "You moved to the right";

    if (st == ERROR)
        return "You cannot move to the right";
}

char *_dialogue_move(STATUS st, Game *game)
{
    char *arg;
    char *desc;
    char *result;
    arg = game_get_argument(game);
    //desc = space_get_description(game_get_space(game, game_get_player_location(game)));
    strcpy(desc, "temp description");
    if (desc == NULL)
        return "There was an error getting the description of the space";
    if (st == OK)
    {
        if (strcmp(arg, "north") == 0 || strcmp(arg, "n") == 0)
        {
            strcpy(result, "You moved to the north. Now you are in ");
            strcat(result, desc);
            return result;
        }
        else if (strcmp(arg, "south") == 0 || strcmp(arg, "s") == 0)
        {
            return "You moved to the south. Now you are in %s", desc;
        }
        else if (strcmp(arg, "west") == 0 || strcmp(arg, "w") == 0)
        {
            return "You moved to the west. Now you are in %s", desc;
        }
        else if (strcmp(arg, "east") == 0 || strcmp(arg, "e") == 0)
        {
            return "You moved to the east. Now you are in %s", desc;
        }
        else
        {
            return "You moved somewhere. Now you are in %s", desc;
        }
    }

    if (st == ERROR)
    {
        if (strcmp(arg, "north") == 0 || strcmp(arg, "n") == 0)
        {
            return "You cannot move to the north here";
        }
        else if (strcmp(arg, "south") == 0 || strcmp(arg, "s") == 0)
        {
            return "You cannot move to the south here";
        }
        else if (strcmp(arg, "west") == 0 || strcmp(arg, "w") == 0)
        {
            return "You cannot move to the west here";
        }
        else if (strcmp(arg, "east") == 0 || strcmp(arg, "e") == 0)
        {
            return "You cannot move to the east here";
        }
        else
        {
            return "You cannot move here";
        }
    }
}
char *_dialogue_inspect(STATUS st)
{
    return "TEST";
}
char *_dialogue_turnon(STATUS st)
{
    return "TEST";
}
char *_dialogue_turnoff(STATUS st)
{
    return "TEST";
}
char *_dialogue_open(STATUS st)
{
    return "TEST";
}