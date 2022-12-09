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
#include <stdio.h>

#include "../constants.h"
#include "game.h"

// player items
Player player_local, player_remote;
// core items
int  score_remote, score_local;
bool is_remote;
bool is_play;


// getters
Player get_player_local() { return player_local; }
Player get_player_remote() { return player_remote; }
void   get_scores(int* local, int* remote)
{
    *local  = score_local;
    *remote = score_remote;
}

// ctrl


int update_game(int key_input, WifiMsg remote_info)
{

    // do remote stuff
    if (remote_info.msg == WIFI_PLAYER_X_DIR_ACTION)
        {
            player_remote.dir    = remote_info.dat2;
            player_remote.action = remote_info.dat3;
            inferred_move(&player_remote);
            player_remote.pos_x = translate_remote_x(remote_info.dat1);
        }
    else if (remote_info.msg == WIFI_PLAYER_Y_YS_HP)
        {
            inferred_move(&player_remote);
            player_remote.pos_y   = remote_info.dat1;
            player_remote.y_speed = remote_info.dat2;
            player_remote.health  = remote_info.dat3;
        }
    else
        {
            inferred_move(&player_remote);
        }

    // do local stuff
    if (((key_input & KEY_MOVE_LEFT) ^ (key_input & KEY_MOVE_RIGHT)) &&
        player_local.action != ACTION_TYPE_NORMAL_ATTACK &&
        player_local.action != ACTION_TYPE_SPECIAL_ATTACK)
        {
            move(&player_local,
                 (key_input & KEY_MOVE_LEFT) ? DIRECTION_LEFT : DIRECTION_RIGHT,
                 key_input & KEY_JUMP,
                 (key_input & KEY_BLOCK) ? SPEED / 2
                                         : SPEED); // HALF SPEED FOR BLOCK

            // determine action
            if (player_local.pos_y != SPRITE_FLOOR_HEIGHT)
                {
                    player_local.action = ACTION_TYPE_JUMP_MOVE;
                }

            else if (key_input & KEY_BLOCK)
                {
                    player_local.action = ACTION_TYPE_BLOCK_MOVE;
                }
            else
                {
                    player_local.action = ACTION_TYPE_WALK;
                }
        }
    else // adjust action for when not moving:
        {
            if (player_local.pos_y != SPRITE_FLOOR_HEIGHT)
                {
                    player_local.action = ACTION_TYPE_JUMP_INPLACE;
                }

            else if (key_input & KEY_BLOCK)
                {
                    player_local.action = ACTION_TYPE_BLOCK_INPLACE;
                }
            else
                {
                    player_local.action = ACTION_TYPE_IDLE;
                }
            move(&player_local, player_local.dir, key_input & KEY_JUMP, 0);
        }


    return 0;
}


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
    player_remote.pos_x   = SCREEN_WIDTH - SPRITE_START_POS - SPRITE_WIDTH;
}

void reset_game()
{
    set_stage();
    score_local  = 0;
    score_remote = 0;
    is_remote    = false; // TODO CHANGE based on bt status
    is_play      = true;
}
void new_round()
{
    set_stage();
    is_play = true;
}


#ifdef CONSOLE_DEBUG
void print_players()
{
    printf("Player_local: x:%d, y:%d, h:%d,ys:%d,d:%d\n", player_local.pos_x,
           player_local.pos_y, player_local.health, player_local.y_speed,
           player_local.dir);
    printf("Player_remote: x:%d, y:%d, h:%d,ys:%d,d:%d\n", player_remote.pos_x,
           player_remote.pos_y, player_remote.health, player_remote.y_speed,
           player_remote.dir);
}
void print_game_state()
{
    printf("Score: %d:%d\nPlaying:%d\nRemote:%d\n", score_local, score_remote,
           is_play, is_remote);
    print_players();
}
#endif