/**
 * @file wifi.c
 * @author Simon Thür and Lokman Mheni
 * @brief Control WIFI through packets of 4 bytes
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "wifi.h"

#include "../constants.h"

// used to detect changes (to then only send that which has changed)
Player old_plr_state;


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


void send_status(Player* const plr)
{
    // check jump and health
    if ((plr->y_speed && old_plr_state.pos_y == SPRITE_FLOOR_HEIGHT) ||
        plr->health != old_plr_state.health)
        {
            WifiMsg transfer;
            transfer.msg  = WIFI_PLAYER_Y_YS_HP;
            transfer.dat1 = plr->pos_y;
            transfer.dat2 = plr->y_speed;
            transfer.dat3 = plr->health;
        }
    // check necessity for x dir speed
    if (plr->dir != old_plr_state.dir || plr->action != old_plr_state.action)
        {
            WifiMsg transfer;

            transfer.msg  = WIFI_PLAYER_X_DIR_ACTION;
            transfer.dat1 = plr->pos_x;
            transfer.dat2 = plr->dir;
            transfer.dat3 = plr->action;

            sendData(&transfer, sizeof(transfer));
        }
}
void send_damage(int dmg_x, int dmg_y) {}

void receive_status(PlayerState* plr, bool* damage, int* dmg_x, int* dmg_y) {}
bool wifi_connect_network()
{
    // WiFi initialization
    if (!initWiFi())
        return false;
    // Socket initialization
    if (!openSocket())
        return false;
    return true;
}
void wifi_disconnect_network()
{ // Close the Socket
    void closeSocket();
    // Disconnect the WiFi
    void disconnectFromWiFi();
}
