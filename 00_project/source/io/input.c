/**
 * @file input.c
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 1.0
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "input.h"
#include "sound.h"
#include "../graphics/graphics.h"
#include "../game/game_controller.h"
#include "../settings.h"
#include <nds.h>
#include <stdio.h>


int rand_ticks;

void get_input(RequestedAction* action, RequestedMovement* movement) {

	int keys;
	scanKeys();
	keys = keysHeld();

	if(keys & KEY_LEFT)
		*movement = REQ_MOVE_LEFT;

	else if(keys & KEY_RIGHT)
		*movement = REQ_MOVE_RIGHT;

	else *movement = REQ_MOVE_NONE;




	if(keys & KEY_X)
		*action = REQ_ACTION_JUMP;

	else if(keys & KEY_A)
		*action = REQ_ACTION_ATTACK;

	else if(keys & KEY_Y)
		*action = REQ_ACTION_BLOCK;

	else if(keys & KEY_B)
		*action = REQ_ACTION_SPECIAL_ATTACK;

	else
		*action = REQ_ACTION_NONE;

}


int get_keys(){
	//Position
	int keys;
	//Read held keys
	scanKeys();
	keys = keysHeld();
	if((keys & KEY_RIGHT)  || (keys & KEY_DOWN)|| (keys & KEY_LEFT) || (keys & KEY_UP) || (keys & KEY_TOUCH) )
		return keys;
	else
		return 0;
}


bool get_touch_input(TouchInput* touchinput) {
	*touchinput = TOUCH_INPUT_NONE;
	while(1){
		//Read the touchscreen position
		touchPosition touch;
		touchRead(&touch);
		scanKeys();
		int keys = keysHeld();
		//If touched, set the background in main
		if((keys & KEY_TOUCH)){
			int x = touch.px;
			int y = touch.py;
			if((x > 78 && x < 178) && (y > 75 && y < 75+21)){
				*touchinput = TOUCH_INPUT_SINGLE_PLAYER;
				return 1;
			}
			if((x > 78 && x < 178) && (y > 75+21 && y < 75+42)){
				*touchinput = TOUCH_INPUT_MULTI_PLAYER;
				return 1;
			}

		}
	}
}

bool get_touch_to_restart(TouchInput* touchinput) {
		while(1){
			//Read the touchscreen position
			touchPosition touch;
			touchRead(&touch);
			scanKeys();
			int keys = keysHeld();
			//If touched, set the background in main

			if((keys & KEY_TOUCH) /*&& set_up*/){
				int x = touch.px;
				int y = touch.py;
				if((x > 78 && x < 178) && (y > 75 && y < 75+21)){
					*touchinput = TOUCH_INPUT_PLAY;
					//selected_game_mode(*touchinput);
					//set_up = false;
					//init_screens();
					return 1;
				}
		}
	}
}

bool get_key_to_continue(){
	int keys;
	//Read held keys
	scanKeys();
	keys = keysHeld();
	while(1){
		if((keys & KEY_A))
			return 1;
		else
			return 0;
	}
}



