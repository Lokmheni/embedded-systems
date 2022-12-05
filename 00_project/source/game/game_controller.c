/**
 * @file game_controller.c
 * @author Simon Thür
 * @brief
 * @version 0.1
 * @date 2022-12-04
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "game_controller.h"

#include <nds.h>

#include "game.h"
#include "input.h"

// player items
Player player_local, player_remote;
// core items
int  score_remote, score_local;
bool is_remote;
bool is_play;

/**
 * @brief Set the characters (local and remote) to starting positions
 *
 */
void set_stage();


int update_game() { return 0; }


void set_stage()
{ // reset player local and remote
    // common values
    player_local.action   = ACTION_TYPE_IDLE;
    player_remote.action  = ACTION_TYPE_IDLE;
    player_local.health   = MAX_HEALTH;
    player_remote.health  = MAX_HEALTH;
    player_local.y_speed  = 0;
    player_remote.y_speed = 0;
    player_local.pos_y    = SPRITE_FLOOR_HEIGHT;
    player_remote.pos_y   = SPRITE_FLOOR_HEIGHT;
    // specifics local
    player_local.dir      = DIRECTION_RIGHT;
    player_local.pos_x    = SPRITE_START_POS;
    // specifics remote
    player_remote.dir     = DIRECTION_LEFT;
    player_remote.pos_y   = SCREEN_WIDTH - SPRITE_START_POS - SPRITE_WIDTH;
}

void reset_game()
{
    set_stage();
    score_local  = 0;
    score_remote = 0;
}
void new_round() { set_stage(); }