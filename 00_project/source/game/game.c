/**
 * @file game.c
 * @author Simon Thür & Lokman Mheni
 * @brief Implementation of game mechanics
 * @version 0.1
 * @date 2022-11-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "game.h"

#include "../constants.h"

void move(Player* plr, Direction dir, bool jmp, int dist)
{
    // update direction
    plr->dir = dir;
    // update position x
    plr->pos_x += dist;
    if (plr->pos_x < 0)
        plr->pos_x = 0;
    else if (plr->pos_x > SCREEN_WIDTH - SPRITE_WIDTH)
        {
            plr->pos_x = SCREEN_WIDTH - SPRITE_WIDTH;
        }
    // update position y
    if (plr->pos_y > SPRITE_FLOOR_HEIGHT) // check if already jumping
        {
            plr->pos_y += plr->y_speed;
            plr->y_speed -= GRAVITY;
            if (plr->pos_y < SPRITE_FLOOR_HEIGHT)
                {
                    plr->pos_y   = SPRITE_FLOOR_HEIGHT;
                    plr->y_speed = 0;
                }
        }
    else if (jmp)
        {
            plr->y_speed = JUMP_SPEED - GRAVITY;
            plr->pos_y   = SPRITE_FLOOR_HEIGHT + JUMP_SPEED;
        }
}


bool take_damage(Player* plr, int dmg_x, int dmg_y, int damage)
{
    // test x
    if (plr->pos_x > dmg_x || (plr->pos_y - SPRITE_WIDTH) < dmg_x)
        return false;
    // test y
    if (plr->pos_y < dmg_y || plr->pos_y + SPRITE_HEIGHT > dmg_y)
        return false;

    // reduce damage if blocked
    if (plr->action == ACTION_TYPE_BLOCK_MOVE ||
        plr->action == ACTION_TYPE_BLOCK_INPLACE)
        {
            plr->health -= damage / BLOCK_FACTOR;
            // #TODO maybe add that only half of sprite is blocked by block
            // damage (e.g. a shield)
        }
    else
        plr->health -= damage;

    return true;
}


void do_damage(Player* const plr, int* dmg_x, int* dmg_y)
{
    *dmg_x = plr->pos_x + (plr->dir == DIRECTION_LEFT ? 0 : SPRITE_WIDTH);
    *dmg_y = plr->pos_y - SPRITE_HEIGHT / 2;
}
