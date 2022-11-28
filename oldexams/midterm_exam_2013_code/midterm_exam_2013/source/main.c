#include <nds.h>
#include "graphics_main.h"
#include "graphics_sub.h"
#include "timer_management.h"
#include "game.h"

void exercise_1() {
	// Configure the MAIN graphical engine
	configureGraphics_Main();
	// Display the four colors in the four regions
	fillRegion_Main(0, RED);
	fillRegion_Main(1, GREEN);
	fillRegion_Main(2, BLUE);
	fillRegion_Main(3, YELLOW);
}

void exercise_2() {
	// Configure the SUB graphical engine
	configureGraphics_Sub();
	// Configure backgrounds BG2 and BG0
	configBG2_Sub();
	configBG0_Sub();
}

void exercise_3() {
	// Configure the timer
	configureTimer();
}


void exercise_4() {
	// Touched region
	int touched_region;

	// Game initialization
	initGame();

	while(1) {
		// Check if the touchscreen has been touched
		// if YES, read the coordinates and identify the touched_region (0,1,2 or 3)
		// if NO, set the touched_region to any different value (e.g. -1)
		//...TO COMPLETE EXERCISE 4
		touchPosition touch;
		touchRead(&touch);
		if(touch.px || touch.py) {
			if(touch.px < 64) {
				touched_region = 0;
			}
			if(touch.px < 128) {
				touched_region = 1;
			}
			if(touch.px < 192) {
				touched_region = 2;
			}
			if(touch.px < 256) {
				touched_region = 3;
			}
		} else {
			touched_region = -1;
		}

		// If a region is touched, try the corresponding color in the secret sequence
		switch(touched_region) {
			case 0: tryColor(RED); break;
			case 1: tryColor(GREEN); break;
			case 2: tryColor(YELLOW); break;
			case 3: tryColor(BLUE); break;
		}
		swiWaitForVBlank();
	}
}


int main(void) {
	// EXERCISE 1: Uncomment the following line
	exercise_1();

	// EXERCISE 2: Uncomment the following line (DO NOT comment the previous ones)
//	exercise_2();

	// EXERCISE 3: Uncomment the following line (DO NOT comment the previous ones)
	exercise_3();

	// EXERCISE 4: Uncomment the following line (DO NOT comment the previous ones)
	exercise_4();

	while(1)
		swiWaitForVBlank();
}
