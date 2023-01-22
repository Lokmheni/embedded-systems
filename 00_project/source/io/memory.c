/**
 * @file memory.c
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 1.0
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "memory.h"

#include <fat.h>
#include <stdio.h>


#define F_GAMES_WON    "/sf_gb.txt"
#define F_GAMES_PLAYED "/sf_gw.txt"


bool store_stats(int nbr_games, int nbr_won)
{
    FILE* file = fopen(F_GAMES_PLAYED, "w+");
    if (file == NULL)
        return false;
    fprintf(file, "%i\n", nbr_games);
    fclose(file);

    file = fopen(F_GAMES_WON, "w+");
    if (file == NULL)
        return false;
    fprintf(file, "%i\n", nbr_won);
    fclose(file);

    return true;
}

bool get_stats(int* nbr_games, int* nbr_won)
{
    FILE* file = fopen(F_GAMES_PLAYED, "r");
    if (file == NULL)
        return false;
    fscanf(file, "%i\n", nbr_games);
    fclose(file);

    file = fopen(F_GAMES_WON, "r");
    if (file == NULL)
        return false;
    fscanf(file, "%i\n", nbr_won);
    fclose(file);


    return true;
}
