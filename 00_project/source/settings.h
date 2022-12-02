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

enum PlayMode
{
    MULTI_PLAYER,
    SINGLE_PLAYER
};


PlayMode selected_game_mode();

bool handle_settings();

#endif  // __SETTINGS_H
