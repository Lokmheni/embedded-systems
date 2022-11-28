#include <nds.h>
#include <stdio.h>
#include "background.h"


int main(void) {

	int i;

	// Activate main engine and background 0 in tiled mode using 64x64 map
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG0_ACTIVE;
	BGCTRL[0] = BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_64x64;

	// Copy tiles and palette to the corresponding place
	swiCopy(backgroundTiles, BG_TILE_RAM(1), backgroundTilesLen/2);
	swiCopy(backgroundPal, BG_PALETTE, backgroundPalLen/2);

	// Copy map to the map base(s): As the used map is 4 times a standard one,
	// we will need 4 map bases (i.e. 64x64 components * 16 bits = 8 KB)

	// TOP LEFT quadrant of the image in first map base
	for(i=0; i<32; i++)
		dmaCopy(&backgroundMap[i*64], &BG_MAP_RAM(0)[i*32], 64);

	// TOP RIGHT quadrant of the image in second map base
	for(i=0; i<32; i++)
		dmaCopy(&backgroundMap[i*64+32], &BG_MAP_RAM(1)[i*32], 64);

	// BOTTOM LEFT quadrant of the image in third map base
	for(i=0; i<32; i++)
		dmaCopy(&backgroundMap[(i+32)*64], &BG_MAP_RAM(2)[i*32], 64);

	// BOTTOM RIGHT quadrant of the image in fourth map base
	for(i=0; i<32; i++)
		dmaCopy(&backgroundMap[(i+32)*64+32], &BG_MAP_RAM(3)[i*32], 64);

	//Shift background
	while(1) {
		//shifting horizontally from left to right
		for(i=0; i<=512-256; i++){
			swiWaitForVBlank();
			REG_BG0HOFS = i;
		}
		//shifting vertically from up to down
		for(i=0; i<=512-192; i++){
			swiWaitForVBlank();
			REG_BG0VOFS = i;
		}
		//shifting horizontally from right to left
		for(i=512-256; i>=0; i--){
			swiWaitForVBlank();
			REG_BG0HOFS = i;
		}
		//shifting vertically from down to up
		for(i=512-192; i>=0; i--){
			swiWaitForVBlank();
			REG_BG0VOFS = i;
		}
	}

	return 0;
}

