/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Eva Moresova
 * @version 1.0
 * @date 10-02-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/game_rules.h"
#include "../include/graphic_engine.h"

// Prototypes

/**
 * @brief Initialize the game but without the random rules
 * @author Ivan del Horno
 * @param game 
 * @param argc 
 * @param argv 
 */
void game_init_rules(Game *game, int argc, char **argv);

/**
 * @brief initialize game and game engine
 *
 * @author Eva Moresova
 * @date 10-02-2021
 * 
 * @param game pointer to game, which is initialized
 * @param gengine double pointer to game engine, which is initialized
 * @param file_name name of file, which game is initialized 
 * @return int 0 = OK, 1 = FAIL
 */
int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);

/**
 * @brief main loop of the game
 *
 * @author Eva Moresova
 * @date 10-02-2021
 * 
 * @param game inittialized game
 * @param gengine pointer to initialized game engine
 */
void game_loop_run(Game *game, Graphic_engine *gengine);

/**
 * @brief clean(free) game and game engine
 *
 * @author Eva Moresova
 * @date 10-02-2021
 * 
 * @param game inittialized game
 * @param gengine pointer to initialized game engine
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

void game_init_from_arguments(Game *game, int argc, char **argv);

int main(int argc, char *argv[])
{
    Game *game = game_init();
    if (game == NULL)
        return 1;
    Graphic_engine *gengine;

    if (argc < 2)
    {
        fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
        return 1;
    }

    if (!game_loop_init(game, &gengine, argv[1]))
    {
        game_init_rules(game, argc, argv);
        game_init_from_arguments(game, argc, argv);
        game_loop_run(game, gengine);
        game_loop_cleanup(game, gengine);
    }

    return 0;
}

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name)
{
    if (game_create_from_file(game, file_name) == ERROR)
    {
        fprintf(stderr, "Error while initializing game.\n");
        Player *pl = game_get_player(game);
        player_destroy(&pl);
        Dice *d = game_get_dice(game);
        dice_destroy(&d);
        return 1;
    }

    if ((*gengine = graphic_engine_create()) == NULL)
    {
        fprintf(stderr, "Error while initializing graphic engine.\n");
        game_destroy(game);
        return 1;
    }

    return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine)
{
    T_Command command = NO_CMD;
    T_Rules rule = NO_RULE;
    STATUS s = ERROR;
    BOOL b = TRUE;

    

    while ((command != EXIT) && !game_is_over(game))
    {
        graphic_engine_paint_game(gengine, game, s);
        command = get_user_input();
        s = game_update(game, command);
        b = game_rules_get(game);
        if (b == TRUE)
        {
            rule = game_get_last_rule(game);
            game_rules_random_command(rule, game);
        }
    }
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine)
{
    game_destroy(game);
    graphic_engine_destroy(gengine);
}

void game_init_from_arguments(Game *game, int argc, char **argv)
{
    for (int i = 2; i < argc; i += 2)
    {
        if (strcmp(argv[i], "-l") == 0 && argc >= i)
        {
            game_open_log_file(game, argv[i + 1]);
        }
    }
}

void game_init_rules(Game *game, int argc, char **argv)
{
    for (int i = 2; i < argc; i += 2)
    {
        if (strcmp(argv[i], "-r") == 0 && argc >= i)
        {
            game_rules_sel(game, FALSE);
        }
    }

    game_rules_sel(game, TRUE);
}