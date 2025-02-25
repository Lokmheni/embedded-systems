#include <nds.h>
#include <stdio.h>

#include "chrono_display.h"
#include "math.h"
#include "quarter.h"

// Define to use paletes easily
#define PALETTE(x) (x << 12)

// Buttons of the simon game
typedef enum
{
    RED,
    YELLOW,
    BLUE,
    GREEN,
    NONE
} button;

// Active button
button active_button = NONE;

// Time variables (for the chronometer)
int min = 0, sec = 0, msec = 0;

// Timer 2 ISR (chronometer)
void TIMER2_ISR()
{
    msec = (msec + 1) % 1000;
    if (!msec)
        {
            sec = (sec + 1) % 60;
            if (!sec)
                min++;
        }
}

// Timer0 ISR (blinking effect of the buttons)
void TIMER0_ISR()
{
    // It is necessary to wait until the screen is refreshed...
    swiWaitForVBlank();

    // Switching between light and dark color
    switch (active_button)
        {
        case RED:
            BG_PALETTE_SUB[17] ^= 0x0B;
            break;
        case GREEN:
            BG_PALETTE_SUB[1] ^= (0x0B << 5);
            break;
        case BLUE:
            BG_PALETTE_SUB[49] ^= (0x0B << 10) | (0x5 << 5);
            break;
        case YELLOW:
            BG_PALETTE_SUB[33] ^= 0x0B | (0xB << 5);
            break;
        default:
            BG_PALETTE_SUB[1]  = ARGB16(1, 0, 20, 0);
            BG_PALETTE_SUB[17] = ARGB16(1, 20, 0, 0);
            BG_PALETTE_SUB[33] = ARGB16(1, 20, 20, 0);
            BG_PALETTE_SUB[49] = ARGB16(1, 0, 0, 20);
            break;
        }
}

// Update the chronometer every VBlank
void VBLANK_ISR() { updateChronoDisp_Main(min, sec, msec); }

//-----------------------------------------------------------------------------
int main(void)
{
    //-----------------------------------------------------------------------------
    // Enable the VRAM bank
    VRAM_C_CR       = VRAM_ENABLE | VRAM_C_SUB_BG;
    // Enable the Engine
    REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE;

    // Configure BG0
    BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_16 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

    /*********************
     * TO COMPLETE EX. 6
     *********************/
    // Copy the tiles to the tile base
    //...

    // Copy the 4 16-colors palettes (4 times the same palette)
    //...
    //...
    //...
    //...

    // Fill all the BG0 with the white tile (tile corresponding to the 12th
    // position of the map, the upper right corner of the original image)
    //...

    // Create the map of the BG0
    //...


    /**********************************************/


    // Change the default colors of the quarters
    BG_PALETTE_SUB[1]  = ARGB16(1, 0, 20, 0);  // Upper left (green)
    BG_PALETTE_SUB[17] = ARGB16(1, 20, 0, 0);  // Upper right (red)
    BG_PALETTE_SUB[33] = ARGB16(1, 20, 20, 0); // Bottom left (yellow)
    BG_PALETTE_SUB[49] = ARGB16(1, 0, 0, 20);  // Bottom rigth (Blue)

    // Enable Interrupt for the timers and Vblank and set the handlers
    irqSet(IRQ_TIMER0, &TIMER0_ISR);
    irqEnable(IRQ_TIMER0);
    irqSet(IRQ_TIMER2, &TIMER2_ISR);
    irqEnable(IRQ_TIMER2);
    irqSet(IRQ_VBLANK, &VBLANK_ISR);
    irqEnable(IRQ_VBLANK);

    // Configure the timers
    TIMER0_DATA = TIMER_FREQ_1024(8);
    TIMER0_CR   = TIMER_DIV_1024 | TIMER_IRQ_REQ | TIMER_ENABLE;
    TIMER2_DATA = TIMER_FREQ_256(1000);
    TIMER2_CR   = TIMER_DIV_256 | TIMER_IRQ_REQ;

    // Initialize the chrono display
    initChronoDisp_Main();
    changeColorDisp_Main(ARGB16(1, 31, 31, 0));
    updateChronoDisp_Main(0, 0, 0);

    int x, y, radius;
    int hits = 0;
    int last;
    active_button = last = NONE;

    while (1)
        {

            /***********************
             * TO COMPLETE EX. 7
             ***********************/
            // Scan the keys
            //...

            // If start is pressed, the game starts
            //		if(....)
            //		{
            //			//Init the randomizer
            //			srand(TIMER0_DATA);
            //			//Random button starts
            //			active_button = rand() % 4;
            //			//Enable Timers
            //			TIMER0_CR |= TIMER_ENABLE;
            //			TIMER2_CR |= TIMER_ENABLE;
            //			//10 times will be hitted
            //			hits = 9;
            //			//Initialize the time variables for the chronometer
            //			min = sec = msec = 0;
            //		}
            /*************************************/


            /***********************
             * TO COMPLETE EX. 8
             ***********************/
            // Declare a touchPosition variable
            //...

            // Poll the touch-screen
            //...

            // If the touch received is different to (0,0)
            //		if(....)
            //		{
            //			//Calculates x and y with respect to the center of the
            //game
            //			// x = ...
            //			// y = ...
            //
            //			//Calculate the radius (distance to the center)
            //			// radius = ...
            //
            //			//Check if any of the buttons has been touched
            //			if(....)	//RED touched
            //				if(active_button == RED) active_button = NONE;
            //			if(....) //BLUE touched
            //				if(active_button == BLUE) active_button = NONE;
            //			if(....) //GREEN touched
            //				if(active_button == GREEN) active_button = NONE;
            //			if(....) //YELLO touched
            //				if(active_button ==YELLOW) active_button = NONE;
            //		}
            /*********************************************/


            if (active_button == NONE)
                {
                    // End of the game (Stop Time Timer)
                    if (hits == 0)
                        {
                            TIMER2_CR &= ~TIMER_ENABLE;
                            last = active_button;
                        }
                    else
                        // Look for another random button different to the last
                        // one
                        {
                            int temp = rand() % 4;
                            if (temp != last)
                                {
                                    hits--;
                                    last = active_button = temp;
                                }
                        }
                    // Reset the colors to the dark ones
                    BG_PALETTE_SUB[1]  = ARGB16(1, 0, 20, 0);
                    BG_PALETTE_SUB[17] = ARGB16(1, 20, 0, 0);
                    BG_PALETTE_SUB[33] = ARGB16(1, 20, 20, 0);
                    BG_PALETTE_SUB[49] = ARGB16(1, 0, 0, 20);
                }
            swiWaitForVBlank();
        }
}
