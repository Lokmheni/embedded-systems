#include "timer_management.h"
#include "game.h"

//Number of timer ticks (periods of 100 ms) passed
int timer_ticks;

void initTimer() {
	// Initialize timer_ticks
	timer_ticks = 0;

	// Configure timer to trigger an interrupt every 250 ms
	//...TO COMPLETE EXERCISE 2
	TIMER0_CR = TIMER_ENABLE | TIMER_DIV_256 | TIMER_IRQ_REQ;
	TIMER_DATA(0) = TIMER_FREQ_256(4);

	// Associate the ISR (timerISR) to the interrupt line and enable it
	//...TO COMPLETE EXERCISE 2
	irqSet(IRQ_TIMER0, &timerISR);
	irqEnable(IRQ_TIMER0);
}

void timerISR() {
	//Every 2 seconds this ISR calls the function changeColor() that changes
	//the color of the upper screen
	//...TO COMPLETE EXERCISE 2
	timer_ticks += 1;
	if(timer_ticks == 8) {
		changeColor();
		timer_ticks = 0;
	}
}

