/**
 * @file game_conrtoller.h
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
 *
 */
void reset_game();


/**
 * @brief Start new round, only resets health and positions. Ideally one should
 * change background when calling this function
 *
 */
void new_round();

#endif // __GAME_CONTROLLER_H
