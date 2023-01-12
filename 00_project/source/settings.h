/**
 * @file settings.h
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __SETTINGS_H
#define __SETTINGS_H
#include <nds.h>
#include "io/input.h"

typedef enum
{
    PLAY_MODE_MULTI_PLAYER,
    PLAY_MODE_SINGLE_PLAYER
} PlayMode;


PlayMode selected_game_mode(TouchInput* touchinput);

bool handle_settings();

#endif // __SETTINGS_H
