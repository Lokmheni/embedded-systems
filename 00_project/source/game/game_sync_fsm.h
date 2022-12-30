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
    GAME_IN_PROGRESS, /*!< Game in progress */
    GAME_IN_SETUP,    /*!< Game in pre game sync */
    GAME_IN_END,      /*!< Game in post game data transfer */
} GameState;


/// @brief Get the game state object
/// @return GameState
GameState get_game_state();

/// @brief Get the connection state object
/// @return ConnectionHierarchy
ConnectionHierarchy get_connection_state();


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

/**
 * @brief If this device is master/or singleplayer, initialize game
 *
 * @return true on success
 * @return false on failure
 */
bool go_for_game_init();

/**
 * @brief When local has lost (becomes master) init new round
 *
 * This implies, local has LOST previous round!
 *
 * @return true if new round initiated
 * @return false on error
 */
bool go_for_new_round();

/**
 * @brief Listen to and execute commands (slave mode)
 *
 * @param req potential command
 */
void execute_commands(WifiMsg req);


#endif // __GAME_SYNC_FSM
