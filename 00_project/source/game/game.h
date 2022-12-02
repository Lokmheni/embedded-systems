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


#define SPEED   5 // number of pixels to move per game iteration
#define GRAVITY 10


#define DAMAGE_NORMAL  5
#define DAMAGE_SPECIAL 10
#define MAX_HEALTH     100

typdef enum {
    IDLE,
    ATTACK,
    MOVE_LEFT,
    MOVE_RIGHT,
    BLOCK,
    JUMP,
    SPECIAL_ATTACK,
} PlayerState;

typedef enum
{
    LEFT,
    RIGHT
} Direction;

typedef enum
{
    IDLE,
    WALK,
    JUMP,
    NORMAL_ATTACK,
    SPECIAL_ATTACK,
    BLOCK,
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


void move(Player* plr, Direction dir, bool jmp = false, int dist = SPEED);


bool take_damage(Player* plr, int dmg_x, int dmg_y, int damage);


void do_damage(Player* const plr, int* dmg_x, int* dmg_y);

#endif // __GAME_H
