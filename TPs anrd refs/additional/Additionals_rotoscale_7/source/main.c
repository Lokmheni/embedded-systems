/*---------------------------------------------------------------------------------

	Basic template code for starting a DS app

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>

/*
 * Function that receives a basic color (RED, GREEN, BLUE)
 * and makes a degradation in the screen (from the upper part to the bottom)
 * If the color received is not a basic one the screen is filled with black
 */
void degradateColor(u16* buffer, u16 color)
{
	//Three components of the color (by default BLACK)
	int r = 0, g = 0, b = 0;

	//This variable will point to the component that will change from 31 to 0
	int *c;

	//Let's identify from which color we degrate
	switch(color)
	{
	case ARGB16(1,31,0,0):	//RED
			c = &r; break;
	case ARGB16(1,0,31,0):	//GREEN
			c = &g; break;
	case ARGB16(1,0,0,31):	//BLUE
			c = &b; break;
	default:	//Not a basic color
			c = NULL; break;
	}

	//If it is one of the basic colors, start from it
	if(c) *c = 31;

	//There are 32 levels of color and 192 rows. 6 rows for each level
	int row, pixel;
	for(row = 0; row < 192; row+=6)
	{
		//Fill 6 rows
		for(pixel = 0; pixel < 256*6; pixel++)
			buffer[row*256 + pixel] = ARGB16(1,r,g,b);

		if(c) *c = *c-1; //Only decrement level if we started from a basic color
	}

}


/*
 * This function receives the pointer to the buffer and shifts one row up
 * The last row is 'replicated' and the first one is lost.
 */
void shiftUp(u16* buffer)
{
	int row, col;
	for(row = 0; row < 191; row++)
		for(col = 0; col < 256; col++)
			buffer[row*256 + col] = buffer[(row + 1)*256 + col];
}

/*
 * This function transforms all the colors on the buffer into gray
 * with a given intensity
 */
void grayScale(u16* buffer)
{
	u16 color, r_comp, g_comp, b_comp, mean, row, col;
	for(row = 0; row < 192; row++)
		for(col = 0; col < 256; col++)
		{
			color = buffer[row*256 + col];	//Value of the pixel in (row,col)
			r_comp = color & 0x001F;		//Red Component
			g_comp = (color >> 5) & 0x01F;	//Green Component
			b_comp = (color >> 10) & 0x01F;	//Blue Component
			mean = 3*r_comp/10;		//3/10 of RED
			mean += 6*g_comp/10;	//6/10 of GREEN
			mean += 1*b_comp /10;	//1/10 of BLUE
			buffer[row*256 + col] = ARGB16(1,mean, mean, mean);	//New gray value
		}
}

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	//Configure Engine in Mode 5 enabling Background 2
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	//Configure VRAM bank A to work in Background mode
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	//Configure Background 2 in rotoscale mode using 16-bit pixels
	BGCTRL[2] = BG_BMP_BASE(0) | BgSize_B16_256x256;

	//Set-up affine matrix
    REG_BG2PA = 256;
    REG_BG2PC = 0;
    REG_BG2PB = 0;
    REG_BG2PD = 256;

	//Pointer to the buffer
	u16* buff = BG_BMP_RAM(0);

	//Let's degradate from GREEN
	degradateColor(buff, ARGB16(1,0,31,0));

	//Let's shift 60 lines
	int i = 0;
	for(i = 0; i < 60; i++)
		shiftUp(buff);

	//Let's apply GrayScale
	grayScale(buff);

	while(true)
		swiWaitForVBlank();
}
