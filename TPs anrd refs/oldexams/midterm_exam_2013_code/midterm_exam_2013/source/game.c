#include "game.h"
#include "graphics_main.h"
#include "graphics_sub.h"
#include "timer_management.h"

int colorSequence[4];
int next_region = 0;

void generateColorSequence() {
	int i, c1, c2, temp;
	for(i = 0; i < 4; i++) {
		c1 = rand() % 4;
		c2 = rand() % 4;
		temp = colorSequence[c1];
		colorSequence[c1] = colorSequence[c2];
		colorSequence[c2] = temp;
	}
}

u16 regionColor(int region) {
	u16 color;

	if((region < 0) || (region > 4))
		return 0;

	switch(colorSequence[region]){
		case 0: color = RED; break;
		case 1: color = GREEN; break;
		case 2: color = YELLOW; break;
		case 3: color = BLUE; break;
	}

	return color;
}

void displayColorSequence() {
	int i;
	for(i = 0; i < 4; i++)
		fillRegion_Main(i, regionColor(i));
}

bool isCorrectColor(int region, u16 color) {
	return regionColor(region) == color;
}

void initGame() {
	int i;
	srand(time(NULL));
	for(i = 0; i < 4; i++)
		colorSequence[i] = i;
	next_region = 0;
	generateColorSequence();
	displayColorSequence();
}

void hideColorSequence() {
	int i;
	for(i = 0; i < 4; i++)
		fillRegion_Main(i, BLACK);
}

void tryColor(u16 color) {
	if(isCorrectColor(next_region, color)) {
		fillRegion_Main(next_region++, color);
	}
	else {
		next_region = 0;
		generateColorSequence();
		displayColorSequence();
		configureTimer();
	}
}


