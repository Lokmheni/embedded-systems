/**
 * @file wifi.c
 * @author Simon Thür and Lokman Mheni
 * @brief Control WIFI through packets of 4 bytes
 * @version 1.0
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "wifi.h"

#include "../constants.h"

// used to detect changes (to then only send that which has changed)
Player old_plr_state;


void send_status(Player* const plr)
{
    // check jump and health
    if ((plr->y_speed > old_plr_state.y_speed) ||
        plr->health != old_plr_state.health)
        {
            WifiMsg transfer;
            transfer.msg  = WIFI_PLAYER_Y_YS_HP;
            transfer.dat1 = plr->pos_y;
            transfer.dat2 = *(u8*)&plr->y_speed;
            transfer.dat3 = plr->health;

            sendData((char*)&transfer, sizeof(transfer));
        }
    // check necessity for x dir speed
    if (plr->dir != old_plr_state.dir || plr->action != old_plr_state.action)
        {
            WifiMsg transfer;

            transfer.msg  = WIFI_PLAYER_X_DIR_ACTION;
            transfer.dat1 = plr->pos_x;
            transfer.dat2 = plr->dir;
            transfer.dat3 = plr->action;

            sendData((char*)&transfer, sizeof(transfer));
        }
}
void send_damage(u8 dmg_x, u8 dmg_y, u8 dmg)
{
    WifiMsg transfer;
    transfer.msg  = WIFI_DAMAGE_X_Y_DMG;
    transfer.dat1 = dmg_x;
    transfer.dat2 = dmg_y;
    transfer.dat3 = dmg;

    sendData((char*)&transfer, sizeof(transfer));
}

bool receive_messages(WifiMsg* rec)
{
    if (receiveData((char*)rec, sizeof(rec)) != sizeof(rec))
        {
            rec->msg = WIFI_NULL_MSG;
            return false;
        }

    if (rec->msg == WIFI_SYNC_INSTR_SCORE && (rec->dat1 & REQ_ACK))
        {
            rec->msg = WIFI_ACK_LM;
            sendData((char*)rec, sizeof(rec));
            rec->msg = WIFI_SYNC_INSTR_SCORE;
        }
    return true;
}


void send_ctrl_instruction(u8 instruction, u8 score)
{
    WifiMsg transfer;
    transfer.msg  = WIFI_SYNC_INSTR_SCORE;
    transfer.dat1 = instruction;
    transfer.dat2 = score;
    sendData((char*)&transfer, sizeof(transfer));
}


void wifi_announce_lfg()
{
    WifiMsg transfer;
    transfer.msg = WIFI_REQ_LFG;
    sendData((char*)&transfer, sizeof(transfer));
}


bool wifi_connect_network()
{
    // WiFi initialization
    if (!initWiFi())
        return false;
    // Socket initialization
    if (!openSocket())
        {
            disconnectFromWiFi();
            return false;
        }
    return true;
}
void wifi_disconnect_network()
{ // Close the Socket
    void closeSocket();
    // Disconnect the WiFi
    void disconnectFromWiFi();
}
