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
#include "graphics.h"
#include <nds.h>
#include <stdio.h>


u16* gfx;

void get_input(RequestedAction* action, RequestedMovement* movement) {}

void get_keys(){
	//Position
	int x = 0, y = 192, keys;
	while(1){
		//Read held keys
		scanKeys();
		keys = keysHeld();

		//Modify position of the sprite accordingly
		if((keys & KEY_RIGHT) && (x < (SCREEN_WIDTH - SPRITE_WIDTH))) x+=2;
		if((keys & KEY_DOWN) && (y < (SCREEN_HEIGHT - SPRITE_HEIGHT))) y+=2;
		if((keys & KEY_LEFT) && (x  > 0)) x-=2;
		if((keys & KEY_UP) && (y  > 0)) y-=2;

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
}


void get_touch_input() {
	//Read the touchscreen position
	while(1){
		touchPosition touch;
		touchRead(&touch);
		scanKeys();
		int keys = keysHeld();
		//If touched, set the background in main
		if(keys & KEY_TOUCH){
			int x = touch.px;
			int y = touch.py;

			if((x > 78 && x < 178) && ((y > 75 && y < 75+21) || (y > 75+21 && y < 75+42))){
				init_main_screen();
				REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG3_ACTIVE;
				//REG_DISPCNT_SUB = ~DISPLAY_BG2_ACTIVE;
				show_timer();
			}
		else
			continue;
		}
	}
}
