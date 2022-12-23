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
 * @return true if player was hit (regardless of the amount of damage)
 * @return false if player was not hit
 */
bool take_damage(Player* plr, int dmg_x, int dmg_y, int damage);


/**
 * @brief Evaluate the position (coordinates) where a player would do damage
 *
 * @param[in,out] plr the relevant player
 * @param[out] dmg_x x coordinate of damage
 * @param[out] dmg_y y coordinate of damage
 */
void do_damage(Player* const plr, u8* dmg_x, u8* dmg_y);


/**
 * @brief Translate remote x_coord to local coordinate system.
 *
 * @note Direction must also be inverted
 *
 * @param x_coord Remote x-coordinate
 * @return u8 x-coordinate in local system
 */
u8 translate_remote_x(u8 x_coord);


/**
 * @brief Update player based on current action, direction, position etc.
 * Executes 1 move.
 *
 * @param[in,out] plr In, player at time t, out player at time t+1
 */
void inferred_move(Player* plr);

#endif // __GAME_H
