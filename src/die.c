/** 
 * @brief It defines the die interface 
 * 
 * @file die.c
 * @author Jiri Zak
 * @version 1.0 
 * @date 1-03-2021 
 * @copyright GNU Public License
 */

#include "../include/die.h"

#include <stdio.h>
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
	if (maximum < minimum) return NULL;
	
    Dice *d = malloc(sizeof(struct dice));
    if (dice_not_exist(d))
        return NULL;

    d->minimum = minimum;
    d->maximum = maximum;
    d->last_roll = -1;
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

STATUS dice_set_last_roll(Dice* d, int roll) {
	if (!dice_exist(d)) return ERROR;

	d->last_roll = roll;
	return OK;
}

void dice_print(Dice *d) {
    if (dice_not_exist(d))
        return;
    printf("minimum: %d\nmaximum: %d\n last roll: %d\n", d->minimum, d->maximum, d->last_roll);
}

STATUS dice_save(FILE* fp, Dice* d) {
	if (d == NULL || fp == NULL) return ERROR;

	fprintf(fp, "#d|%d|%d|%d\n", d->last_roll, d->minimum, d->maximum);
	return OK;
}
