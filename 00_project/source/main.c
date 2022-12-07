/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

#include "io/wifi.h"


void print_msg(WifiMsg m)
{
    printf("%x-%x-%x-%x\n", m.msg, m.dat1, m.dat2, m.dat3);
}


int main(void)
{

    consoleDemoInit();
    printf("TEST_WIFI\n");

    // init wifi
    while (!wifi_connect_network())
        {
            printf("FAILED TO START WIFI\n");
            swiWaitForVBlank();
        }
    printf("WIFI connection established\n");
    swiWaitForVBlank();


    bool connection = false;
    printf("press any button to connect to wifi\n");
    scanKeys();
    while (!connection)
        {
            scanKeys();
            if (keysDown())
                {
                    connection = wifi_connect_network();
                    if (!connection)
                        printf("\nfailed to connect to wifi");
                }
            swiWaitForVBlank();
        }
    printf("CONNECTION ESTABLISHED\n");
    printf("PressButton A to send LFG\n");
    printf("PressButton B to send INSTR");
    swiWaitForVBlank();


    WifiMsg transfer;
    for (;;)
        // sending
        scanKeys();
    if (keysDown() & KEY_A)
        {
            wifi_announce_lfg();
            printf("-> LFG\n");
        }
    if (keysDown() & KEY_B)
        {
            send_ctrl_instruction(RESET_GAME | START_GAME | REQ_ACK, 1);
            printf("-> INSTR\n");
        }

    if (receive_messages(&transfer))
        {
            printf("<- ");
            print_msg(transfer);
        }

    swiWaitForVBlank();
}
