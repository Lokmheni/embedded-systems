/**
 * @file game_controller.h
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __GAME_CONTROLLER_H
#define __GAME_CONTROLLER_H
#include <nds.h>


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
 * @param[in,out] score_local
 * @param[in,out] score_remote
 */
void get_scores(int* local, int* remote);


//===================================================================
// Control
//===================================================================
/**
 * @brief Set the characters (local and remote) to starting positions
 *
 */
void set_stage();


/**
 * @brief Execute next step of the game (for now, we assume that it also takes
 * care of bluetooth transmission)
 *
 * @return int where 0 means the game continues
 *                   1 means player_local has won round
 *                   2 means player_remote has won round
 *                   3 means the connection died
 */
int update_game();

/**
 * @brief Set/Reset the game stage, points health etc.
 * (also starts game already)
 *
 */
void reset_game();


/**
 * @brief Start new round, only resets health and positions. Ideally one should
 * change background when calling this function
 *
 */
void new_round();


// DEBUG
#ifdef CONSOLE_DEBUG
// uses printf!
void print_players();
// uses printf!
void print_game_state();
#endif

#endif // __GAME_CONTROLLER_H
