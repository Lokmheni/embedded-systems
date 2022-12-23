/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

#include "game/game_controller.h"
#include "graphics/graphics.h"


int main(void)
{

    consoleDemoInit();
    show_logo();
    init_main_screen();
    configureSprites();
    // get_touch_input();
    // configureSprites();
    // printf("\nTemplate nds\n");
    // set screens

    printf("BEGIN\n");
    for (;;)
        {
            printf("set stage\n");
            set_stage();
            swiWaitForVBlank();
            printf("configure sprites\n");
            configureSprites();
            printf("done with sprites\n");
            while (!wifi_connect_network())
                {
                    printf("failed to connect\n");
                    int i;
                    for (i = 0; i < 50; i++)
                        {
                            swiWaitForVBlank();
                        }
                }
            printf("connected\n");
            wifi_announce_lfg();
            printf("sent lfg\n");
            bool    game = false;
            WifiMsg msg;
            // wait for game
            while (!game)
                {
                    game = receive_messages(&msg);
                }
            printf("receifved msg\n");
            if (msg.msg == WIFI_REQ_LFG)
                {
                    send_ctrl_instruction(
                        START_GAME | IS_PLAY | SET_STAGE | RESET_GAME, 0);
                    printf("sent start command\n");
                }
            reset_game();
            u32 keys;
            printf("start game\n");
            for (;;) // game
                {
                    RequestedAction   a;
                    RequestedMovement m;
                    a = REQ_ACTION_NONE;
                    scanKeys();
                    keys = keysHeld();
                    if (keys & KEY_A)
                        {
                            a = REQ_ACTION_JUMP;
                            printf("Key pressed A\n");
                        }
                    if (keys / KEY_Y)
                        {
                            a = REQ_ACTION_BLOCK;
                            printf("Key pressed Y\n");
                        }
                    if (keys & KEY_X)
                        {
                            a = REQ_ACTION_ATTACK;
                        }
                    m = REQ_MOVE_NONE;
                    if (keys & KEY_LEFT)
                        {
                            m = REQ_MOVE_LEFT;
                            printf("Key pressed left\n");
                        }
                    if (keys & KEY_RIGHT)
                        {
                            m = REQ_MOVE_RIGHT;
                            printf("Key pressed right\n");
                        }


                    if (receive_messages(&msg))
                        {
                            printf("received wifi msg\n");
                            update_game(a, m, msg);
                        }
                    else
                        {
                            msg.msg = WIFI_NULL_MSG;
                            update_game(a, m, msg);
                        }
                    Player l = get_player_local();
                    send_status(&l);
                    // print_players();

                    // configureSprites();
                    u16* gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32,
                                              SpriteColorFormat_256Color);


                    oamSet(&oamMain, // oam handler
                           0,        // Number of sprite
                                     //    get_player_local().pos_x,
                           //    get_player_local().pos_y, // Coordinates
                           get_player_remote().pos_x,
                           get_player_remote().pos_y,  // Coordinates
                           0,                          // Priority
                           0,                          // Palette to use
                           SpriteSize_32x32,           // Sprite size
                           SpriteColorFormat_256Color, // Color format
                           gfx,          // Loaded graphic to display
                           -1,           // Affine rotation to use (-1 none)
                           false,        // Double size if rotating
                           false,        // Hide this sprite
                           false, false, // Horizontal or vertical flip
                           false         // Mosaic
                    );
                    // Update the sprites
                    oamUpdate(&oamMain);


                    gfx += 32 * 32;


                    oamSet(&oamMain, // oam handler
                           1,        // Number of sprite
                           translate_remote_x(get_player_remote().pos_x),
                           get_player_remote().pos_y,  // Coordinates
                           0,                          // Priority
                           0,                          // Palette to use
                           SpriteSize_32x32,           // Sprite size
                           SpriteColorFormat_256Color, // Color format
                           gfx,          // Loaded graphic to display
                           -1,           // Affine rotation to use (-1 none)
                           false,        // Double size if rotating
                           false,        // Hide this sprite
                           false, false, // Horizontal or vertical flip
                           false         // Mosaic
                    );

                    oamUpdate(&oamMain);
                    // int i;
                    // for (i = 0; i < 25; i++)
                    //     {
                    //         swiWaitForVBlank();
                    //     }
                    swiWaitForVBlank();
                }
        }
}
