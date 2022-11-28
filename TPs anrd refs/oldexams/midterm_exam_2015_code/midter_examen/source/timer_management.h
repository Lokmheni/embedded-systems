/////////////////////////////////////////////////////////
////	DO NOT MODIFY THIS FILE
/////////////////////////////////////////////////////////
#ifndef TIMER_MANAGEMENT_H_
#define TIMER_MANAGEMENT_H_
#include <nds.h>

/*
 * initTimer:
 * configures a timer in order to trigger an interrupt every 250 ms
 * and associates the interrupt service routine timerISR() to that
 * line. It also activates the timer
 */
void initTimer();

/*
 * timerISR:
 * Interrupt Service Routine of the timer. This ISR calls every 2
 * seconds the function changeColor() that changes the color of the
 * upper screen
 */
void timerISR();

#endif /* TIMER_MANAGEMENT_H_ */
