/*---------------------------------------------------------------------------------

    Basic template code for starting a DS app

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <nds/arm9/background.h>
#include <nds/arm9/video.h>
#include <stdio.h>

#include "chrono_display.h"
#include "numbers.h"


#define MY_TILE_BASE 1
#define MY_MAP_BASE  0
//---------------------------------------------------------------------------------
int main(void)
{
    //---------------------------------------------------------------------------------

    // Enable a suitable VRAM block and map it to the main engine
    VRAM_A_CR   = VRAM_ENABLE | VRAM_A_MAIN_BG;
    // Configure the engine in Mode 0 and use the BG0
    REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;


    // Configure the engine to be used as a 32x32 grid of tiles of 256
    // colors Use BG_MAP_BASE(0) and  a suitable BG_TILE_BASE
    BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(MY_MAP_BASE) |
                BG_TILE_BASE(MY_TILE_BASE);

    // Copy the tiles and the palette to the corresonding location
    dmaCopy(numbersTiles, BG_TILE_RAM(MY_TILE_BASE), numbersTilesLen);
    dmaCopy(numbersPal, BG_PALETTE, numbersPalLen);
    // The digit 8 is printed in the upper left part of the screen
    printDigit(BG_MAP_RAM(0), 8, 0, 0);

    // The value 12:34.567 is going to be printed in the center of the screen
    updateChronoDisp(BG_MAP_RAM(0), 12, 34, 567);

    // The background color is ste to BLACK and the digits color is set to RED
    changeColorDisp(BLACK, RED);

    while (1)
        {
            swiWaitForVBlank();
        }
}
