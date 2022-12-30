/**
 * @file game_controller.h
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 1.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __GAME_CONTROLLER_H
#define __GAME_CONTROLLER_H
#include <nds.h>

#include "../io/input.h"
#include "../io/wifi.h"
#include "game.h"

//===================================================================
// Get values
//===================================================================
/**
 * @brief Get the player local object
 *
 * @return Player
 */
Player get_player_local();
/**
 * @brief Get the player remote object
 *
 * @return Player
 */
Player get_player_remote();
/**
 * @brief Get the scores of the game
 *
 * @param[out] score_local
 * @param[out] score_remote
 */
void get_scores(u8* local, u8* remote);

/**
 * @brief Set the remote scores object
 *
 * @param remote score of remote
 */
void set_score_remote(u8 remote);

/**
 * @brief Increment local score by 1
 *
 */
void inc_score_lcoal();


//===================================================================
// Control
//===================================================================
/**
 * @brief Set the characters (local and remote) to starting positions
 *
 */
void set_stage();


/**
 * @brief Calculate next step of the game based on player input and remote
 * message.
 *
 * @note This function only updates movements! It does not care about damage.
 * Damage and health should be handled separately elsewhere
 *
 * @param action Action that the player wishes to execute
 * @param movement that the player wishes to do.
 * @param remote_info Messages concerning what remote is doing
 */
void update_game(RequestedAction action, RequestedMovement movement,
                 WifiMsg remote_info);


/**
 * @brief Execute an attack. return attack characteristic as WifiMsg format.
 * This action will block player movements for a small delay (uses timer2 and
 * ISR).
 * @note This functions automatically calls @ref local_attack_handler(u8* dmg_x,
 * u8* dmg_y, u8* dmg) at the correct time (either instantly or after an
 * interrupt delay).
 *
 * @param special If attack is supposed to be special attack
 * @return true if the attack is valid and will be transmitted
 * @return false if the attack is not legal at this time.
 */
bool local_attack(bool special);

/**
 * @brief Sends damage to wifi or handles local singleplayer stuff
 *
 * @param dmg_x coord of dmg
 * @param dmg_y coord of dmg
 * @param dmg amount of dmg
 */
void local_attack_handler(u8 dmg_x, u8 dmg_y, u8 dmg);

/**
 * @brief Do damage to local player (i.e. handle remote attacks)
 *
 * @param dmg_x coord of dmg
 * @param dmg_y coord of dmg
 * @param dmg amount of dmg
 * @return true if player was hit (even if dmg is 0)
 * @return false if player was not hit
 */
bool remote_attack(u8 dmg_x, u8 dmg_y, u8 dmg);

/**
 * @brief This function takes care of remote attacks. If an attack was
 * successful, damage is subtracted from local player.
 *
 * @param remote_attack in the WifiMsg format (attack msg type)
 * @return true if attack hit the player
 * @return false if the attack did not hit.
 */
bool remote_attack_handler(WifiMsg remote_info);


/**
 * @brief Set/Reset the game stage, points health etc.
 *
 * @param remote whether game is remote.
 */
void reset_game(bool remote);

/**
 * @brief Start new round, only resets health and positions. Ideally one should
 * change background when calling this function
 *
 */
void new_round();


//===================================================================
// Helper
//===================================================================
/**
 * @brief Calculate hit position based on local player position
 *
 * @param[out] x position of where dmg would be done at this instant
 * @param[out] y position of where dmg would be done at this instant
 */
void where_is_my_hit(u8* x, u8* y);

// DEBUG
#ifdef CONSOLE_DEBUG
// uses printf!
void print_players();
// uses printf!
void print_game_state();
#endif

#endif // __GAME_CONTROLLER_H
