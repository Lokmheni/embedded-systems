/////////////////////////////////////////////////////////
////	DO NOT MODIFY THIS FILE
/////////////////////////////////////////////////////////

#include "game.h"
#include "graphics_main.h"
#include "graphics_sub.h"
#include "timer_management.h"

int current_color = 0;
int playField[48];
int n_buttons = 48;

void changeButton(int button, int value) {
	u16 color;

	switch(value) {
		case 0: color = RED; break;
		case 1: color = GREEN; break;
		case 2: color = BLUE; break;
		case 3: color = YELLOW; break;
		default: color = BLACK;
	}

	playField[button] = value;
	fill_32x32_button((button/8)*32, (button%8)*32, WHITE, color);
}


void initGame() {
	int i;
	srand(time(NULL));
	initTimer();
	changeColor();
	n_buttons = 48;
	for(i=0;i<48;i++)
		changeButton(i,rand()%4);
}

void changeColor() {
	int choice;
	u16 color;

	if (n_buttons > 0)
		do{
			choice = rand() % 4;
		} while(choice == current_color);
	else
		choice = -1;

	current_color = choice;
	switch(choice) {
		case 0: color = RED; break;
		case 1: color = GREEN; break;
		case 2: color = BLUE; break;
		case 3: color = YELLOW; break;
		default: color = BLACK;
	}

	fillScreen_Main(color);
}

void playerPlaysButton(int button) {
	if(playField[button] == current_color) {
		changeButton(button, -1);
		n_buttons--;
	}
	else {
		initGame();
	}
}


