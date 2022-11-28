
#include "irq_management.h"

#include <stdio.h>

// ------ Exercise 2 ------ //

/*
 * IRQ_initialize:
 * configures the timer and IRQs of the system
 */
void IRQ_initialize()
{
    // Configure timer 0 to trigger an interrupt every 1 ms
    TIMER_DATA( 0 ) = TIMER_FREQ_1024( 1000 );  // COULD PROLLY BE OPTIMIZED;
    TIMER0_CR       = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;


    // Countdown timer value decrementing:
    // Associate the ISR (ISR_countdown_timer) to the interrupt
    // line of timer 0 (Do not enable it!)
    irqSet( IRQ_TIMER0, ISR_countdown_timer );

    // Main screen refreshing:
    // Associate the ISR (ISR_VBlank) to the interrupt line VBLANK and enable
    // it
    irqSet( IRQ_VBLANK, ISR_VBlank );
    irqEnable( IRQ_VBLANK );
}


// ------ Exercise 4 ------ //


// Initial value of the countdown timer (in sec)
// (set by the user before starting the countdown)
uint32 sec_init = 0;  // Reset

// Current value of the countdown timer (in mini-sec, sec and min)
uint32 min = 0, sec = 0, msec = 0;  // Reset

// Countdown timer states list
enum
{
    STOP,
    PLAY,
    PAUSE
};

// Countdown timer state
u8 countdown_state = STOP;  // Initial state


/*
 * This function handles the input by monitoring the keys and the touchscreen.
 */
void handleInput()
{
    // Scan the keys
    scanKeys();

    /* Identify the keys and map the action according to the instructions
     * presented in the exam sheet. */
    u32           k = keysDown();
    touchPosition touch;
    touchRead( &touch );

    // If the arrows have been touched and  countdown_state is STOP
    if ( ( ( k & KEY_UP ) || ( k & KEY_DOWN ) ) && countdown_state == STOP )
        {
            // Save the initial value of the countdown timer in seconds
            if ( sec_init < 59 * 60 + 30 && k & KEY_UP )
                {
                    if ( sec == 30 )
                        {
                            sec = 0;
                            min += 1;
                        }
                    else
                        {
                            sec = 30;
                        }
                }
            if ( k & KEY_DOWN && ! ( sec == 0 && min == 0 ) )
                {
                    if ( sec == 0 )
                        {
                            sec = 30;
                            min -= 1;
                        }
                    else
                        {
                            sec = 0;
                        }
                }


            sec_init = sec + min * 60;
        }
    else if ( touch.px && touch.py )  // The touchscreen has been touched
        {
            // Call the touch-handling function of Exercise 5: handleTouchPad()
            handleTouchPad();
        }
}


// ------ Exercise 5 ------ //

/*
 * This function handles the touchscreen.
 */
void handleTouchPad()
{
    // Read the touch position (structure).
    touchPosition touch;
    touchRead( &touch );

    /* Get the coordinates of the touched position:
       ▪ If STOP (square) button/region touched:
         - Disable the countdown timer IRQ (IRQ_TIMER0).
         - Reset timer value to zero.
         - Change the state of "countdown_state".
         - Set background color to WHITE and the digits color to BLACK on the
       MAIN screen, with the function: changeMainColorDisp(uint16 bg_color,
       uint16 digit_color). ▪ If PLAY (triangle) button/region touched:
         - Start countdown timer by enabling its IRQ (IRQ_TIMER0).
         - Change the state of "countdown_state".
         - Set background color to YELLOW and the digits color to BLACK on the
       MAIN screen, with the function: changeMainColorDisp(uint16 bg_color,
       uint16 digit_color). ▪ If PAUSE (double bars) button/region touched:
         - Pause countdown timer by disabling its IRQ (IRQ_TIMER0).
         - Change the state of "countdown_state".
         - Set background color to GREEN and the digits color to BLACK on the
       MAIN screen, with the function: changeMainColorDisp(uint16 bg_color,
       uint16 digit_color). ▪ If the touch position is not in one of those 3
       regions, do nothing.
    */

    // If we are in the region of the 3 buttons (STOP, PLAY and PAUSE),
    // perform the actions presented above.
    //... TO COMPLETE EXERCISE 5
    if ( touch.px > 187 && touch.px < 187 + 39
         && ! ( touch.py < 35 || touch.py > 192 - 25 ) )
        {
            if ( touch.py < 35 + 38 + 2 )  // stop
                {
                    irqDisable( IRQ_TIMER0 );
                    min             = 0;
                    sec             = 0;
                    msec            = 0;
                    countdown_state = STOP;
                    changeMainColorDisp( WHITE, BLACK );
                }
            else if ( touch.py < 35 + 2 * 38 + 6 )  // play
                {
                    irqEnable( IRQ_TIMER0 );
                    countdown_state = PLAY;
                    changeMainColorDisp( YELLOW, BLACK );
                }
            else  // pause
                {
                    irqDisable( IRQ_TIMER0 );
                    countdown_state = PAUSE;
                    changeMainColorDisp( GREEN, BLACK );
                }
        }
}


/////////////////////////////////////////////////////////
////	DO NOT MODIFY THE FUNCTION BELOW
/////////////////////////////////////////////////////////

/*
 * ISR_countdown_timer:
 * Interrupt Service Routine of the timer.
 * After each 1 ms, it decrements the countdown timer.
 */
void ISR_countdown_timer()
{
    if ( msec || sec
         || min )  // if the countdown timer did not reach 00:00.000
        {
            if ( ! msec && ( sec || min ) )
                {
                    msec = 999;  // Reset to the max of the ms range
                    if ( ! sec )
                        {
                            sec = 59;  // Reset to the max of the sec range
                            if ( min )
                                min--;  // Decrement 1 minutes
                        }
                    else
                        sec -= 1;  // Decrement 1 seconds
                }
            else
                msec -= 1;  // Decrement 1 ms
        }
    else  // Countdown finished!!!
        {
            // Change the color of the MAIN screen
            changeMainColorDisp( RED, WHITE );

            // Disable the Timer IRQ
            irqDisable( IRQ_TIMER0 );
        }
}

/////////////////////////////////////////////////////////
////	DO NOT MODIFY THE FUNCTION BELOW
/////////////////////////////////////////////////////////

/*
 * ISR_VBlank:
 * Interrupt Service Routine of the screens, to refresh them properly.
 */
void ISR_VBlank()
{
    // Handles the inputs (keys / touchscreen)
    handleInput();

    // Update the time value printed on the MAIN screen
    updateTimerDisp( BG_MAP_RAM( 0 ), min, sec, msec );

    // Update the rotation angle of the countdown timer's hand
    updateClkHandPosition( sec_init, min * 60 + sec );
}
