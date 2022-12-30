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
    send_ctrl_instruction(RESET_GAME | IS_PLAY | START_GAME, 0);
    reset_game();
    game_state = GAME_IN_PROGRESS;
    con_state  = CONNECTION_TYPE_CONTESTED;
}


void go_for_new_round()
{
    new_round();
    u8 scr, dontcare;
    get_scores(scr, dontcare);
    send_ctrl_instruction(SET_STAGE | IS_PLAY, scr);
}


void execute_commands(WifiMsg req) {}
