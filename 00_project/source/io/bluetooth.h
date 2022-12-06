/**
 * @file bluetooth.h
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H


#include "../game/game.h"

void send_status(PlayerState* const plr);
void send_damage(int dmg_x, int dmg_y);

void receive_status(PlayerState* plr, bool* damage, int* dmg_x, int* dmg_y);


#endif // __BLUETOOTH_H
