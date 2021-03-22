/** 
 * @brief It defines player interface
 * 
 * @file player.h
 * @author Jiri Zak
 * @version 1.0 
 * @date 12-02-2021 
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "types.h"
#include "inventory.h"

/**
 * Structure for Player
 * Id id
 * char[] name
 * id location 
 * Object *obj
 */
typedef struct player {
    Id id;
    char name[WORD_SIZE + 1];
    Id location;
    Inventory* inventory;
} Player;

/**
 * @brief Player create
 *
 * @author Jiri Zak
 * @date 22-03-2021
 * 
 * @param id id of player
 * @param cap capacity of players backpack (inventory)
 * @return pointer to Player
 */
Player*     player_create(Id, int);

/**
 * @brief Player destroy
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param p double pointer to player
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS      player_destroy(Player **);

/**
 * @brief Check if player is not NULL
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param p pointer to Player
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS      player_exist(Player *);

/**
 * @brief Player id getter 
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param p pointer to Player
 * @return Id or -1 if ERROR
 */
Id          player_get_id(Player *);

/**
 * @brief Player name getter 
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param p pointer to Player
 * @return pointer to const char or NULL if ERROR 
 */
const char* player_get_name(Player *);

/**
 * @brief Player name setter 
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param p pointer to Player
 * @param str pointer to const char
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS      player_set_name(Player *, const char *);

/**
 * @brief Player location setter 
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param p pointer to Player
 * @param id id of location
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS      player_set_location(Player *, Id);

/**
 * @brief PLayer location getter 
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param p pointer to Player
 * @return Id or NO_ID if ERROR 
 */
Id      	player_get_location(Player *);

/**
 * @brief Add object to players inventory
 *
 * @author Jiri Zak
 * @date 12-02-2021
 *
 * @param p pointer to Player 
 * @param o pointer to Object
 * @return STATUS ERROR = 0, OK = 1
 */
STATUS      player_add_object(Player *, Object *);

/**
 * @brief Player object getter 
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param p pointer to Player
 * @return pointer to object or NULL if ERROR 
 */
Object*     player_get_object(Player *, Id);

/**
 * @brief Check if players inventory is full 
 *
 * @author Eva Moresova
 * @date 22-03-2021
 * 
 * @param p pointer to Player
 * @return TRUE if the inventory is full, FALSE otherwise
 */
BOOL player_inventory_full(Player*);

/**
 * @brief Player print
 *
 * @author Jiri Zak
 * @date 12-02-2021
 * 
 * @param p pointer to Player
 */
void        player_print(Player *);

#endif