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



/**
 * @brief Function called immediately when the nds is turned on.
 * 		  Main and Sub screens are configured to work in rotoscale mode.
 * 		  Respective VRAM memory locations are configured, as well as corresponding main and sub backgrounds.
 * 		  Then it calls the functions @ref show_logo() and @ref init_sub_screen().
 */
void init_screens();

/**
 * @brief The logo of the game is shown by transfering the image and the palette to the corresponding VRAM locations.
 */
void show_logo();

/**
 * @brief An initial image is displayed in the SUB engine.
 * 		  It shows the two different game modes: sigle player or multiplayer
 *
 */
void init_sub_screen();

/**
 * @brief Main screen configured to work in tile mode
 * 		  A landscape is shown in background.
 */
void init_main_screen();

/**
 * @brief A timer showing the passed time of the round is displayed in tiled mode.
 */
void show_timer();

/**
 * @brief The function allows to display and move the sprite which represents the local player.
 */
void sprite_pos_local(const Player* player);

/**
 * @brief The function allows to display and move the sprite which represents the local player.
 */
void sprite_pos_remote(const Player* player);

/**
 * @brief The function computes the remaining time for the end of the game.
 */
int set_time_remaining(int min, int sec, int msec);

// show statistics
void show_settings(int games_played, int games_won);

/**
 * @brief	The timer is configured to have a 1 Hz period.
 * 		  	@ref ISR_TIMER0 is used as interrupt service routine.
 * 		  	Then the ISR is being associated to the timer interrupt line.
 * 		  	The timer interrupt line is enabled.
 * */
void manage_timer();

/**
 * @brief Get the timer timeout object 
 * 
 * @return true if the timer has run out
 * @return false if timer is uninitialaized or still counting
 */
bool get_timer_timeout();

//void change_background();
//void set_background(int new_background);

/**
 * @brief the function displays an image to say that the game is over.
 */
void gameover();

void sprite_initializer();

void updateChrono(const Player* t, const Player* s);

void set_healthbars();

/**
 * @brief the function displays the health bars and receives health as parameter to set the tiles corresponding to decreasing health into transparent
 */
void show_health(const Player* t, const Player* s);

/**
 * @brief the function displays an image to say that the player won.
 */
void youwin();

/**
 * @brief the function displays an image to say that the player lost.
 */
void youlose();



#endif // __GRAPHICS_H
