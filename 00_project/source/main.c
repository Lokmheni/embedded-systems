/**
 * @file main.c
 * @author Simon Thür
 * @brief test for wifi fsm sync
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
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

    printf("set stage\n");
    set_stage();
    swiWaitForVBlank();
    printf("configure sprites\n");
    configureSprites();
    printf("done with sprites\n");
    bool    game = false;
    WifiMsg msg;
    u32     keys;

#ifndef TESTBENCH
    // settings emulation multiplayer
    go_for_multiplayer();
    printf("start game\n");


    for (;;) // game
        {
            // emulate io
            RequestedAction   a;
            RequestedMovement m;
            a = REQ_ACTION_NONE;
            scanKeys();
            keys = keysHeld();
            if (keys & KEY_A)
                {
                    a = REQ_ACTION_JUMP;
                }
            if (keys & KEY_Y)
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
                   gfx,                        // Loaded graphic to display
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
                   gfx1,                       // Loaded graphic to display
                   -1,           // Affine rotation to use (-1 none)
                   false,        // Double size if rotating
                   false,        // Hide this sprite
                   false, false, // Horizontal or vertical flip
                   false         // Mosaic
            );


            swiWaitForVBlank();
            oamUpdate(&oamMain);
        }


#else
    while (!wifi_connect_network())
        ;
    for (;;)
        {

            swiWaitForVBlank();
            if (receive_messages(&msg))
                {
                    printf("<-");
                    switch (msg.msg)
                        {
                        case WIFI_SYNC_INSTR_SCORE_BG:
                            printf("WIFI_SYNC_INSTR_SCORE_BG: %x\n", msg.dat1);
                            break;
                        case WIFI_REQ_LFG:
                            printf("WIFI_REQ_LFG\n");
                            break;
                        case WIFI_PLAYER_X_DIR_ACTION:
                            printf("WIFI_PLAYER_X_DIR_ACTION: %d,", msg.dat1);
                            printf(msg.dat2 == DIRECTION_LEFT ? "left, "
                                                              : "right, ");
                            switch (msg.dat3)
                                {
                                case ACTION_TYPE_IDLE:
                                    printf("ACTION_TYPE_IDLE\n");
                                    break;
                                case ACTION_TYPE_WALK:
                                    printf("ACTION_TYPE_WALK\n");
                                    break;
                                case ACTION_TYPE_JUMP_INPLACE:
                                    printf("ACTION_TYPE_JUMP_INPLACE\n");
                                    break;
                                case ACTION_TYPE_JUMP_MOVE:
                                    printf("ACTION_TYPE_JUMP_MOVE\n");
                                    break;
                                case ACTION_TYPE_NORMAL_ATTACK:
                                    printf("ACTION_TYPE_NORMAL_ATTACK\n");
                                    break;
                                case ACTION_TYPE_SPECIAL_ATTACK:
                                    printf("ACTION_TYPE_SPECIAL_ATTACK\n");
                                    break;
                                case ACTION_TYPE_BLOCK_INPLACE:
                                    printf("ACTION_TYPE_BLOCK_INPLACE\n");
                                    break;
                                case ACTION_TYPE_BLOCK_MOVE:
                                    printf("ACTION_TYPE_BLOCK_MOVE\n");
                                    break;
                                default:
                                    break;
                                }
                            break;
                        case WIFI_PLAYER_Y_YS_HP:
                            printf("WIFI_PLAYER_Y_YS_HP: %d,%d,%d\n", msg.dat1,
                                   msg.dat2, msg.dat3);
                            break;
                        case WIFI_DAMAGE_X_Y_DMG:
                            printf("WIFI_DAMAGE_X_Y_DMG: %d,%d,%d\n", msg.dat1,
                                   msg.dat2, msg.dat3);
                            break;
                        case WIFI_ACK_LM:
                            printf("WIFI_ACK_LM\n");
                            break;
                        case WIFI_NULL_MSG:
                            printf("WIFI_NULL_MSG\n");
                            break;
                        default:
                            break;
                        }
                }

            scanKeys();
            keys = keysDown();
            // score arbitrary nonzero
            if (keys & KEY_UP)
                {
                    wifi_announce_lfg();
                    printf("->lgf\n");
                }
            if (keys & KEY_DOWN)
                {
                    send_ctrl_instruction(START_GAME, 0x03, 0);
                    printf("-> START_GAME\n");
                }
            if (keys & KEY_LEFT)
                {
                    send_ctrl_instruction(IS_PLAY, 0x03, 0);
                    printf("-> IS_PLAY\n");
                }
            if (keys & KEY_RIGHT)
                {
                    send_ctrl_instruction(SET_STAGE, 0x03, 0);
                    printf("-> SET_STAGE\n");
                }
            if (keys & KEY_A)
                {
                    send_ctrl_instruction(RESET_GAME, 0x03, 0);
                    printf("-> RESET_GAME\n");
                }
            if (keys & KEY_B)
                {
                    send_ctrl_instruction(END_ROUND, 0x03, 0);
                    printf("-> END_ROUND\n");
                }
            if (keys & KEY_X)
                {
                    send_ctrl_instruction(WINNER_REMOTE, 0x03, 0);
                    printf("-> WINNER_REMOTE\n");
                }
            if (keys & KEY_Y)
                {
                    send_ctrl_instruction(END_GAME, 0x03, 0);
                    printf("-> END_GAME\n");
                }
            if (keys & KEY_R)
                {
                    send_ctrl_instruction(REQ_ACK, 0x03, 0);
                    printf("-> REQ_ACK\n");
                }
        }
#endif
}
