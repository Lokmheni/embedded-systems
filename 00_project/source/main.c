/*
 * Template Nintendo DS
 * May 2011
 */

#include <math.h>
#include <nds.h>
#include <stdio.h>

#include "constants.h"
#include "game/game_controller.h"
#include "game/game_sync_fsm.h"
#include "graphics/graphics.h"
#include "numbers.h"
#include "paysage.h"
#include "play_mode.h"
#include "player.h"
#include "player2.h"
#include "streetfighter.h"
#include "string.h"


int main(void)
{

    consoleDemoInit();
    show_logo();
    init_main_screen();
    // configureSprites();
    // get_touch_input();
    // configureSprites();
    // printf("\nTemplate nds\n");
    // set screens


    // do sprites in main

    u16* gfx;
    u16* gfx1;
    // Set up memory bank to work in sprite mode (offset since we are using VRAM
    // A for backgrounds)
    VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;
    VRAM_G_CR = VRAM_ENABLE | VRAM_G_MAIN_SPRITE_0x06400000;

    // Initialize sprite manager and the engine
    oamInit(&oamMain, SpriteMapping_1D_32, false);
    // Allocate space for the graphic to show in the sprite
    gfx =
        oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    gfx1 =
        oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);


    // Copy data for the graphic (palette and bitmap)
    dmaCopy(playerPal, SPRITE_PALETTE, playerPalLen);
    dmaCopy(playerTiles, gfx, playerTilesLen);
    dmaCopy(playerPal, SPRITE_PALETTE, playerPalLen);
    dmaCopy(player2Tiles, gfx1, player2TilesLen);
    dmaCopy(playerTiles, gfx1, playerTilesLen);
    dmaCopy(player2Pal, &SPRITE_PALETTE[playerPalLen / 2], player2PalLen);
    dmaCopy(player2Tiles, gfx1, player2TilesLen);


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
            reset_game(true);
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
                        }
                    if (keys / KEY_Y)
                        {
                            a = REQ_ACTION_BLOCK;
                        }
                    if (keys & KEY_X)
                        {
                            a = REQ_ACTION_ATTACK;
                        }
                    m = REQ_MOVE_NONE;
                    if (keys & KEY_LEFT)
                        {
                            m = REQ_MOVE_LEFT;
                        }
                    if (keys & KEY_RIGHT)
                        {
                            m = REQ_MOVE_RIGHT;
                        }


                    receive_messages(&msg);


                    exec_sync_fsm(a, m, msg, false);

                    Player l = get_player_local();
                    send_status(&l);
                    // print_players();

                    // configureSprites();


                    oamSet(&oamMain, // oam handler
                           0,        // Number of sprite
                           get_player_local().pos_x,
                           get_player_local().pos_y, // Coordinates
                           //    get_player_remote().pos_x,
                           //    get_player_remote().pos_y,  // Coordinates
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


                    oamSet(&oamMain, // oam handler
                           1,        // Number of sprite
                           get_player_remote().pos_x,
                           get_player_remote().pos_y, // Coordinates
                                                      //    SCREEN_WIDTH / 2,
                           //    SPRITE_FLOOR_HEIGHT + SPRITE_HEIGHT / 2,
                           0,                          // Priority
                           1,                          // Palette to use
                           SpriteSize_32x32,           // Sprite size
                           SpriteColorFormat_256Color, // Color format
                           gfx1,         // Loaded graphic to display
                           -1,           // Affine rotation to use (-1 none)
                           false,        // Double size if rotating
                           false,        // Hide this sprite
                           false, false, // Horizontal or vertical flip
                           false         // Mosaic
                    );

                    // int i;
                    // for (i = 0; i < 25; i++)
                    //     {
                    //         swiWaitForVBlank();
                    //     }
                    swiWaitForVBlank();
                    oamUpdate(&oamMain);
                }
        }
}
