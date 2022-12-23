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
    init_main_screen();
    configureSprites();
    // get_touch_input();
    // configureSprites();
    // printf("\nTemplate nds\n");
    // set screens


    for (;;)
        {
            set_stage();
            swiWaitForVBlank();
            configureSprites();
            while (!wifi_connect_network())
                printf("failed to connect\n");
            printf("connected");
            wifi_announce_lfg();
            printf("sent lfg");
            bool    game = false;
            WifiMsg msg;
            // wait for game
            while (!game)
                {
                    game = receive_messages(&msg);
                }
            printf("receifved msg");
            if (msg.msg == WIFI_REQ_LFG)
                {
                    send_ctrl_instruction(
                        START_GAME | IS_PLAY | SET_STAGE | RESET_GAME, 0);
                }
            reset_game();
            u32 keys;
            printf("start game");
            for (;;) // game
                {
                    RequestedAction   a;
                    RequestedMovement m;
                    scanKeys();
                    keys = keysHeld();
                    if (keys & KEY_A)
                        a = REQ_ACTION_JUMP;
                    if (keys / KEY_Y)
                        a = REQ_ACTION_BLOCK;
                    if (keys & KEY_X)
                        a = REQ_ACTION_ATTACK;
                    if (keys & KEY_LEFT)
                        m = REQ_MOVE_LEFT;
                    else if (keys & KEY_RIGHT)
                        m = REQ_MOVE_RIGHT;
                    else
                        m = REQ_MOVE_NONE;

                    if (receive_messages(&msg))
                        update_game(a, m, msg);
                    else
                        {
                            msg.msg = WIFI_SYNC_INSTR_SCORE;
                            update_game(a, m, msg);
                        }
                    Player l = get_player_local();
                    send_status(&l);


                    // configureSprites();
                    u16* gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32,
                                              SpriteColorFormat_256Color);


                    oamSet(&oamMain, // oam handler
                           0,        // Number of sprite
                           get_player_local().pos_x,
                           get_player_local().pos_y,   // Coordinates
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
                           127,      // Number of sprite
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


                    oamUpdate(&oamMain);
                    swiWaitForVBlank();
                }
        }
}
