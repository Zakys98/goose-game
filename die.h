/** 
 * @brief It defines the die interface
 * 
 * @file die.h
 * @author Jiri Zak
 * @version 1.0 
 * @date 1-03-2021 
 * @copyright GNU Public License
 */

#ifndef DIE_H
#define DIE_H

#include "types.h"

typedef struct dice Dice;

/**
 * @brief Dice create and set last roll to 0
 *
 * @author Jiri Zak
 * @date 1-03-2021
 * 
 * @param minimum minimum of the range
 * @param maximum maximum of the range
 * @return pointer to Dice or NULL if error
 */
Dice* dice_create(int, int);

/**
 * @brief Dice destroy and set it to NULL
 *
 * @author Jiri Zak
 * @date 1-03-2021
 * 
 * @param d double pointer to Dice
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS dice_destroy(Dice **);

/**
 * @brief Generate random number from dice range and save it to the structure
 *
 * @author Jiri Zak
 * @date 1-03-2021
 * 
 * @param d pointer to Dice
 * @return generated number or -1 if error
 */
int dice_roll(Dice *);

/**
 * @brief Dice last roll getter 
 *
 * @author Jiri Zak
 * @date 1-03-2021
 * 
 * @param d pointer to Dice
 * @return int or -1 if ERROR
 */
int dice_get_last_roll(Dice *);

/**
 * @brief Dice print
 *
 * @author Jiri Zak
 * @date 1-03-2021
 * 
 * @param d pointer to Dice
 */
void dice_print(Dice *);

#endif