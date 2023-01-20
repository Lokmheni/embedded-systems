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


void store_stats(u8 nbr_games, u8 nbr_won);

void get_stats(u8* nbr_games, u8* nbr_won);


#endif // __MEMORY_H
