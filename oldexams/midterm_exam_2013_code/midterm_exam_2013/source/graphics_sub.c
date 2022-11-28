#include "graphics_sub.h"
#include "game.h"
#include "bottom.h"


u8 emptyTile[64] =
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};
u8 fullTile[64] =
{
	255,255,254,254,255,255,254,254,
	255,255,254,254,255,255,254,254,
	254,254,255,255,254,254,255,255,
	254,254,255,255,254,254,255,255,
	255,255,254,254,255,255,254,254,
	255,255,254,254,255,255,254,254,
	254,254,255,255,254,254,255,255,
	254,254,255,255,254,254,255,255
};


void configureGraphics_Sub() {
	// Configure the MAIN engine in Rotoscale Mode
	//...TO COMPLETE EXERCISE 2
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG0_ACTIVE;
	// Configure the corresponding VRAM memory bank correctly
	//...TO COMPLETE EXERCISE 2
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
}


void configBG2_Sub() {
	// Configure background BG2 in rotoscale mode using 8bit pixels
	//...TO COMPLETE EXERCISE 2
	BGCTRL_SUB[2] = BG_BMP_BASE(0) | BG_BMP8_256x256;

	// Transfer image and palette to the corresponding memory locations
	//...TO COMPLETE EXERCISE 2
	swiCopy(bottomBitmap, BG_BMP_RAM_SUB(0), bottomBitmapLen/2);
	swiCopy(bottomPal, BG_PALETTE_SUB, bottomPalLen/2);

    // Set up affine matrix
    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;
}



// Custom empty tile
//...TO COMPLETE EXERCISE 5

// Custom full tile
//...TO COMPLETE EXERCISE 5

void configBG0_Sub() {

	// Configure background BG0 in tiled mode using a 32x32 grid and 256 colors
	//...TO COMPLETE EXERCISE 5
	BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(25) | BG_TILE_BASE(3);

	// Transfer custom tiles to the proper memory locations
	//...TO COMPLETE EXERCISE 5
	dmaCopy(emptyTile, (u8*)BG_TILE_RAM(4), 64);
	dmaCopy(fullTile, (u8*)BG_TILE_RAM(4) + 64, 64);

	// Assign color to the used components of the palette
	//...TO COMPLETE EXERCISE 5
	//BG_PALETTE[0] = ARGB16(1,0,0,0);
	BG_PALETTE[254] = BLACK;
	BG_PALETTE[255] = GREY;

	// Create map to show a separation of 16 pixels (2 tiles) between regions
	//...TO COMPLETE EXERCISE 5
	int row, col;
	for(row=0; row<32;row++) {
		for(col=0; col<32; col++) {
			BG_MAP_RAM_SUB(25)[row*32 + col] = 0;
		}
	}
	for(row=0; row<32;row++) {
		for(col=8; col<32; col+=8) {
			BG_MAP_RAM_SUB(25)[row*32 + col] = 1;
			BG_MAP_RAM_SUB(25)[row*32 + col] = 1;
		}
	}
}
