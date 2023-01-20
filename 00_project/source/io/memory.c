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

u8 games_played, games_won;

FILE* file = NULL;
DIR*  dir  = NULL;

struct dirent* entry;
struct stat    st;


const char* const target_dir = "/streetfighter/";

void store_stats(u8 nbr_games, u8 nbr_won)
{

    if ((entry = readdir(dir)) == NULL)
        {
            // Close and reopen the directory
            closedir(dir);
            dir   = opendir(target_dir);
            entry = readdir(dir);
        }
}

void get_stats(u8* nbr_games, u8* nbr_won)
{
    *nbr_games = games_played;
    *nbr_won   = games_won;
}
