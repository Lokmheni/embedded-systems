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
	u16 r = 64, g = 32, b = 0, black=31;

	//This variable will point to the component that will change from 31 to 0
	u16 c=0;

	//Let's identify from which color we degrade
	switch(color)
	{
	case ARGB16(1,31,0,0):	//RED
			c += r; break;
	case ARGB16(1,0,31,0):	//GREEN
			c += g; break;
	case ARGB16(1,0,0,31):	//BLUE
			c += b; break;
	default:	//Not a basic color
			c += black; break;
	}

    if (c==black) // If not basic Color - Fill BLACK on screen
    {
    	int row, pixel;
		for(row = 0; row < 192; row+=6)
		{  for(pixel = 0; pixel < 256*6/2; pixel++)				// divide by 2 cause we use u16 and need 8 bits per pixel
				buffer[row*256/2 + pixel] = (c << 8) | (c) ;	// c is the number in the palette - we write 2 pixels at the time!
		}
    }
    else //degrade the basic color
    {
		//There are 32 levels of color and 192 rows. 6 rows for each level
		int row, pixel;
		for(row = 0; row < 192; row+=6)
		{
			//Fill 6 rows
			for(pixel = 0; pixel < 256*6/2; pixel++)		// divide by 2 cause we use u16 and need 8 bits per pixel
				buffer[row*256/2 + pixel] = (c << 8) | (c); // c is the number in the palette - we write 2 pixels at the time!
			c++;

		}
    }

}

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	//Configure Engine in Mode 5 enabling Background 2
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	//Configure VRAM bank A to work in Background mode
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	//Configure Background 2 in rotoscale mode using 8-bit pixels
	BGCTRL[2] = BG_BMP_BASE(0) | BgSize_B8_256x256;

	//Set-up affine matrix
    REG_BG2PA = 256;
    REG_BG2PC = 0;
    REG_BG2PB = 0;
    REG_BG2PD = 256;

	//Pointer to the buffer
	u16* buff = BG_GFX;

	//Build the Palette
	u16* myPalette = BG_PALETTE;

	//Build the Palette
	//BLUE is from 0-31
	//GREEN is from 32-63
	//RED is from 64-95
	//BLACK is 31, 63, 95 as all colors when degraded are BLACK
	int i;
	int j = 31;
	for (i=0; i<32; i++)
	{
		myPalette[i] = ARGB16(1,0,0,j);    // BLUE color degradation 0 -31 in palette
		myPalette[i+32] = ARGB16(1,0,j,0); // Green color degradation 32-63 in palette
		myPalette[i+64] = ARGB16(1,j,0,0); // Red color degradation 64-95 in palette
		j--;
	}

    //Let's degradate from BLUE
	degradateColor(buff, ARGB16(1,0,0,31));

	while(true)
		swiWaitForVBlank();
}
