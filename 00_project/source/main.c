/*
 * Template Nintendo DS
 * May 2011
 */

#include <math.h>
#include <nds.h>
#include <stdio.h>

#include "game/game_controller.h"
#include "graphics/graphics.h"
#include "numbers.h"
#include "paysage.h"
#include "play_mode.h"
#include "player.h"
#include "player2.h"
#include "streetfighter.h"
#include "string.h"
#include "graphics/chrono_display.h"

int min, sec, msec;

/*void ISR_TIMER0()
{
	msec = (msec + 1)%1000;
	if(msec == 0)
	{
		sec = (sec+1) % 60;
		if(sec == 0)
			min++;
	}
	updateChronoDisp_Sub(min, sec, msec);
}*/


int main(void)
{
    consoleDemoInit();

    // using tiled mode?

    //Enable a suitable VRAM block and map it to the main engine
    VRAM_A_CR = VRAM_ENABLE
    			| VRAM_A_MAIN_BG;
    //Configure the engine in Mode 0 and use the BG0
    REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;
    //Configure the engine to be used as a 32x32 grid of tiles of 256 colors
    //Use BG_MAP_BASE(0) and  a suitable BG_TILE_BASE
    BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

    //Copy the tiles and the palette to the corresonding location
   	swiCopy(numbersTiles, BG_TILE_RAM(1), numbersTilesLen);
    swiCopy(numbersPal, BG_PALETTE, numbersPalLen);

    //The digit 8 is printed in the upper left part of the screen
    printDigit(BG_MAP_RAM(0), 8,0,0);

    //The value 12:34.567 is going to be printed in the center of the screen
    updateChronoDisp(BG_MAP_RAM(0),12,34,567);

    //The background color is ste to BLACK and the digits color is set to RED
    changeColorDisp(BLACK, RED);

    while(1) {
    	swiWaitForVBlank();
    }



    //Player* t;
    //init_screens();


    //sprite_pos_local(t);
    //configureSprites();
    //get_touch_input();
    // configureSprites();
    // printf("\nTemplate nds\n");
    // set screens


    // do sprites in main

    //displaying timer in sub in main.c

    /*initChronoDisp_Sub();
	changeColorDisp_Sub(RED);
	irqInit();
	min = sec = msec = 0;
	TIMER_DATA(0) = TIMER_FREQ_1024(1000);
	TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqSet(IRQ_TIMER0, &ISR_TIMER0);
	irqEnable(IRQ_TIMER0);

	while(1) {
			swiWaitForVBlank();
		}*/
}




