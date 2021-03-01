/** 
 * @brief It defines the die interface
 * 
 * @file die.c
 * @author Jiri Zak
 * @version 1.0 
 * @date 1-03-2021 
 * @copyright GNU Public License
 */

#include "die.h"

#include <stdlib.h>
#include <time.h>

struct dice {
    int minimum;
    int maximum;
    int last_roll;
};

BOOL dice_exist(Dice *d) {
    return d == NULL ? FALSE : TRUE;
}

BOOL dice_not_exist(Dice *d) {
    return !dice_exist(d);
}

Dice *dice_create(int minimum, int maximum) {
    Dice *d = malloc(sizeof(struct dice));
    if (d == NULL)
        return NULL;

    d->minimum = minimum;
    d->maximum = maximum;
    d->last_roll = 0;
    srand(time(NULL));
    return d;
}

STATUS dice_destroy(Dice **d) {
    if (dice_not_exist(*d)) {
        return ERROR;
    }

    free(*d);
    *d = NULL;

    return OK;
}

int dice_roll(Dice *d) {
    if (dice_not_exist(d))
        return -1;
    d->last_roll = (rand() % d->maximum) + d->minimum;
    return d->last_roll;
}

int dice_get_last_roll(Dice *d) {
    return dice_exist(d) ? d->last_roll : -1;
}

void dice_print(Dice *d) {
    if (dice_not_exist(d))
        return;
    printf("minimum: %d\nmaximum: %d\n last roll: %d\n", d->minimum, d->maximum, d->last_roll);
}