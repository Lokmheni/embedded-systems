/**
 * @file input.c
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "input.h"

#include <nds.h>
#include <stdio.h>

#include "constants.h"
#include "game/game.h"
#include "game/game_controller.h"
#include "graphics.h"

static u16* gfx;


void get_input(RequestedAction* action, RequestedMovement* movement) {}

void getswagkeys()
{
    // Position
    int x = 0, y = 192, keys;
    while (1)
        {
            // Read held keys
            scanKeys();
            keys       = keysHeld();
            Player plr = get_player_local();
            // Modify position of the sprite accordingly
            if ((keys & KEY_RIGHT) || (keys & KEY_DOWN) || (keys & KEY_LEFT) ||
                (keys & KEY_UP))
                {
                    if (keys & KEY_RIGHT)
                        move(&plr, DIRECTION_RIGHT, keys & KEY_UP, SPEED);
                    if (keys & KEY_DOWN)
                        move(&plr, DIRECTION_LEFT, keys & KEY_UP, SPEED);
                    // no jump
                }


            else
                continue;
            x = plr.pos_x;
            y = plr.pos_y;
            oamSet(&oamMain,                   // oam handler
                   0,                          // Number of sprite
                   x, y,                       // Coordinates
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
            swiWaitForVBlank();
            // Update the sprites
            oamUpdate(&oamMain);
        }
}


void get_touchswagggainput()
{
    // Read the touchscreen position
    while (1)
        {
            touchPosition touch;
            touchRead(&touch);
            scanKeys();
            int keys = keysHeld();
            // If touched, set the background in main
            if (keys & KEY_TOUCH)
                {
                    int x = touch.px;
                    int y = touch.py;

                    if ((x > 78 && x < 178) && ((y > 75 && y < 75 + 21) ||
                                                (y > 75 + 21 && y < 75 + 42)))
                        {
                            printf("Lokman");
                            init_main_screen();
                            // REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG3_ACTIVE;
                            // REG_DISPCNT_SUB = ~DISPLAY_BG2_ACTIVE;
                            show_timer();
                        }
                    else
                        continue;
                }
        }
}
