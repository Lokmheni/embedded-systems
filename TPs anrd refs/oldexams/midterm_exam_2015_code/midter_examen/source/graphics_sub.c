#include "graphics_sub.h"
#include "game.h"

void configureGraphics_Sub() {
	// Configure the SUB engine in mode 5 and activate background 2
	//...TO COMPLETE EXERCISE 3
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	// Configure the VRAM bank C accordingly
	//...TO COMPLETE EXERCISE 3
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
}


void configBG2_Sub() {
	// Configure background BG2 in extended rotoscale mode using 16bit pixels
	//...TO COMPLETE EXERCISE 3
	BGCTRL_SUB[2] = BG_BMP_BASE(0) | BG_BMP16_256x256;

    // Set up affine matrix
    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;
}


void fillScreen_Sub(u16 color) {
	//Fill the buffer of the screen with the given input color
	//...TO COMPLETE EXERCISE 3
	u16* Graphics_subBuffer = BG_BMP_RAM_SUB(0);
	int i;
	for(i = 0; i<256*192; i++) {
		Graphics_subBuffer[i] = color;
	}
}


void fill_32x32_button(unsigned int top, unsigned int left, u16 out, u16 in) {

		//Sanity check. If the coordinates are not correct (the button will be
		//partially or fully outside the screen) return without doing anything
		//...TO COMPLETE EXERCISE 4
	if(top>=0 && top<=160 && left>=0 && left<=224) {

		//Draw the button of 32x32 pixels given the top left corner and the outside
		//color (out) and the inside color (in)
		//...TO COMPLETE EXERCISE 4

		u16* P_Graphics_Buffer = BG_BMP_RAM_SUB(0);
		int row, col;
		for(row = top; row < (top+32); row++) {		//For rows from top to bottom
			for(col = left; col < (left+32); col++)	{ //And for column from left to right
				P_Graphics_Buffer[row*256 + col] = out;	//Assign the color
			}
		}
		for(row = (top+4); row < (top+32-4); row++) {		//For rows from top to bottom
			for(col = (left+4); col < (left+32-4); col++)	{ //And for column from left to right
				P_Graphics_Buffer[row*256 + col] = in;	//Assign the color
			}
		}
	}

		//Example diagram for top = 10 and left = 3

		// coordinates	...		3	4	5	6	7	8	.....		29	30	31	32	33	34

		//				10		out	out	out	out	out	out	.....		out	out	out	out	out	out
		//				11		out	out	out	out	out	out	.....		out	out	out	out	out	out
		//				12		out	out	out	out	out	out	.....		out	out	out	out	out	out
		//				13		out	out	out	out	out	out	.....		out	out	out	out	out	out
		//				14		out	out	out	out	in	in	.....		in	in	out	out	out	out
		//				15		out	out	out	out	in	in	.....		in	in	out	out	out	out
		//				...			.....		....	.....			....		....
		//				...			.....		....	.....			....		....
		//				36		out	out	out	out	in	in	.....		in	in	out	out	out	out
		//				37		out	out	out	out	in	in	.....		in	in	out	out	out	out
		//				38		out	out	out	out	out	out	.....		out	out	out	out	out	out
		//				39		out	out	out	out	out	out	.....		out	out	out	out	out	out
		//				40		out	out	out	out	out	out	.....		out	out	out	out	out	out
		//				41		out	out	out	out	out	out	.....		out	out	out	out	out	out
}
