/**
 * @file graphics.h
 * @author Simon Thür
 * @brief Header of functions for graphics
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include "../game/game.h"


void init_screens();

void sprite_pos_local(Player* const player);
void init_main_screen();

void init_sub_screen();

void configureSprites();

void show_timer();

//void sprite_pos_local(PlayerState* const player);

//void sprite_pos_remote(PlayerState* const player);

void change_background();

void set_background(int new_background);

void set_time_remaining(int min, int sec, int msec);

// show statistics
void show_settings(int games_played, int games_won);

void manage_timer();

void show_sprites(Player* plr1, Player* plr2);


#endif // __GRAPHICS_H
