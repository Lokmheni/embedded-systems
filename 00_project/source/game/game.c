/**
 * @file game.c
 * @author Simon Thür & Lokman Mheni
 * @brief Implementation of game mechanics
 * @version 1.0
 * @date 2022-11-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "game.h"

#include "../constants.h"
#include "../io/sound.h"

void move(Player* plr, Direction dir, bool jmp, int dist)
{
    // update direction
    plr->dir   = dir;
    // update position x
    u8 old_pos = plr->pos_x;
    plr->pos_x += dir == DIRECTION_RIGHT ? dist : -dist;
    if (plr->pos_x > old_pos && dir == DIRECTION_LEFT) // check underflow
        {
            plr->pos_x = 0;
        }
    else if (plr->pos_x > SCREEN_WIDTH - SPRITE_WIDTH)
        {
            plr->pos_x = SCREEN_WIDTH - SPRITE_WIDTH;
        }
    // update position y
    if (plr->pos_y < SPRITE_FLOOR_HEIGHT) // check if already jumping
        {
            plr->pos_y -= plr->y_speed;
            plr->y_speed -= GRAVITY;
            if (plr->pos_y > SPRITE_FLOOR_HEIGHT)
                {
                    plr->pos_y   = SPRITE_FLOOR_HEIGHT;
                    plr->y_speed = 0;
                }
        }
    else if (jmp)
        {
            plr->y_speed = JUMP_SPEED - GRAVITY;
            plr->pos_y   = SPRITE_FLOOR_HEIGHT - JUMP_SPEED;
        }
}


bool take_damage(Player* plr, int dmg_x, int dmg_y, int damage)
{
    bool hit = true;
    // test x
    if (plr->pos_x > dmg_x || (plr->pos_x + SPRITE_WIDTH) < dmg_x)
        hit = false;
    // test y
    else if (plr->pos_y > dmg_y || (plr->pos_y + SPRITE_HEIGHT) < dmg_y)
        hit = false;

    // reduce damage if blocked
    else if (plr->action == ACTION_TYPE_BLOCK_MOVE ||
             plr->action == ACTION_TYPE_BLOCK_INPLACE)
        {
            plr->health -= damage / BLOCK_FACTOR;
        }
    else
        plr->health -= damage;


    // sound effects
    if (damage)
        {
            if (hit)
                play_sound_effect(SOUND_EFFECT_BLOCK);
            else
                play_sound_effect(SOUND_EFFECT_ATTACK);
        }
    return hit;
}


void do_damage(const Player* plr, u8* dmg_x, u8* dmg_y)
{
    *dmg_x = plr->pos_x + (plr->dir == DIRECTION_LEFT ? 0 : SPRITE_WIDTH);
    *dmg_y = plr->pos_y + SPRITE_HEIGHT / 2;
}


u8 translate_remote_x_sprite(u8 x_coord)
{
    return SCREEN_WIDTH - SPRITE_WIDTH - x_coord;
}
u8 translate_remote_x_point(u8 x_coord) { return SCREEN_WIDTH - x_coord; }


void inferred_move(Player* plr)
{
    if (plr->action != ACTION_TYPE_NORMAL_ATTACK &&
        plr->action != ACTION_TYPE_SPECIAL_ATTACK)
        {
            move(plr, plr->dir,
                 plr->action == ACTION_TYPE_JUMP_INPLACE || // if jump then jump
                     plr->action == ACTION_TYPE_JUMP_MOVE,
                 plr->action == ACTION_TYPE_JUMP_MOVE ||
                         plr->action == ACTION_TYPE_WALK
                     ? SPEED // if moving then move, speed
                 : plr->action == ACTION_TYPE_BLOCK_MOVE
                     ? SPEED_BLOCKING // if blockin speed block, else 0
                     : 0);
        }
}
