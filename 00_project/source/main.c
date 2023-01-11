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

/************************
 * Macros for the colors
 ***********************/
#define	RED ARGB16(1,31,0,0)
#define GREEN ARGB16(1,0,31,0)
#define	BLUE ARGB16(1,0,0,31)
#define	YELLOW ARGB16(1,31,31,0)
#define	LIGHT_BLUE ARGB16(1,0,31,31)
#define	WHITE ARGB16(1,31,31,31)
#define	BLACK ARGB16(1,0,0,0)


// Different color tiles
u8 TransTile[64] =
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};
u8 GreenTile[64] =
{
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1
};

u8 BlueTile[64] =
{
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2
};

u8 WhiteTile[64] =
{
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3
};

u8 BlackTile[64] =
{
	4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4
};

u8 RedTile[64] =
{
	5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,
	5,5,5,5,5,5,5,5,
};


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
        //show_health();
        show_timer();
        init_main_screen();

        sprite_initializer(t,s);
        sprite_pos_remote(s);
        sprite_pos_local(t);
    }
    //show_timer();
    //init_screens();
    //show_health();

    while(1) {

    	updateChrono();
    	swiWaitForVBlank();
    	oamUpdate(&oamMain);
    }
}


void show_health(){
	// 1) VRAM configuration for SUB engine
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
	// 2) SUB engine configuration in tiled mode
	REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE;
	// 3) Configure the background
	BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);
	// 4) Copy the 4 tiles to the tile base

	//swiCopy(TransTile, &BG_TILE_RAM_SUB(1)[0], 32);
	swiCopy(GreenTile, &BG_TILE_RAM_SUB(1)[32], 32);
	swiCopy(BlueTile, &BG_TILE_RAM_SUB(1)[64], 32);
	swiCopy(WhiteTile, &BG_TILE_RAM_SUB(1)[96], 32);
	swiCopy(BlackTile, &BG_TILE_RAM_SUB(1)[128], 32);
	swiCopy(RedTile, &BG_TILE_RAM_SUB(1)[160], 32);
	// 5) Initialize the palette (5 components)
	//BG_PALETTE_SUB[0] = TRANS;
	BG_PALETTE_SUB[1] = GREEN;
	BG_PALETTE_SUB[2] = BLUE;
	BG_PALETTE_SUB[3] = WHITE;
	BG_PALETTE_SUB[4] = BLACK;
	BG_PALETTE_SUB[5] = RED;
	// 6) Generate the map
	int i,j, tile;
	/*	for(i = 0; i < 32; i++){
			for(j = 0; j < 24; j++)
				BG_MAP_RAM_SUB(25)[j*32+i] = 0;
		}*/

	for(tile = 0; tile <1024; tile++)
		BG_MAP_RAM_SUB(0)[tile] = 0;

	for(j = 3; j < 5; j++){
		for(i = 4; i < 12; i++)
			BG_MAP_RAM_SUB(0)[j*32+i] = 1;
		for(i = 20; i < 28; i++)
			BG_MAP_RAM_SUB(0)[j*32+i] = 2;
	}
}









