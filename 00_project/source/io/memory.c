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


#include "memory.h"

#include <dirent.h>
#include <fat.h>
#include <stdio.h>
#include <string.h>
#include <sys/dir.h>


const char* const file_name_games_won    = "/streetfighter_gb.txt";
const char* const file_name_games_played = "/streetfighter_gw.txt";


const char* const file_name = "/streetfighter/scores.txt";


bool store_stats(int nbr_games, int nbr_won)
{
    FILE* file = fopen(file_name_games_played, "w+");
    if (file == NULL)
        return false;
    fprintf(file, "%i\n", nbr_games);
    fclose(file);

    file = fopen(file_name_games_won, "w+");
    if (file == NULL)
        return false;
    fprintf(file, "%i\n", nbr_won);
    fclose(file);

    return true;
}

bool get_stats(int* nbr_games, int* nbr_won)
{
    FILE* file = fopen(file_name_games_played, "r");
    if (file == NULL)
        return false;
    fscanf(file, "%i\n", nbr_games);
    fclose(file);

    file = fopen(file_name_games_won, "r");
    if (file == NULL)
        return false;
    fscanf(file, "%i\n", nbr_won);
    fclose(file);


    return true;
}
