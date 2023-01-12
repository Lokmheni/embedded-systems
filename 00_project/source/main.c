/*
 * Template Nintendo DS
 * May 2011
 */

#include <math.h>
#include <nds.h>
#include <stdio.h>

#include "io/sound.h"
#include "game/game_controller.h"
#include "graphics/graphics.h"
#include "numbers.h"
#include "paysage.h"
#include "play_mode.h"
#include "player.h"
#include "player2.h"
#include "streetfighter.h"
#include "string.h"
#include "graphics/chrono_display.h"
#include "health.h"

Player* t;
Player* s;


int main(void)
{
    consoleDemoInit();
    oamInit(&oamMain, SpriteMapping_1D_32, false);
    //gameover();



    play();



    //show_timer();
    //init_screens();
    //show_health();

    while(1) {

    	updateChrono(t, s);
    	swiWaitForVBlank();
    	oamUpdate(&oamMain);
    }
}

void play(){

    (t->pos_x) = 0;
    (t->pos_y) = 90;

    (s->pos_x) = 100;
    (s->pos_y) = 90;
    TouchInput* touchinput;
	SoundEffect* sound;
	if(get_player_local().action == ACTION_TYPE_WALK)
	    *sound = SOUND_EFFECT_MOVE;
	if((get_player_local().action == ACTION_TYPE_NORMAL_ATTACK) || (get_player_local().action == ACTION_TYPE_SPECIAL_ATTACK))
		*sound = SOUND_EFFECT_ATTACK;
	if(get_player_local().action == ACTION_TYPE_JUMP_INPLACE || get_player_local().action == ACTION_TYPE_JUMP_MOVE)
	   	*sound = SOUND_EFFECT_JUMP;
	if(get_player_local().action == ACTION_TYPE_BLOCK_INPLACE || get_player_local().action == ACTION_TYPE_BLOCK_MOVE)
		*sound = SOUND_EFFECT_BLOCK;
	init_sound();
	play_music();

	init_screens();
	bool touch = get_touch_input(touchinput);
	if(touch){

    	//stop_music();
        //play_sound_effect(*sound);
        show_timer();
       /// show_health();
        init_main_screen();
        sprite_initializer();
        sprite_pos_remote(s);
        sprite_pos_local(t);
    }
	//bool touch_restart = get_touch_to_restart(touchinput);
	/*if(touch)
		play();*/
}










