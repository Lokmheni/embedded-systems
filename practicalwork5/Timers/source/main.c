
#include <math.h>
#include <nds.h>
#include <stdio.h>

#include "chrono_display.h"

extern int
iSqrt(int);

// Exercises 2 and 3
int min, sec, msec;
/*
//EX2
void Timer0()
{
    if ( ++msec >= 1000 )
        msec = 0;

    updateChronoDisp_Main( min, sec, msec );
}
void Timer1()
{
    if ( ++sec >= 60 )
        {
            sec = 0;
            min++;
        }
}
*/
// EX3
void
Timer0()
{
    if (++msec >= 1000)
        {
            msec = 0;
            if (++sec >= 60)
                {
                    sec = 0;
                    min++;
                }
        }
    updateChronoDisp_Main(min, sec, msec);
}

int
main(void)
{
    consoleDemoInit();

    // Exercise 1
    /*

    u16 start, end;
    int result;

    // Initialize the timer with the correct configuration
    TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1 | TIMER_IRQ_REQ;

    // Set the TIMER_DATA to 0 (the timer starts to count in 0)
    TIMER_DATA(0) = 0;

    // Read the value of the timer
    start  = TIMER0_DATA;
    result = floor(sqrt((double)start));
    // Read the value of the timer again
    end    = TIMER0_DATA;
    // Print the solution
    printf("double sqrt = %fus\n", 29.838276541e-3 * (end - start));

    // Do the same fot the hand-written square root
    start  = TIMER0_DATA;
    result = iSqrt(start);
    end    = TIMER0_DATA;
    printf("iSqrt = %fus\n", 29.838276541e-3 * (end - start));

    // Exercise 2
    // Initialization of the display
    initChronoDisp_Main();

    // Initialize the interrupts correctly
    irqInit();

    // Set the seconds and mseconds to 0
    min = sec = msec = 0;

    // Configure two timers (i.e.: TIMER0 and TIMER1) correcly
    TIMER_DATA( 0 ) = TIMER_FREQ_1024( 1000 );
    TIMER0_CR       = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
    TIMER_DATA( 1 ) = TIMER_FREQ_1024( 1 );
    TIMER1_CR       = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;

    // Associate the interrupt handlers
    irqSet( IRQ_TIMER0, Timer0 );
    irqSet( IRQ_TIMER1, Timer1 );
    // Enable the interrupt lines of the timers
    irqEnable( IRQ_TIMER0 );
    irqEnable( IRQ_TIMER1 );

    */

    // Exercise 3 (Comment exercise 1 and 2)

    // Initialize the display and the color of the display
    initChronoDisp_Main();
    changeColorDisp_Main(RED);

    // Initialize the interrupts correctly
    irqInit();


    // Set the minutes, the seconds and the mseconds
    min = sec = msec = 0;

    // Configure the timer (i.e. TIMER0) correctly
    TIMER_DATA(0) = TIMER_FREQ_1024(1000);
    TIMER0_CR     = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;

    // Associate the interrupt handler and enable the interrupt line
    irqSet(IRQ_TIMER0, Timer0);
    irqEnable(IRQ_TIMER0);


    /*
        //Exercise 4

        //Associate the interrupt handler for the VBLANK interrupt line
       and enable it
        TODO;
        TODO;
    */

    /*
        //Exercise 5

        //Configure the timer correctly, associate the handler and enable
       the interrupt
        TODO;
        TODO;
        TODO;
        TODO;
    */

    /*
        //Exercise 6

        //Configure the interruption to be fired when button A is pressed
        REG_KEYCNT = (1<<14)| KEY_A;
        //Associate the handler and enable the line of interrupt
        TODO;
        TODO;
    */

    while (1)
        {
            swiWaitForVBlank();
        }
}
