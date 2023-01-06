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
    /// @attention reverse order implementation is used as priority encoding


    // default assignment
    bool round_done = false;

    /// @todo if not connected, emulate WifiMsg

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
                    go_for_end_round();
                }
            ///@todo end when singleplayer win?
        }


    // initialize game
    if (game_state == GAME_IN_SETUP)
        go_for_game_init();
    // make new round
    if (game_state == GAME_IN_ROUND_SETUP)
        go_for_new_round();

    if (con_state != CONNECTION_TYPE_NULL)
        send_local_player();


    // userdriven (io) state-transitions

    // exit endstates
    if (game_state == GAME_IN_END && a != REQ_ACTION_NONE)
        {
            game_state = GAME_IN_SETUP;
            printf("GAME_IN_SETUP\n");
        }
    if (game_state == GAME_IN_ROUND_END && a != REQ_ACTION_NONE &&
        con_state != CONNECTION_TYPE_SLAVE)
        {
            game_state = GAME_IN_ROUND_SETUP;
            printf("GAME_IN_ROUND_SETUP\n");
        }

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
                    printf("constate CONNECTION_TYPE_LFG\n");
                }
        }
}


void go_for_singleplayer()
{
    if (con_state != CONNECTION_TYPE_NULL)
        {
            /// @todo update BG
            u8 scr, dontcare;
            get_scores(&scr, &dontcare);
            // inform remote of quit
            send_ctrl_instruction(game_state == GAME_IN_PROGRESS
                                      ? END_GAME | WINNER_REMOTE
                                      : END_GAME,
                                  scr, 0);
            // turn off wifi
            wifi_disconnect_network();
            // change state
            con_state = CONNECTION_TYPE_NULL;
            printf("constate CONNECTION_TYPE_NULL\n");
        }
}

void go_for_game_init()
{
    printf("game_init\n");
    if (con_state != CONNECTION_TYPE_NULL)
        {
            /// @todo update BG
            send_ctrl_instruction(RESET_GAME | IS_PLAY | START_GAME, 0, 0);
            reset_game(con_state != CONNECTION_TYPE_NULL);
            con_state = CONNECTION_TYPE_CONTESTED;
            printf("constate CONNECTION_TYPE_CONTESTED\n");
        }
    else
        {
            reset_game(con_state != CONNECTION_TYPE_NULL);
        }

    game_state = GAME_IN_PROGRESS;
    printf("GAME_IN_PROGRESS\n");
}

void go_for_end_round()
{
    printf("end_round\n");

    if (con_state != CONNECTION_TYPE_NULL)
        {
            u8 scr, dontcare;
            get_scores(&scr, &dontcare);
            send_ctrl_instruction(END_ROUND | WINNER_REMOTE, scr, 0);
            con_state = CONNECTION_TYPE_MASTER;
            printf("constate CONNECTION_TYPE_MASTER\n");
        }
    game_state = GAME_IN_ROUND_END;
    printf("GAME_IN_ROUND_END\n");
}

void go_for_new_round()
{
    printf("new_round\n");

    /// @todo change BG and send ctrl changeBG instr
    new_round();
    u8 scr, dontcare;
    get_scores(&scr, &dontcare);
    send_ctrl_instruction(SET_STAGE | IS_PLAY, scr, 0);
    game_state = GAME_IN_PROGRESS;
    printf("GAME_IN_PROGRESS\n");
}


void execute_commands(WifiMsg req)
{
    // does it make sense to do stuff?
    if (con_state == CONNECTION_TYPE_NULL)
        {
            // printf("connection_null!!!\n");
            return;
        }
    // Am I searching for game?
    if (con_state == CONNECTION_TYPE_LFG)
        {
            if (req.msg == WIFI_REQ_LFG)
                {
                    con_state = CONNECTION_TYPE_MASTER;
                    printf("constate:CONNECTION_TYPE_MASTER\n");
                    game_state = GAME_IN_SETUP;
                    printf("GAME_IN_SETUP\n");
                }
            else if (req.msg == WIFI_SYNC_INSTR_SCORE_BG)
                {
                    con_state = CONNECTION_TYPE_SLAVE;
                    printf("constate:CONNECTION_TYPE_SLAVE\n");
                    game_state = GAME_IN_SETUP;
                    printf("GAME_IN_SETUP\n");
                }
        }

    // connection state possibly changed before ^
    if (req.msg == WIFI_SYNC_INSTR_SCORE_BG)
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
                {
                    game_state = GAME_IN_PROGRESS;
                    printf("GAME_IN_PROGRESS\n");
                }
            else if (game_state == GAME_IN_PROGRESS)
                {
                    game_state = GAME_IN_PAUSE;
                    printf("GAME_IN_PAUSE\n");
                }
            // eor
            if (req.dat1 & END_ROUND) // override is_play
                {
                    game_state = GAME_IN_ROUND_END;
                    printf("GAME_IN_ROUND_END\n");
                }
            // quit
            if (req.dat1 & END_GAME)
                {
                    wifi_disconnect_network();
                    con_state = CONNECTION_TYPE_NULL;
                }
        }
}
