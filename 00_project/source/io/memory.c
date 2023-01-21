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


FILE* file = NULL;
DIR*  dir  = NULL;


const char* const file_name = "/streetfighter/scores.txt";

bool store_stats(int nbr_games, int nbr_won)
{
    file = fopen(file_name, "w+");
    if (file != NULL)
        {
            fprintf(file, "%i\n%i\n", nbr_won, nbr_games);
            fclose(file);
            return true;
        }
    return false;
}

bool get_stats(int* nbr_games, int* nbr_won)
{
    file = fopen(file_name, "r");
    if (file != NULL)
        {
            fclose(file);
            return true;
        }
    return false;
}
