/**
 * @file wifi.h
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __WIFI_H
#define __WIFI_H


#include "../game/game.h"


// wifi usability shit
void send_status( PlayerState* const plr );
void send_damage( int dmg_x, int dmg_y );

void receive_status( PlayerState* plr, bool* damage, int* dmg_x, int* dmg_y );


// wifi setup and control shit
bool wifi_connect_network();

#endif  // __WIFI_H
