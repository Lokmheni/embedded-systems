/**
 * @file wifi.h
 * @author Simon Thür and Lokman Mheni
 * @brief WIFI interface
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 *
 * USAGE of wifi:
 * 1)   When using wifi.h inteface, it is up to the user to first call @ref
 *      wifi_connect_network() to connect to the wifi and set up a port.
 *
 * 2)   After the wifi has been enabled and one wants to play with other
 *      players, it is vital to announce this using @ref announce_lfg(). One can
 *      optionally send this message periodically, but it must be sent at least
 *      once upon connecting to the network.
 *
 * 3)   The user is responsible for periodically polling incoming messages with
 *      @ref receive_messages(). Upon receiving an LFG msg, the receiver becomes
 *      the `master` and is in charge of syncing game (with commands such as
 *      RESET_GAME and IS_PLAY defined in @ref wifi_instr.h )
 *
 * 4)   During game, for every frame send !LOCAL! player  with @ref
 *      send_status(Player* const plr) and the function will arbitrate whether
 *      or not a transmission needs to be sent or not.
 *
 * 5)   Whenever a player does damage, this is to be sent to the remote NDS
 *      using @ref send_damage(u8 dmg_x, u8 dmg_y, u8 dmg)
 *
 * 6)   During the game, it is important to periodically poll for incoming
 *       messages (again with @ref receive_messages()) and handle the (player,
 *      damage or abort) instructions.
 *
 * 7)   Whoever loses the game (health, giveup, whatever) is in charge of
 *      signalling the lose and becomes the new master, tasked with setting up a
 *      new round etc.
 *
 * 8)   To disconnect from wifi (i.e. single player) call @ref
 *      wifi_disconnect_network()
 *
 */


#ifndef __WIFI_H
#define __WIFI_H

#include "../game/game.h"
#include "WiFi_minilib.h"
#include "wifi_instr.h"


typedef enum MsgType
{
    WIFI_SYNC_INSTR_SCORE,
    WIFI_REQ_LFG,
    WIFI_PLAYER_X_DIR_ACTION,
    WIFI_PLAYER_Y_YS_HP,
    WIFI_DAMAGE_X_Y_DMG,
    WIFI_ACK_LM,
} MsgType;


typedef struct __attribute__((__packed__)) WifiMsg
{
    MsgType msg;
    u8      dat1;
    u8      dat2;
    u8      dat3;
} WifiMsg;


// wifi usability stuff
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
bool receive_messages(WifiMsg* rec);

/**
 * @brief Transmit a control instruction (defined in @ref wifi_instr.h) as well
 * as current score of local
 *
 * @param instruction
 * @param score
 */
void send_ctrl_instruction(u8 instruction, u8 score);

/**
 * @brief Announce to network that one is looking for group
 *
 */
void announce_lfg();


// wifi setup and control shit
bool wifi_connect_network();
void wifi_disconnect_network();

#endif // __WIFI_H
