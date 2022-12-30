/**
 * @file game_sync_fsm.c
 * @author Simon Thür
 * @brief FSM for wifi synchronization
 * @version 0.1
 * @date 2022-12-30
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "game_sync_fsm.h"

#include "../constants.h"
#include "game_controller.h"

//===================================================================
// Variables
//===================================================================
/// @brief Connection state
ConnectionHierarchy con_state = CONNECTION_TYPE_NULL;
/// @brief game state
GameState game_state          = GAME_IN_END;


//===================================================================
// Getters
//===================================================================
GameState           get_game_state() { return game_state; }
ConnectionHierarchy get_connection_state() { return con_state; }


//===================================================================
// FSM logic
//===================================================================
bool exec_sync_fsm(RequestedAction a, RequestedMovement m, WifiMsg msg,
                   bool timeout)
{
    // default assignment
    bool round_done = false;

    /// @todo if not connected, emulate WifiMsg

    /// @todo start game (i.e. go for game init)

    // obvious stuff thats always needed
    execute_commands(msg);

    // actual game
    if (game_state == GAME_IN_PROGRESS)
        {

            update_game_complete(a, m, msg);
            // check player death (lazy evaluation) || timeout loss
            if ((remote_attack_handler(msg) &&
                 get_player_local().health > MAX_HEALTH) ||
                (timeout &&
                 get_player_local().health < get_player_remote().health))
                {
                    round_done = true;
                    game_state = GAME_IN_ROUND_END;
                    con_state  = con_state == CONNECTION_TYPE_NULL
                                   ? CONNECTION_TYPE_NULL
                                   : CONNECTION_TYPE_MASTER;
                }
        }


    if (con_state != CONNECTION_TYPE_NULL)
        send_local_player();
    return round_done;
}


//===================================================================
// Generalized control
//===================================================================
void go_for_multiplayer()
{
    if (con_state == CONNECTION_TYPE_NULL)
        {
            if (wifi_connect_network())
                {
                    wifi_announce_lfg();
                    con_state = CONNECTION_TYPE_LFG;
                }
        }
}


void go_for_singleplayer()
{
    u8 scr, dontcare;
    get_scores(&scr, &dontcare);
    // inform remote of quit
    send_ctrl_instruction(
        game_state == GAME_IN_PROGRESS ? END_GAME | WINNER_REMOTE : END_GAME,
        scr);
    // turn off wifi
    wifi_disconnect_network();
    // change state
    con_state = CONNECTION_TYPE_NULL;
}

void go_for_game_init()
{
    if (con_state != CONNECTION_TYPE_NULL)
        {
            send_ctrl_instruction(RESET_GAME | IS_PLAY | START_GAME, 0);
            reset_game(true);
            con_state = CONNECTION_TYPE_CONTESTED;
        }
    else
        {
            reset_game(false);
        }

    game_state = GAME_IN_PROGRESS;
}

void go_for_end_round()
{
    u8 scr, dontcare;
    get_scores(&scr, &dontcare);
    send_ctrl_instruction(END_ROUND | WINNER_REMOTE, scr);
    game_state = GAME_IN_ROUND_END;
    con_state  = CONNECTION_TYPE_MASTER;
}

void go_for_new_round()
{
    new_round();
    u8 scr, dontcare;
    get_scores(&scr, &dontcare);
    send_ctrl_instruction(SET_STAGE | IS_PLAY, scr);
    game_state = GAME_IN_PROGRESS;
}


void execute_commands(WifiMsg req)
{
    // does it make sense to do stuff?
    if (con_state == CONNECTION_TYPE_NULL)
        return;
    // Am I searching for game?
    if (con_state == CONNECTION_TYPE_LFG)
        {
            if (req.msg == WIFI_REQ_LFG)
                {
                    con_state  = CONNECTION_TYPE_MASTER;
                    game_state = GAME_IN_SETUP;
                }
            else if (req.msg == WIFI_SYNC_INSTR_SCORE)
                {
                    con_state  = CONNECTION_TYPE_SLAVE;
                    game_state = GAME_IN_SETUP;
                }
        }

    // connection state possibly changed before ^
    if (con_state == CONNECTION_TYPE_SLAVE && req.msg == WIFI_SYNC_INSTR_SCORE)
        {
            // lowlevel
            if (req.dat1 & RESET_GAME)
                reset_game(true);
            if (req.dat1 & SET_STAGE)
                set_stage();
            if (req.dat1 & WINNER_REMOTE)
                inc_score_lcoal();

            // statelevel
            // playpause
            if (req.dat1 & IS_PLAY)
                game_state = GAME_IN_PROGRESS;
            else if (game_state == GAME_IN_PROGRESS)
                game_state = GAME_IN_PAUSE;
            // eor
            if (req.dat1 & END_ROUND) // override is_play
                game_state = GAME_IN_ROUND_END;
            // quit
            if (req.dat1 & END_GAME)
                {
                    wifi_disconnect_network();
                    con_state = CONNECTION_TYPE_NULL;
                }
        }
}
