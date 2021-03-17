#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "screen.h"

struct _Graphic_engine {
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

Graphic_engine *graphic_engine_create() {
    static Graphic_engine *ge = NULL;

    if (ge)
        return ge;

    screen_init();
    ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
    if (ge == NULL)
        return NULL;

    ge->map = screen_area_init(1, 1, 48, 13);
    ge->descript = screen_area_init(50, 1, 29, 13);
    ge->banner = screen_area_init(28, 15, 23, 1);
    ge->help = screen_area_init(1, 16, 78, 2);
    ge->feedback = screen_area_init(1, 20, 78, 2);

    return ge;
}

void graphic_engine_destroy(Graphic_engine *ge) {
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

char *graphic_engine_get_space_objects(Game *g, Space *s) {
    if (space_objects_count(s) == 0)
        return NULL;

    Id *obj_ids = space_get_objects(s);
    char *res = (char *)malloc(20);
    char *object_names = res;
    Object *obj = game_get_object(g, obj_ids[0]);

    object_names += sprintf(object_names, "%s", object_get_name(obj));

    for (int i = 1; i < space_objects_count(s); i++) {
        obj = game_get_object(g, obj_ids[i]);
        object_names += sprintf(object_names, ", %s", object_get_name(obj));
    }
    free(obj_ids);
    return res;
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game, STATUS s) {
    Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID;
    Space *space_act = NULL;
    char str[255];
    T_Command last_cmd = UNKNOWN;
    extern char *cmd_to_str[N_CMD][N_CMDT];
    char *objects = NULL;

    /* Paint the in the map area */
    screen_area_clear(ge->map);
    if ((id_act = game_get_player_location(game)) != NO_ID) {
        space_act = game_get_space(game, id_act);
        id_back = space_get_north(space_act);
        id_next = space_get_south(space_act);
        objects = graphic_engine_get_space_objects(game, space_act);

        if (id_back != NO_ID) {
            sprintf(str, "  |         %2d|", (int)id_back);
            screen_area_puts(ge->map, str);
            //gen obj
            sprintf(str, "  +-----------+");
            screen_area_puts(ge->map, str);
            sprintf(str, "        ^");
            screen_area_puts(ge->map, str);
        }

        if (id_act != NO_ID) {
            sprintf(str, "  +-----------+");
            screen_area_puts(ge->map, str);
            sprintf(str, "  | 8D      %2d|", (int)id_act);
            screen_area_puts(ge->map, str);
            sprintf(str, "  | %s   |", space_get_gdesc(space_act, 0));
            screen_area_puts(ge->map, str);
            sprintf(str, "  | %s   |", space_get_gdesc(space_act, 1));
            screen_area_puts(ge->map, str);
            sprintf(str, "  | %s   |", space_get_gdesc(space_act, 2));
            screen_area_puts(ge->map, str);
            if (objects != NULL) {
                int n = 10 - strlen(objects);
                printf("%*c", n, ' ');
                sprintf(str, "  | %s%*c|", objects, n, ' ');
                screen_area_puts(ge->map, str);
                free(objects);
            }
            sprintf(str, "  +-----------+");
            screen_area_puts(ge->map, str);
        }

        if (id_next != NO_ID) {
            sprintf(str, "        v");
            screen_area_puts(ge->map, str);
            sprintf(str, "  +-----------+");
            screen_area_puts(ge->map, str);
            sprintf(str, "  |         %2d|", (int)id_next);
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
    sprintf(str, "     next or n, back or b, exit or e, take or t, drop or d, roll or r1, left or l, right or r");
    screen_area_puts(ge->help, str);

    /* Paint in the feedback area */
    last_cmd = game_get_last_command(game);
    sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], s == OK ? "OK" : "ERROR");
    screen_area_puts(ge->feedback, str);
    if(game_logfile_exist(game))
        fprintf(game->log, " %s (%s): %s\n", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], s == OK ? "OK" : "ERROR");

    /* Dump to the terminal */
    screen_paint();
    printf("prompt:> ");
}

void graphic_engine_paint_description_area(Graphic_engine *ge, Game *game) {
    screen_area_clear(ge->descript);
    char str[255] = "";
    if (game_get_number_object(game) != 0) {
        screen_area_clear(ge->descript);
        sprintf(str, " Objects location:");
        screen_area_puts(ge->descript, str);
        memset(str, '\0', 255);
        for (int i = 0; i < game_get_number_object(game); i++) {
            char pom[30] = "";
            sprintf(pom, " %s:%ld", object_get_name(game->objects[i]), object_get_location(game->objects[i]));
            if (i + 1 != game_get_number_object(game))
                strcat(pom, ",");
            strcat(str, pom);
        }
        screen_area_puts(ge->descript, str);
    }

    if (object_get_name(game->player->obj) != NULL) {
        sprintf(str, " ");
        screen_area_puts(ge->descript, str);
        sprintf(str, " Player object: %s:%ld", object_get_name(game->player->obj), object_get_location(game->player->obj));
        screen_area_puts(ge->descript, str);
    }

    sprintf(str, " ");
    screen_area_puts(ge->descript, str);
    sprintf(str, " Last die value: %d", dice_get_last_roll(game->dice));
    screen_area_puts(ge->descript, str);
}