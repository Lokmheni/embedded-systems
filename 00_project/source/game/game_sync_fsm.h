/**
 * @file game_sync_fsm.h
 * @author Simon Thür
 * @brief FSM for wifi synchronization
 * @version 0.1
 * @date 2022-12-30
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __GAME_SYNC_FSM
#define __GAME_SYNC_FSM


#include <nds.h>

#include "../io/wifi.h"
#include "../settings.h"


typedef enum ConnectionHierarchy
{
    CONNECTION_TYPE_NULL,      /*!< Not connected to wifi */
    CONNECTION_TYPE_LFG,       /*!< Wait for other NDS */
    CONNECTION_TYPE_MASTER,    /*!< Local is master */
    CONNECTION_TYPE_SLAVE,     /*!< Local is slave */
    CONNECTION_TYPE_CONTESTED, /*!< Connected, no master/salve relationship */
} ConnectionHierarchy;


typedef enum GameState
{
    GAME_IN_PROGRESS,    /*!< Game in progress */
    GAME_IN_PAUSE,       /*!< Game paused/not started yet */
    GAME_IN_SETUP,       /*!< Game in pre game sync */
    GAME_IN_ROUND_SETUP, /*!< Game in pre ROUND sync */
    GAME_IN_ROUND_END,   /*!< Game in post ROUND data transfer */
    GAME_IN_END,         /*!< Game in post game data transfer */
} GameState;


//===================================================================
// Getters (Ok for external use)
//===================================================================
/// @brief Get the game state object
/// @return GameState
GameState get_game_state();

/// @brief Get the connection state object
/// @return ConnectionHierarchy
ConnectionHierarchy get_connection_state();


//===================================================================
// FSM logic (Ok for external use)
//===================================================================
/**
 * @brief Master function for game FSM (call once per frame!)
 *
 * This function takes care of all back-end related tasks concerning wifi, game
 * mechanics, game synchromization and game progression.
 *
 * @note To change between single-player and multiplayer, directly call @ref
 * go_for_multiplayer() or @ref go_for_singleplayer().
 *
 * @param a Action the player wishes to execute
 * @param m movement the player wishes to execute
 * @param msg wifi message received from remote (unfiltered!)
 * @param timeout if this round is out of time
 *
 * @return true if round/game has just finished!
 */
bool exec_sync_fsm(RequestedAction a, RequestedMovement m, WifiMsg msg,
                   bool timeout);


//===================================================================
// Generalized control (Ok for external use)
//===================================================================
/**
 * @brief Change mode of operation to multiplayer
 *
 */
void go_for_multiplayer();

/**
 * @brief Change mode of operation to singleplayer
 *
 * (Forfeit game, exit, and disconnect wifi)
 *
 */
void go_for_singleplayer();


//===================================================================
// Sync control (Intended for internal use only, external use discouraged)
//===================================================================
/**
 * @brief If this device is master/or single-player, initialize game
 */
void go_for_game_init();

/**
 * @brief Call to pause game and end round.
 *
 * This function is to be used iif when local has LOST!.
 *
 */
void go_for_end_round();

/**
 * @brief When local has lost (becomes master) init new round.
 *
 * @ref go_for_end_round() should be called when losing round, then this
 * function should be called to being new round!
 */
void go_for_new_round();

/**
 * @brief Listen to and execute commands (slave mode)
 *
 * This function does NOT initiate any master commands (i.e. if an LFG is
 * received, it will change the local state, but will not initiate any
 * communication)
 *
 * @param req potential command
 */
void execute_commands(WifiMsg req);


#endif // __GAME_SYNC_FSM
