#include "clk_hand.h"


// ------ Exercise 3 ------ //

/*
 * Rotate the image representing the red hand of the clock on the background 2
 * of the bottom screen.
 */
void rotateImage_Sub_BG2(int x, int y, float angle_rads)
{
	// Compute the distance from rotation point to system origin
	//... TO COMPLETE EXERCISE 3


	// Determine the rotation angle alpha of the image
	//... TO COMPLETE EXERCISE 3


	// Image rotation matrix
	//... TO COMPLETE EXERCISE 3


	// Image translation
	//... TO COMPLETE EXERCISE 3

}



/////////////////////////////////////////////////////////
////	DO NOT MODIFY THE FUNCTION BELOW
/////////////////////////////////////////////////////////

/*
 * Update the angular position of the red hand, based on
 * the initial timer's value and the current one.
 */
void updateClkHandPosition(uint32 sec_init, uint32 sec_curr)
{
	static float angle = 0; // Reset the angle (only once)

	if (sec_curr != sec_init)
		angle = -(2*M_PI*sec_curr)/sec_init;

	rotateImage_Sub_BG2((CLK_HAND_WIDTH_PIX/2) + CLK_HAND_MARGIN_X_PIX, (CLK_HAND_WIDTH_PIX/2) + CLK_HAND_MARGIN_Y_PIX, angle);
}

