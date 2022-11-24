

#include "graphics_sub.h"
//... TO COMPLETE EXERCISE 1



// ------ Exercise 1 ------ //

/*
 * Print timer's plate, dial and buttons in extended rotoscale mode
 * with palette of 256 colors
 */
void configureGraphics_Sub_Plate()
{
	// Configure the VRAM bank C accordingly
	//... TO COMPLETE EXERCISE 1


	// Configure the engine in Mode 5 and use the BG3
	//... TO COMPLETE EXERCISE 1


	// Configure background BG3 in extended rotoscale mode using 8 bit pixels and "0" for the base address
	//... TO COMPLETE EXERCISE 1


	// Transfer image bitmap and palette to the corresponding memory locations
	//... TO COMPLETE EXERCISE 1


	// Set up affine matrix
	REG_BG3PA_SUB = 256;
	REG_BG3PC_SUB = 0;
	REG_BG3PB_SUB = 0;
	REG_BG3PD_SUB = 256;
}
