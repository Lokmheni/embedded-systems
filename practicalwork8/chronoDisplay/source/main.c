/*---------------------------------------------------------------------------------

	Basic template code for starting a DS app

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include "chrono_display.h"

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	//Enable a suitable VRAM block and map it to the main engine
//	VRAM_A_CR = ...
	//Configure the engine in Mode 0 and use the BG0
//	REG_DISPCNT = ...
	//Configure the engine to be used as a 32x32 grid of tiles of 256 colors
	//Use BG_MAP_BASE(0) and  a suitable BG_TILE_BASE
//	BGCTRL[0] = ...

	//Copy the tiles and the palette to the corresonding location
//	swiCopy(...
//	swiCopy(...

	//The digit 8 is printed in the upper left part of the screen
	printDigit(BG_MAP_RAM(0), 8,0,0);

	//The value 12:34.567 is going to be printed in the center of the screen
	updateChronoDisp(BG_MAP_RAM(0),12,34,567);

	//The background color is ste to BLACK and the digits color is set to RED
	changeColorDisp(BLACK, RED);

	while(1) {
		swiWaitForVBlank();
	}
}
