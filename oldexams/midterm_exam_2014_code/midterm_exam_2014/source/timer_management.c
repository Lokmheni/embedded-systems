#include "timer_management.h"
#include "game.h"

//Number of timer ticks (periods of 100 ms) passed
int timer_ticks;

void initTimer() {
	// Initialize timer_ticks
	timer_ticks = 0;

	// Configure timer to trigger an interrupt every 100 ms
	//... TO COMPLETE EXERCISE 3
	TIMER_DATA(0) = TIMER_FREQ_64(10);
	TIMER0_CR = TIMER_ENABLE | TIMER_DIV_64 | TIMER_IRQ_REQ;

	// Associate the ISR (timerISR) to the interrupt line and enable it
	//... TO COMPLETE EXERCISE 3
	irqSet(IRQ_TIMER0, &timerISR);
	irqEnable(IRQ_TIMER0);
}

void timerISR() {
	// Disable the timer when 1.5 seconds have passed and call the function
	// playerLoses() to finish the game (player did not play on time)
	//... TO COMPLETE EXERCISE 3
	timer_ticks += 1;
	if(timer_ticks>=15) {
		irqDisable(IRQ_TIMER0);
		playerLoses();
	}
}


