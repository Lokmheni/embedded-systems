#include "graphics_main.h"
#include "game.h"


u8 UpRightTile[64] =
{
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,0,0,0,
	1,1,1,1,0,0,0,0,
	1,1,1,0,0,0,0,0,
	1,1,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0
};
u8 UpLeftTile[64] =
{
	1,1,1,1,1,1,1,1,
	0,0,0,1,1,1,1,1,
	0,0,0,0,1,1,1,1,
	0,0,0,0,0,1,1,1,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,0,0,1,
	0,0,0,0,0,0,0,1,
	0,0,0,0,0,0,0,1
};
u8 DownRightTile[64] =
{
	1,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,
	1,1,0,0,0,0,0,0,
	1,1,1,0,0,0,0,0,
	1,1,1,1,0,0,0,0,
	1,1,1,1,1,0,0,0,
	1,1,1,1,1,1,1,1
};
u8 DownLeftTile[64] =
{
	0,0,0,0,0,0,0,1,
	0,0,0,0,0,0,0,1,
	0,0,0,0,0,0,0,1,
	0,0,0,0,0,0,1,1,
	0,0,0,0,0,1,1,1,
	0,0,0,0,1,1,1,1,
	0,0,0,1,1,1,1,1,
	1,1,1,1,1,1,1,1
};


void configureGraphics_Main() {
	// Configure the MAIN engine in mode 5 activating background 2
	//... TO COMPLETE EXERCISE 2
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG0_ACTIVE ;
	// Configure the VRAM bank A accordingly
	//... TO COMPLETE EXERCISE 2
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
}

void configBG2_Main() {
	// Configure background BG2 in extended rotoscale mode emulating framebuffer mode
	//... TO COMPLETE EXERCISE 2
	BGCTRL[2] = BG_BMP_BASE(1) | BgSize_B16_256x256;


    // Set up affine matrix
    REG_BG2PA = 256;
    REG_BG2PC = 0;
    REG_BG2PB = 0;
    REG_BG2PD = 256;
}

void fillRectangle(int left, int right, int top, int bottom, u16 color){

	//Check boundaries of rectangle and return if not correct
	//All points (top, bottom, left and right) must be within the screen boundaries
	//... TO COMPLETE EXERCISE 2
	if(top >=0 && top <=191)	//Check boundaries of top
		if(bottom >= 0 && bottom <=191)	//Check boundaries of bottom
			if(left >=0 && left <= 255)	//Check boundaries of left
				if(right >=0 && right <=255) {	//Check boundaries of right


	//Paint the rectangle
	//... TO COMPLETE EXERCISE 2
					int row, col;
					u16* P_Graphics_Buffer = (u16*)BG_BMP_RAM(1);
					for(row = top; row <= bottom; row++)		//For rows from top to bottom
						for(col = left; col <= right; col++)	//And for column from left to right
							P_Graphics_Buffer[row*256 + col] = color;	//Assign the color
				}
	/*
		Example: top=1 bottom=2 left=1 right=2 should paint a 2x2 pixels rectangle
		in the top left corner of the screen as in the following diagram

						Column
					0	1	2	3	... W-1
		 Row 	0	-	-	-	-		-
		 Row	1	-	#	#	-		-
		 Row	2	-	#	#	-		-
		 Row	3	-	-	-	-		-
		 ...					   ...
		 Row   H-1	-	-	-	-		-
	*/
}


// Custom tile
//... TO COMPLETE EXERCISE 5


void configBG0_Main() {

	//Configure background
	//... TO COMPLETE EXERCISE 5
	BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(2) | BG_TILE_BASE(0) ;

	//Copy the tile(s)
	//... TO COMPLETE EXERCISE 5
	dmaCopy(UpRightTile, (u8*)BG_TILE_RAM(0), 64);
	dmaCopy(UpLeftTile, (u8*)BG_TILE_RAM(0) + 64, 64);
	dmaCopy(DownRightTile, (u8*)BG_TILE_RAM(0) + 64 + 64, 64);
	dmaCopy(DownLeftTile, (u8*)BG_TILE_RAM(0) + 64 + 64 + 64, 64);

	//Set color(s) in the palette
	//... TO COMPLETE EXERCISE 5
	BG_PALETTE[0] = ARGB16(1,0,0,0);
	BG_PALETTE[1] = ARGB16(1,0,0,31);

	//Create map
	//... TO COMPLETE EXERCISE 5
	int row, column = 0;
	for(row = 0; row < 24; row+=2) {
		for(column = 0; column < 32; column+=2)
		{
			BG_MAP_RAM(2)[32*row + column] = 0 ;
		}
	}
	for(row = 0; row < 24; row+=2) {
		for(column = 1; column < 32; column+=2)
		{
			BG_MAP_RAM(2)[32*row + column] = 1 ;
		}
	}
	for(row = 1; row < 24; row+=2) {
		for(column = 0; column < 32; column+=2)
		{
			BG_MAP_RAM(2)[32*row + column] = 2 ;
		}
	}
	for(row = 1; row < 24; row+=2) {
		for(column = 1; column < 32; column+=2)
		{
			BG_MAP_RAM(2)[32*row + column] = 3 ;
		}
	}


}


