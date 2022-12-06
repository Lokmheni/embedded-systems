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


typedef enum MsgType
{
    WIFI_SYNC,
    WIFI_STOP,
    WIFI_PLAYER_X_DIR_ACTION,
    WIFI_PLAYER_Y_YS_HP,
    WIFI_DAMAGE_X_Y_DMG,
} MsgType;


typedef struct __attribute__((__packed__)) WifiMsg
{
    MsgType msg;
    u8      dat1;
    u8      dat2;
    u8      dat3;
} WifiMsg;


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

/**
 * @brief Receive messages from remote. No handling of data is done at this
 *        stage other than confirming the correct length of packet
 *
 * @param[out] rec recieved message
 * @return true if the correct packet size was received
 * @return false if the packet size was not of correct size (includes packet
 *         size 0, e.g. no messages received)
 */
bool receive_changes(WifiMsg* rec);


// wifi setup and control shit
bool wifi_connect_network();
void wifi_disconnect_network();

#endif // __WIFI_H
