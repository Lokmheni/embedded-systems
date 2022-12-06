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
#include "WiFi_minilib.h"


// wifi usability shit
/**
 * @brief Transfer player updates to remote device.
 * @note  This function can be called even when no changes are made, as it
 * detects itself changes and transmits only when necessary
 *
 * @param[in] plr local player current state
 */
void send_status(Player* const plr);

/**
 * @brief Transfer damage done to remote device (irrelevant of whether the
 *        target was hit)
 *
 * @param dmg_x x coord of damage
 * @param dmg_y y coord of damage
 * @param dmg amount of damage done if it strikes
 */
void send_damage(u8 dmg_x, u8 dmg_y, u8 dmg);

void receive_status(PlayerState* plr, bool* damage, int* dmg_x, int* dmg_y);


// wifi setup and control shit
bool wifi_connect_network();
void wifi_disconnect_network();

#endif // __WIFI_H
