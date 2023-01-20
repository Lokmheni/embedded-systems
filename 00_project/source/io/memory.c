/**
 * @file memory.c
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */

int games_played, games_won;

#include "memory.h"


void store_stats(int nbr_games, int nbr_won) {
}

void get_stats(int* nbr_games, int* nbr_won) {
	*nbr_games  = games_played;
	*nbr_won = games_won;
}
