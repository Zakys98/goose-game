#include "../include/graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/command.h"
#include "../include/screen.h"
#include "../include/dialogue.h"

struct _Graphic_engine
{
    Area *map, *descript, *banner, *help, *feedback;
};

//Private functions

/**
 * @brief Paint important things to description area
 *
 * @author Jiri Zak
 * @date 02-03-2021
 * 
 * @param ge pointer to graphic_engine
 * @param game pointer to game
 */
void graphic_engine_paint_description_area(Graphic_engine *ge, Game *game);

/**
 * @brief Get string of all object names in a space
 *
 * @author Eva Moresova
 * @date 14-03-2021
 * 
 * @param g pointer to game
 * @param s pointer to space
 * @return string with names of all objects in the specified space
 */
char *graphic_engine_get_space_objects(Game *g, Space *s);

//Implementation

Graphic_engine *graphic_engine_create()
{
    static Graphic_engine *ge = NULL;

    if (ge)
        return ge;

    screen_init();
    ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
    if (ge == NULL)
        return NULL;

    ge->map = screen_area_init(1, 1, 54, 19);
    ge->descript = screen_area_init(56, 1, 35, 13);
    ge->banner = screen_area_init(28, 21, 23, 1);
    ge->help = screen_area_init(1, 22, 88, 2);
    ge->feedback = screen_area_init(1, 26, 88, 2);

    return ge;
}

void graphic_engine_destroy(Graphic_engine *ge)
{
    if (!ge)
        return;

    screen_area_destroy(ge->map);
    screen_area_destroy(ge->descript);
    screen_area_destroy(ge->banner);
    screen_area_destroy(ge->help);
    screen_area_destroy(ge->feedback);

    screen_destroy();
    free(ge);
}

char *graphic_engine_get_space_objects(Game *g, Space *s)
{
    if (space_objects_count(s) == 0)
        return NULL;

    Id *obj_ids = space_get_objects(s);
    char *res = (char *)malloc(20);
    char *object_names = res;
    Object *obj = game_get_object(g, obj_ids[0]);

    object_names += sprintf(object_names, "%s", object_get_name(obj));

    for (int i = 1; i < space_objects_count(s); i++)
    {
        obj = game_get_object(g, obj_ids[i]);
        object_names += sprintf(object_names, ", %s", object_get_name(obj));
    }
    free(obj_ids);
    return res;
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game, STATUS s)
{
    Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID;
    Space *space_act = NULL;
    char str[255];
    T_Rules last_rule = NO_RULE;
    T_Command last_cmd = UNKNOWN;
    //extern char *cmd_to_str[N_CMD][N_CMDT];
    char *objects = NULL, *toprint = NULL;

    /* Paint the in the map area */
    screen_area_clear(ge->map);
    if ((id_act = game_get_player_location(game)) != NO_ID)
    {
        space_act = game_get_space(game, id_act);
        id_back = link_get_second_space(space_get_north(space_act));
        id_next = link_get_second_space(space_get_south(space_act));
        objects = graphic_engine_get_space_objects(game, space_act);

        if (id_back != NO_ID)
        {
            sprintf(str, "         |            %2d|", (int)id_back);
            screen_area_puts(ge->map, str);
            sprintf(str, "         |%s|", space_get_name(game_get_space(game, id_back)));
            screen_area_puts(ge->map, str);
            sprintf(str, "         +--------------+");
            screen_area_puts(ge->map, str);
            sprintf(str, "               ^ %s", link_get_name(space_get_north(space_act)));
            screen_area_puts(ge->map, str);
        }

        if (id_act != NO_ID)
        {
            sprintf(str, "         +--------------+");
            screen_area_puts(ge->map, str);
            if (space_get_east(space_act) == NULL && space_get_west(space_act) == NULL)
                sprintf(str, "         | >8D        %2d|", (int)id_act);
            else if (space_get_west(space_act) == NULL && space_get_east(space_act) != NULL)
                sprintf(str, "         | >8D        %2d| --> %s", (int)id_act, link_get_name(space_get_east(space_act)));
            else if (space_get_west(space_act) != NULL && space_get_east(space_act) == NULL)
                sprintf(str, " %s <-- | >8D        %2d|", link_get_name(space_get_west(space_act)), (int)id_act);
            else
                sprintf(str, " %s <-- | >8D        %2d| --> %s", link_get_name(space_get_west(space_act)), (int)id_act, link_get_name(space_get_east(space_act)));
            screen_area_puts(ge->map, str);
            sprintf(str, "         |%s|", space_get_name(space_act));
            screen_area_puts(ge->map, str);
            sprintf(str, "         |    %s   |", space_get_gdesc(space_act, 0));
            screen_area_puts(ge->map, str);
            sprintf(str, "         |    %s   |", space_get_gdesc(space_act, 1));
            screen_area_puts(ge->map, str);
            sprintf(str, "         |    %s   |", space_get_gdesc(space_act, 2));
            screen_area_puts(ge->map, str);
            if (objects != NULL && space_get_illumination(space_act) == TRUE)
            {
                int n = 10 - strlen(objects);
                printf("%*c", n, ' ');
                sprintf(str, "         |%s%*c   |", objects, n, ' ');
                screen_area_puts(ge->map, str);
                free(objects);
            }
            else
            {
                sprintf(str, "         |              |");
                screen_area_puts(ge->map, str);
            }
            sprintf(str, "         +--------------+");
            screen_area_puts(ge->map, str);
        }

        if (id_next != NO_ID)
        {
            sprintf(str, "               v %s", link_get_name(space_get_south(space_act)));
            screen_area_puts(ge->map, str);
            sprintf(str, "         +--------------+");
            screen_area_puts(ge->map, str);
            sprintf(str, "         |            %2d|", (int)id_next);
            screen_area_puts(ge->map, str);
            sprintf(str, "         |%s|", space_get_name(game_get_space(game, id_next)));
            screen_area_puts(ge->map, str);
            sprintf(str, "         |    %s   |", space_get_gdesc(game_get_space(game, id_next), 0));
            screen_area_puts(ge->map, str);
            sprintf(str, "         |    %s   |", space_get_gdesc(game_get_space(game, id_next), 1));
            screen_area_puts(ge->map, str);
            sprintf(str, "         |    %s   |", space_get_gdesc(game_get_space(game, id_next), 2));
            screen_area_puts(ge->map, str);
        }
    }

    /* Paint in the description area */
    graphic_engine_paint_description_area(ge, game);

    /* Paint in the banner area */
    screen_area_puts(ge->banner, " The game of the Goose ");

    /* Paint in the help area */
    screen_area_clear(ge->help);
    sprintf(str, " The commands you can use are:");
    screen_area_puts(ge->help, str);
    sprintf(str, "     exit or e, take or t, drop or d, roll or rl, move or m, inspect or i, turn on, turn off, save, load");
    screen_area_puts(ge->help, str);

    /* Paint in the feedback area */
    last_cmd = game_get_last_command(game);
    last_rule = game_get_last_rule(game);
    toprint = dialogue_cmd_print(last_cmd, s, game);
    strcat(toprint, dialogue_rule_print(last_rule, game));
    sprintf(str, "%s", toprint);

    screen_area_puts(ge->feedback, str);
    if (game_logfile_exist(game))
        //fprintf(game_get_log_file(game), " %s (%s): %s\n", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], s == OK ? "OK" : "ERROR");
        fprintf(game_get_log_file(game), " %s\n", toprint);


    free(toprint);
    /* Dump to the terminal */
    screen_paint();
    printf("prompt:> ");
}

