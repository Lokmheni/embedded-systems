/**
 * @file settings.c
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "settings.h"


PlayMode selected_game_mode(TouchInput* touchinput) {
	if(*touchinput == TOUCH_INPUT_SINGLE_PLAYER)
		return PLAY_MODE_SINGLE_PLAYER;
	else
		return TOUCH_INPUT_MULTI_PLAYER;
}

bool handle_settings() { return false; }
