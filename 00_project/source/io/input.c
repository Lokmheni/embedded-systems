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
#include "sound.h"
#include "../graphics/graphics.h"
#include <nds.h>
#include <stdio.h>


u16* gfx;

int rand_ticks;

void get_input(RequestedAction* action, RequestedMovement* movement, SoundEffect* sound) {

	int keys;
	while(1){
		//Read held keys
		scanKeys();
		keys = keysHeld();
		if(keys & KEY_LEFT){
			*movement = REQ_MOVE_LEFT;
			*action = REQ_ACTION_NONE;
			*sound = SOUND_EFFECT_MOVE;
		}
		if(keys & KEY_RIGHT){
			*movement = REQ_MOVE_RIGHT;
			*action = REQ_ACTION_NONE;
			*sound = SOUND_EFFECT_MOVE;
		}
		if(keys & KEY_X){
			*movement = REQ_MOVE_NONE;
			*action = REQ_ACTION_JUMP;
			*sound = SOUND_EFFECT_JUMP;
		}
		if(keys & KEY_A){
			*movement = REQ_MOVE_NONE;
			*action = REQ_ACTION_ATTACK;
			*sound = SOUND_EFFECT_ATTACK;
		}
		if(keys & KEY_Y){
			*movement = REQ_MOVE_NONE;
			*action = REQ_ACTION_BLOCK;
			*sound = SOUND_EFFECT_BLOCK;
		}

		if(keys & KEY_B){
			*movement = REQ_MOVE_NONE;
			*action = REQ_ACTION_SPECIAL_ATTACK;
			*sound = SOUND_EFFECT_ATTACK;
		}
	}
}

int get_keys(){
	//Position
	int keys;
	while(1){
		//Read held keys
		scanKeys();
		keys = keysHeld();
		if((keys & KEY_RIGHT)  || (keys & KEY_DOWN)|| (keys & KEY_LEFT) || (keys & KEY_UP) || (keys & KEY_TOUCH) )
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
				set_up = false;
			}
		}
	}
}

