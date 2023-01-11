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

/*enum BUFFER_TYPE
{
    MAIN,
    SUB,
}bT;

int x = 2; x2 = 122; y = 2;

u16* P_Graphics_mainBuffer;
u16* P_Graphics_subBuffer;
u16 color = RED;*/

int main(void)
{
    consoleDemoInit();
    oamInit(&oamMain, SpriteMapping_1D_32, false);
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
       	}
    //health();

    while(1) {
    	updateChrono();
    	swiWaitForVBlank();
    	oamUpdate(&oamMain);
    }
}



/*void health(){
	//Engine and background configuration
	bT = MAIN;
	DrawHorizontalLine(bT, x, x2, y, color);
}

void P_Graphics_setup_main()
{
#ifdef FB0
	//Graphics (Part 1)
	//Set the mode to FB0
	REG_DISPCNT = MODE_FB0;

	//Set the corresponding VRAM bank
	VRAM_A_CR = VRAM_ENABLE		//Enable the Bank
			| VRAM_A_LCD;		//Assign it to the Main engine in FB0

#endif

#ifdef ROTOSCALE
	//Graphics (Part 2)
	//Enable a proper RAM memory bank for the main engine
	VRAM_A_CR = VRAM_ENABLE //Enable
			| VRAM_A_MAIN_BG; //Bank for the main engine

	//Configure the main engine in mode 5 (2D) and activate Background 2
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;


	//Enable a proper RAM memory bank for sub engine
	VRAM_C_CR = VRAM_ENABLE
			| VRAM_C_SUB_BG;
	//Configure the sub engine in mode 5 (2D) and activate Background 2
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;
#endif

#ifdef TILES
	//Graphics (Part 3)
#endif
}



void DrawHorizontalLine(enum BUFFER_TYPE bT, int x, int x2, int y, u16 color)
{
	int col;
	if(bT == MAIN) //Check that we want to use the Main engine
	if(y >= 0 && y <=191)	//Check the boundaries of y
		if(x >=0 && x <= 255)	//Check the boundaries of x
			if(x2 >=0 && x2 <=255)	//Check the boundaries of x2
				for(col = x; col < x2; col++)	//For columns from x to x2
					P_Graphics_mainBuffer[y*256 + col] = color;	//Assign the color
}
*/






