/**
 * @file game_controller.c
 * @author Simon Thür
 * @brief
 * @version 1.1
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
u8   score_remote, score_local;
bool is_remote;  /*<! true if remote is wifi person */
bool is_play;    /*<! @deprecated handled outside of this scope*/
bool bot_attack; /*<! true if bot attack cooldown active */


// IRQ

/// @brief Local execute delayed attack isr
void isr_attack()
{
    // printf("ISR CALLED\n");
    // DISABLE IRQ:
    irqDisable(IRQ_TIMER2);
    // DISABLE TIMER:
    TIMER2_CR &= ~TIMER_ENABLE;
    // maybe send data?
    if (player_local.action == ACTION_TYPE_SPECIAL_ATTACK)
        {
            u8 x, y;
            where_is_my_hit(&x, &y);
            local_attack_handler(x, y, DAMAGE_SPECIAL);
        }
    // unblock player:
    player_local.action = ACTION_TYPE_IDLE;
}

/// @brief Attack from local bot on local player isr
void isr_bot_attack()
{
    // DISABLE IRQ AND TIMER
    irqDisable(IRQ_TIMER3);
    TIMER3_CR &= ~TIMER_ENABLE;
    // UNBLOCK BOT
    bot_attack = false;
    // do damage to local
    u8 dx, dy;
    do_damage(&player_remote, &dx, &dy);
    take_damage(&player_local, dx, dy, DAMAGE_SPECIAL);
}


/**
 * @brief Local bot execute attack (init timer and isr)
 *
 */
void remote_bot_attack()
{
    // IRQ
    irqSet(IRQ_TIMER3, isr_bot_attack);
    irqEnable(IRQ_TIMER3);
    // timer
    TIMER3_DATA = TIMER_FREQ_256(SPECIAL_ATK_CHARGEUP_FREQ); // gcc warn ok
    TIMER3_CR   = TIMER_ENABLE | TIMER_DIV_256 | TIMER_IRQ_REQ;

    // block bot
    bot_attack = true;
}

// getters
Player get_player_local() { return player_local; }
Player get_player_remote() { return player_remote; }
void   get_scores(u8* local, u8* remote)
{
    *local  = score_local;
    *remote = score_remote;
}


void set_score_remote(u8 remote) { score_remote = remote; }
void inc_score_lcoal()
{
    score_local = score_local + 1 > score_local
                    ? score_local + 1
                    : score_local; // conditional increment
}


void send_local_player() { send_status(&player_local); }


// ctrl

void update_game_complete(RequestedAction action, RequestedMovement movement,
                          WifiMsg remote_info)
{
    if (action == REQ_ACTION_ATTACK)
        local_attack(false);
    else if (action == REQ_ACTION_SPECIAL_ATTACK)
        local_attack(true);
    update_game_mov(action, movement, remote_info);
}

void update_game_mov(RequestedAction action, RequestedMovement movement,
                     WifiMsg remote_info)
{
    // do remote stuff
    if (remote_info.msg == WIFI_PLAYER_X_DIR_ACTION)
        {
            player_remote.dir =
                remote_info.dat2 == DIRECTION_LEFT
                    ? DIRECTION_RIGHT
                    : DIRECTION_LEFT; // switch direction for remote
            player_remote.action = remote_info.dat3;
            inferred_move(&player_remote);
            player_remote.pos_x = translate_remote_x_sprite(remote_info.dat1);
        }
    else if (remote_info.msg == WIFI_PLAYER_Y_YS_HP)
        {
            inferred_move(&player_remote);
            player_remote.pos_y   = remote_info.dat1;
            player_remote.y_speed = remote_info.dat2;
            player_remote.health  = remote_info.dat3;
        }
    else if (is_remote)
        {
            inferred_move(&player_remote);
        }
    else if (!bot_attack) // Bot logic
        {
            // dmg
            u8 dx, dy;
            do_damage(&player_remote, &dx, &dy);
            // BOT ONLY DOING SPECIAL ATTACKS, ALLOWS FOR EVADING
            if (take_damage(&player_local, dx, dy, 0))
                {
                    remote_bot_attack();
                }
            else
                {
                    // movement:
                    move(&player_remote,
                         player_local.pos_x < player_remote.pos_x
                             ? DIRECTION_LEFT
                             : DIRECTION_RIGHT,
                         player_local.pos_y < player_remote.pos_y, SPEED);
                }
        }

    // check if attacking
    if (player_local.action == ACTION_TYPE_NORMAL_ATTACK ||
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
                    if (player_local.pos_y < SPRITE_FLOOR_HEIGHT)
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
                    if (player_local.pos_y < SPRITE_FLOOR_HEIGHT)
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

    // singlplayer reset
    bot_attack = false;
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
    /// @todo mediate between single player and multiplayer
    send_damage(dmg_x, dmg_y, dmg);
    // printf("Execute attack at %d,%d (%d damage)\n", dmg_x, dmg_y, dmg);
    // printf("plr pos loc:%d,%d\n", player_local.pos_x, player_local.pos_y);
    // printf("plr pos rem:%d,%d\n", player_remote.pos_x, player_remote.pos_y);
    // if (take_damage(&player_remote, dmg_x, dmg_y, dmg))
    //     printf("hit success\n");
}

bool remote_attack(u8 dmg_x, u8 dmg_y, u8 dmg)
{
    return take_damage(&player_local, translate_remote_x_point(dmg_x), dmg_y,
                       dmg);
}


bool remote_attack_handler(WifiMsg remote_info)
{
    // take damage (local)
    if (remote_info.msg == WIFI_DAMAGE_X_Y_DMG)
        {
            return remote_attack(remote_info.dat1, remote_info.dat2,
                                 remote_info.dat3);
        }
    return false;
}

void reset_game(bool remote)
{
    set_stage();
    score_local  = 0;
    score_remote = 0;
    is_remote    = remote;
    is_play      = true;
}
void new_round()
{
    set_stage();
    is_play = true;
}


void where_is_my_hit(u8* x, u8* y) { do_damage(&player_local, x, y); }

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