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

typedef enum
{
    MULTI_PLAYER_MODE,
    SINGLE_PLAYER_MODE
} PlayMode;


PlayMode selected_game_mode();

bool handle_settings();

#endif // __SETTINGS_H
