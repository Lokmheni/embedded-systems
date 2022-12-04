/**
 * @file game.h
 * @author Simon Thür & Lokman Mheni
 * @brief Definition of necessary functions for game mechanics
 * @version 0.1
 * @date 2022-11-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __GAME_H
#define __GAME_H
#include <nds.h>

#include "constants.h"


typedef enum
{
    PLAYER_STATE_IDLE,
    PLAYER_STATE_ATTACK,
    PLAYER_STATE_MOVE_LEFT,
    PLAYER_STATE_MOVE_RIGHT,
    PLAYER_STATE_BLOCK,
    PLAYER_STATE_JUMP,
    PLAYER_STATE_SPECIAL_ATTACK,
} PlayerState;

typedef enum
{
    DIRECTION_LEFT,
    DIRECTION_RIGHT
} Direction;

typedef enum
{
    ACTION_TYPE_IDLE,
    ACTION_TYPE_WALK,
    ACTION_TYPE_JUMP,
    ACTION_TYPE_NORMAL_ATTACK,
    ACTION_TYPE_SPECIAL_ATTACK,
    ACTION_TYPE_BLOCK,
} ActionType;


typedef struct
{
    int        pos_x;
    int        pos_y;
    int        y_speed;
    int        health;
    ActionType action;
    Direction  dir;
} Player;


/**
 * @brief Update the x,y and speed coordinates of Player
 *
 * @param[in,out] plr Player to be updated
 * @param dir Direction in which player should move
 * @param jmp If player is initializing jump (only has effect if player is on
 *            the ground)
 * @param dist distance the player should move (speed of the player)
 */
void move(Player* plr, Direction dir, bool jmp, int dist);


/**
 * @brief Evaluate if player takes damage and subtract the damage from health
 * (based on damage position and player position, takes into account blocking)
 *
 * @note Health of player may drop below 0. This case is to be handled outside
 * this function
 *
 * @param[in,out] plr player subject to damage
 * @param dmg_x x coordinate of damage
 * @param dmg_y y coordinate of damage
 * @param damage amount of damage dealt
 * @return true if player was hit (regadles of the amount of damage)
 * @return false if player was not hit
 */
bool take_damage(Player* plr, int dmg_x, int dmg_y, int damage);


void do_damage(Player* const plr, int* dmg_x, int* dmg_y);

#endif // __GAME_H
