/**
 * @file memory.h
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __MEMORY_H
#define __MEMORY_H


#include <nds.h>


/**
 * @brief Store values to permanent memory
 *
 * @param nbr_games total number of games played
 * @param nbr_won total number of games won
 * @return true on success
 * @return false writing failed
 */
bool store_stats(int nbr_games, int nbr_won);


/**
 * @brief Get the stored game statistics from permanent memory
 *
 * @param nbr_games total number of games played
 * @param nbr_won total number of games won
 * @return true if values were read correctly
 * @return false if something failed
 */
bool get_stats(int* nbr_games, int* nbr_won);


#endif // __MEMORY_H
