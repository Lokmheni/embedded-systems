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


// IRQ
void isr_attack()
{
    // DISABLE IRQ:
    irqDisable(IRQ_TIMER2);
    // DISABLE TIMER:
    TIMER2_CR &= ~TIMER_ENABLE;
    // maybe send data?
    if (player_local.action == ACTION_TYPE_SPECIAL_ATTACK)
        {
            u8 x, y;
            where_is_my_hit(&x, &y);
            // transmitting data... is this smart? Assistant says its probably
            // fine, @TODO test and see if it works...
            local_attack_handler(x, y, DAMAGE_SPECIAL);
        }
    // unblock player:
    player_local.action = ACTION_TYPE_IDLE;
}

// getters
Player get_player_local() { return player_local; }
Player get_player_remote() { return player_remote; }
void   get_scores(int* local, int* remote)
{
    *local  = score_local;
    *remote = score_remote;
}

// ctrl


void update_game(RequestedAction action, RequestedMovement movement,
                 WifiMsg remote_info)
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

    // check if attacking
    if (player_local.action == ACTION_TYPE_NORMAL_ATTACK &&
        player_local.action == ACTION_TYPE_SPECIAL_ATTACK)
        {
            // no movements when attacking, potentially do other stuff

            // move(&player_local,
            //      (key_input & KEY_MOVE_LEFT) ? DIRECTION_LEFT :
            //      DIRECTION_RIGHT, false, 0);
        }
    else
        {
            // do local stuff movements
            if (movement != REQ_MOVE_NONE)
                {
                    move(&player_local,
                         movement == REQ_MOVE_LEFT ? DIRECTION_LEFT
                                                   : DIRECTION_RIGHT,
                         action == REQ_ACTION_JUMP,
                         (action == REQ_ACTION_BLOCK) ? SPEED_BLOCKING : SPEED);

                    // determine action
                    if (player_local.pos_y != SPRITE_FLOOR_HEIGHT)
                        {
                            player_local.action = ACTION_TYPE_JUMP_MOVE;
                        }

                    else if (action == REQ_ACTION_BLOCK)
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

                    else if (action == REQ_ACTION_BLOCK)
                        {
                            player_local.action = ACTION_TYPE_BLOCK_INPLACE;
                        }
                    else
                        {
                            player_local.action = ACTION_TYPE_IDLE;
                        }
                    move(&player_local, player_local.dir,
                         action == REQ_ACTION_JUMP, 0);
                }
        }
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


bool local_attack(bool special)
{
    if (player_local.action == ACTION_TYPE_NORMAL_ATTACK ||
        player_local.action == ACTION_TYPE_SPECIAL_ATTACK)
        {
            return false;
        }
    player_local.action =
        special ? ACTION_TYPE_SPECIAL_ATTACK : ACTION_TYPE_NORMAL_ATTACK;

    if (!special)
        {
            u8 x, y;
            where_is_my_hit(&x, &y);
            local_attack_handler(x, y, DAMAGE_NORMAL);
        }
    // IRQ
    irqSet(IRQ_TIMER2, isr_attack);
    irqEnable(IRQ_TIMER2);
    // timer
    TIMER2_DATA = special ? TIMER_FREQ_256(SPECIAL_ATK_CHARGEUP_FREQ)
                          : TIMER_FREQ_256(ATTACK_DELAY_FREQ);
    TIMER2_CR   = TIMER_ENABLE | TIMER_DIV_256 | TIMER_IRQ_REQ;
    return true;
}


void local_attack_handler(u8 dmg_x, u8 dmg_y, u8 dmg)
{
    // todo mediate between single player and multiplayer
    send_damage(dmg_x, dmg_y, dmg);
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


void where_is_my_hit(u8* x, u8* y)
{
    *x = player_local.pos_x +
         (player_local.dir == DIRECTION_LEFT ? 0 : SPRITE_WIDTH);
    *y = player_local.pos_y + SPRITE_HEIGHT / 2;
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