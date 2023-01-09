/**
 * @file input.c
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "input.h"
#include "../graphics/graphics.h"
#include <nds.h>
#include <stdio.h>


u16* gfx;

int rand_ticks;

void get_input(RequestedAction* action, RequestedMovement* movement) {}

int get_keys(){
	//Position
	int keys;
	while(1){
		//Read held keys
		scanKeys();
		keys = keysHeld();
		if((keys & KEY_RIGHT)  || (keys & KEY_DOWN)|| (keys & KEY_LEFT) || (keys & KEY_UP) || (keys & KEY_TOUCH))
			return keys;
		else
			return 0;
	}
	return 0;
}

void manage_key(int keys){
	int x = 0, y = 192;
	//Modify position of the sprite accordingly
	if((keys & KEY_RIGHT)  || (keys & KEY_DOWN)|| (keys & KEY_LEFT) || (keys & KEY_UP)){
		if((keys & KEY_RIGHT) && (x < (SCREEN_WIDTH - SPRITE_WIDTH))) x+=2;
		if((keys & KEY_DOWN) && (y < (SCREEN_HEIGHT - SPRITE_HEIGHT))) y+=2;
		if((keys & KEY_LEFT) && (x  > 0)) x-=2;
		if((keys & KEY_UP) && (y  > 0)) y-=2;
	}

	oamSet(&oamMain, 	// oam handler
			0,				// Number of sprite
			x, y,			// Coordinates
			0,				// Priority
			0,				// Palette to use
			SpriteSize_32x32,			// Sprite size
			SpriteColorFormat_256Color,	// Color format
			gfx,			// Loaded graphic to display
			-1,				// Affine rotation to use (-1 none)
			false,			// Double size if rotating
			false,			// Hide this sprite
			false, false,	// Horizontal or vertical flip
			false			// Mosaic
	);
	swiWaitForVBlank();
	//Update the sprites
	oamUpdate(&oamMain);
}

bool get_touch_input() {
	bool set_up = true;
	while(1){
		//Read the touchscreen position
		touchPosition touch;
		touchRead(&touch);
		scanKeys();
		int keys = keysHeld();
		//If touched, set the background in main

		if((keys & KEY_TOUCH) && set_up){
			int x = touch.px;
			int y = touch.py;
			if((x > 78 && x < 178) && ((y > 75 && y < 75+21) || (y > 75+21 && y < 75+42))){
				return 1;
				//printf("Lokman");
				//show_timer();
				//init_main_screen();
				set_up = false;
			}
		}
	}
}


/*int get_input(){
	int keys;
	while(1){
	//Read held keys
		scanKeys();
		keys = keysHeld();
		if((keys & KEY_RIGHT)  || (keys & KEY_DOWN)|| (keys & KEY_LEFT) || (keys & KEY_UP) || (keys & KEY_TOUCH))
			return keys;
		else
			continue;
	}
	return 0;
}*/
