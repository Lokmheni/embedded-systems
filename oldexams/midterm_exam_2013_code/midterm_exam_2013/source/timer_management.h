#ifndef TIMER_MANAGEMENT_H_
#define TIMER_MANAGEMENT_H_
#include <nds.h>
#include "game.h"

/*
 * configureTimer:
 * configures a timer in order to trigger an interrupt every 100 ms
 * and associates the interrupt service routine timerISR() to that
 * line
 */
void configureTimer();

/*
 * timerISR:
 * Interrupt Service Routine of the timer. When 2 seconds have passed,
 * it disables the timer and hides the color sequence from the upper
 * screen with a call to hideColorSequence()
 */
void timerISR();

#endif /* TIMER_MANAGEMENT_H_ */
