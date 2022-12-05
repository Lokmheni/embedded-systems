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


// used to detect changes (to then only send that which has changed)
Player old_plr_state;


typedef enum MsgType
{
    WIFI_SYNC,
    WIFI_STOP,
    WIFI_PLAYER_X_DIR_SPEED,
    WIFI_PLAYER_Y_YS_ACTION,
    WIFI_DAMAGE_X_Y_DMG,
} MsgType;


typedef struct WifiMsg
{
    MsgType msg;
    u8      dat1;
    u8      dat2;
    u8      dat3;
} WifiMsg;


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

void send_status(Player* const plr) {}
void send_damage(int dmg_x, int dmg_y) {}

void receive_status(PlayerState* plr, bool* damage, int* dmg_x, int* dmg_y) {}
