#include <nds.h>
#include "graphics_main.h"
#include "graphics_sub.h"
#include "timer_management.h"
#include "game.h"

void exercise_1() { //DO NOT modify this function
	configureGraphics_Main();
	fillScreen_Main(MAGENTA);
}

void exercise_2() { //DO NOT modify this function
	initTimer();
}

void exercise_3() {
	configureGraphics_Sub();
	configBG2_Sub();
	fillScreen_Sub(MAGENTA);
}

void exercise_4() { //DO NOT modify this function
	fill_32x32_button(0,0,RED, BLACK);
	fill_32x32_button(80,112,YELLOW, BLACK);
	fill_32x32_button(160,224,BLACK, GREEN);
	fill_32x32_button(180,30,BLUE, YELLOW);
	fill_32x32_button(30,240,BLUE, YELLOW);
	fill_32x32_button(-1,30,BLUE, YELLOW);
	fill_32x32_button(30,-1,BLUE, YELLOW);
}

void exercise_5() {

	// Game initialization -> DO NOT modify this line
	initGame();


	while(1) {
		// Scan the keys that have been pressed down
		//...TO COMPLETE EXERCISE 5
		scanKeys();

		// Check if the player has pressed START
		// In that case restart the game (initGame)
		//...TO COMPLETE EXERCISE 5
		unsigned keys = keysDown();
		swiWaitForVBlank();
		if(keys & KEY_START) {
			initGame();
		}

		// Check if the touchscreen has been touched and if YES get the coordinates
		//Filter if the player has touched a colored square (not a white region) and
		//identify which button has been touched. Call the function playerPlaysButton(..)
		//with the index of the identified button.
		//...TO COMPLETE EXERCISE 5
		touchPosition touch;
		touchRead(&touch);
		if(touch.px || touch.py) {
			int x = touch.px%32;
			int y = touch.py%32;
			int button = -1;
			if((x>=4)&&(x<28)&&(y>=4)&&(y<28)) {
				button = 8*(touch.py/32) + (touch.px/32);
				playerPlaysButton(button);
			}

		}
		swiWaitForVBlank();
	}
}


int main(void) {
	// EXERCISE 1: Uncomment the following line
	exercise_1();

	// EXERCISE 2: Uncomment the following line (DO NOT comment the previous ones)
	exercise_2();

	// EXERCISE 3: Uncomment the following line (DO NOT comment the previous ones)
	exercise_3();

	// EXERCISE 4: Uncomment the following line (DO NOT comment the previous ones)
	exercise_4();

	// EXERCISE 5: Uncomment the following line (DO NOT comment the previous ones)
	exercise_5();

	while(1)
		swiWaitForVBlank();
}
