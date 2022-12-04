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


void move(Player* plr, Direction dir, bool jmp, int dist);


bool take_damage(Player* plr, int dmg_x, int dmg_y, int damage);


void do_damage(Player* const plr, int* dmg_x, int* dmg_y);

#endif // __GAME_H
