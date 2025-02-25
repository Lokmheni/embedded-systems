#include "clk_hand.h"

#include "nds/arm9/background.h"

// ------ Exercise 3 ------ //

/*
 * Rotate the image representing the red hand of the clock on the background 2
 * of the bottom screen.
 */
void rotateImage_Sub_BG2( int x, int y, float angle_rads )
{
    // Compute the distance from rotation point to system origin
    double r = sqrt( x * x + y * y );


    // Determine the rotation angle alpha of the image
    double alpha = atan( ( float ) x / ( float ) y ) + angle_rads;


    // Image rotation matrix


    REG_BG2PA_SUB = 256 * cos( angle_rads );
    REG_BG2PB_SUB = 256 * sin( angle_rads );
    REG_BG2PC_SUB = -256 * sin( angle_rads );
    REG_BG2PD_SUB = 256 * cos( angle_rads );


    // Image translation
    REG_BG2X_SUB = 256 * ( x - r * sin( alpha ) - CLK_HAND_MARGIN_X_PIX );
    REG_BG2Y_SUB = 256 * ( y - r * cos( alpha ) - CLK_HAND_MARGIN_X_PIX );
}


/////////////////////////////////////////////////////////
////	DO NOT MODIFY THE FUNCTION BELOW
/////////////////////////////////////////////////////////

/*
 * Update the angular position of the red hand, based on
 * the initial timer's value and the current one.
 */
void updateClkHandPosition( uint32 sec_init, uint32 sec_curr )
{
    static float angle = 0;  // Reset the angle (only once)

    if ( sec_curr != sec_init )
        angle = -( 2 * M_PI * sec_curr ) / sec_init;

    rotateImage_Sub_BG2( ( CLK_HAND_WIDTH_PIX / 2 ) + CLK_HAND_MARGIN_X_PIX,
                         ( CLK_HAND_WIDTH_PIX / 2 ) + CLK_HAND_MARGIN_Y_PIX,
                         angle );
}
