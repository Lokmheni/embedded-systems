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

int min, sec, msec;
int x1, y, x2;

int main(void)
{
    consoleDemoInit();
    /*oamInit(&oamMain, SpriteMapping_1D_32, false);
    //gameover();
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
        play_sound_effect(*sound);
        show_timer();
        init_main_screen();
        //sprite_pos_remote(s);
        sprite_pos_local(t);
       	}*/
    health();

    while(1) {
    	updateChronoDisp(BG_MAP_RAM_SUB(0), min, sec, msec);
    	swiWaitForVBlank();
    	oamUpdate(&oamMain);
    }
}


void health(){
	//Engine and background configuration
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	BGCTRL[2] = BG_MAP_BASE(0) | BgSize_B8_256x256;

	//Transfer of the image and the palette to the engine
	memcpy(BG_GFX, healthBitmap, 120*32);
	memcpy(BG_PALETTE, healthPal, healthPalLen);

	//Set the matrix affine transform
	bgTransform[2]->xdx = 256;
	bgTransform[2]->ydy = 256;
	bgTransform[2]->xdy = 0;
	bgTransform[2]->ydx = 0;
}







