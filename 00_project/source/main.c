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

int min, sec, msec;
int x1, y, x2;

int main(void)
{
    consoleDemoInit();
    oamInit(&oamMain, SpriteMapping_1D_32, false);
    //gameover();
    init_sound();
    play_music();

    Player* t;
    Player* s;

    (t->pos_x) = 0;
    (t->pos_y) = 90;

    (s->pos_x) = 100;
    (s->pos_y) = 90;


    init_screens();
    bool touch = get_touch_input();
    if(touch){
    	stop_music();
    	play_sound_effect(SOUND_EFFECT_JUMP);
    	show_timer();
    	init_main_screen();

    	sprite_pos_remote(s);
    	//sprite_pos_local(t);
    }

    while(1) {

    	swiWaitForVBlank();
    	oamUpdate(&oamMain);
    }
}