void graphic_engine_paint_description_area(Graphic_engine *ge, Game *game)
{
    screen_area_clear(ge->descript);
    char str[255] = "";
    if (game_get_number_object(game) != 0)
    {
        screen_area_clear(ge->descript);
        sprintf(str, " Objects location:");
        screen_area_puts(ge->descript, str);
        memset(str, '\0', 255);
        for (int i = 0; i < game_get_number_object(game); i++)
        {
            char pom[30] = "";
            sprintf(pom, " %s:%ld", object_get_name(game_get_object_at_position(game, i)), object_get_location(game_get_object_at_position(game, i)));
            if (i + 1 != game_get_number_object(game))
                strcat(pom, ",");
            strcat(str, pom);
        }
        screen_area_puts(ge->descript, str);
    }

    Id *objectsOfPlayer = inventory_get_elements(player_get_inventory(game_get_player(game)));
    if (objectsOfPlayer != NULL)
    {
        sprintf(str, " ");
        screen_area_puts(ge->descript, str);
        sprintf(str, " Player objects: %s", object_get_name(game_get_object(game, objectsOfPlayer[0])));
        screen_area_puts(ge->descript, str);
        for (int i = 1; i < inventory_get_nObjects(player_get_inventory(game_get_player(game))); i++)
        {
            sprintf(str, "                 %s", object_get_name(game_get_object(game, objectsOfPlayer[i])));
            screen_area_puts(ge->descript, str);
        }
        free(objectsOfPlayer);
    }

    char *space_description = game_get_space_description(game); 

    if (space_description != NULL)
    {
        sprintf(str, " ");
        screen_area_puts(ge->descript, str);
        sprintf(str, " Space description:");
        screen_area_puts(ge->descript, str);
        sprintf(str, " %s", space_description);
        screen_area_puts(ge->descript, str);
    }
    
    char *description = game_get_description(game); 
    
    if (description != NULL)
    {
        sprintf(str, " ");
        screen_area_puts(ge->descript, str);
        sprintf(str, " Descriptions:");
        screen_area_puts(ge->descript, str);
        sprintf(str, " %s", description);
        screen_area_puts(ge->descript, str);
    }

    sprintf(str, " ");
    screen_area_puts(ge->descript, str);
    sprintf(str, " Last die value: %d", dice_get_last_roll(game_get_dice(game)));
    screen_area_puts(ge->descript, str);
}