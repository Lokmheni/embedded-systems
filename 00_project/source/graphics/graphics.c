/**
 * @file graphics.c
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "graphics.h"
#include <nds.h>
#include "paysage.h"
#include "player.h"
#include "play_mode.h"
#include "player2.h"
#include "../io/input.h"
#include "../settings.h"
#include "streetfighter.h"
#include <math.h>
#include "numbers.h"
#include "string.h"
#include "chrono_display.h"
#include "gameover.h"
#include "health.h"

#include "../game/game_controller.h"

#define	SPRITE_WIDTH	32
#define	SPRITE_HEIGHT	32


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

int min = 0, sec = 0, msec = 0, /*time_remaining,*/ time_round = 1000*20; // 120 seconds for each round

int colore_cornice;

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
	int i,j;
	/*	for(i = 0; i < 32; i++){
			for(j = 0; j < 24; j++)
				BG_MAP_RAM_SUB(25)[j*32+i] = 0;
		}*/

	//for(tile = 0; tile <1024; tile++)
	//	BG_MAP_RAM_SUB(0)[tile] = 0;

		for(j = 2; j < 6; j++){
			if(j == 2 || j == 5){
					for (i = 3; i < 14; i++)
						BG_MAP_RAM_SUB(0)[j*32+i] = colore_cornice;
					for (i = 19; i < 30; i++)
						BG_MAP_RAM_SUB(0)[j*32+i] = colore_cornice;
				}
			else{
				for(i = 3; i < 14; i++)
					if(i == 3 || i == 13)
						BG_MAP_RAM_SUB(0)[j*32+i] = colore_cornice;
					else
						BG_MAP_RAM_SUB(0)[j*32+i] = 1;
				for(i = 19; i < 30; i++)
					if(i == 19 || i == 29)
						BG_MAP_RAM_SUB(0)[j*32+i] = colore_cornice;
					else
						BG_MAP_RAM_SUB(0)[j*32+i] = 1;
			}
		}
	}

void updateChrono(){
	updateChronoDisp(BG_MAP_RAM_SUB(0), min, sec, msec);
	show_health();
}

void ISR_TIMER0(){
	int time_remaining = set_time_remaining(min, sec, msec);
	if(time_remaining > 0){
		msec = (msec + 1)%1000;
		if(msec == 0)
		{
			sec = (sec+1) % 60;
			if(sec == 0)
				min++;
		}
		if(time_remaining < 10*1000){
			colore_cornice = 2;
			//The background color is ste to BLACK and the digits color is set to RED
			changeColorDisp(BLACK, RED);
		}
		else{
			colore_cornice = 4;
			changeColorDisp(WHITE, BLACK);
		}
		//updateChronoDisp(BG_MAP_RAM_SUB(0), min, sec, msec);
	}
	else
		gameover();
}


void init_screens(){
	// Configure the SUB engine in Rotoscale Mode
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE |  DISPLAY_BG3_ACTIVE;
	// Configure the corresponding VRAM memory bank correctly
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
	// Configure background BG2 in rotoscale mode using 8bit pixels
	BGCTRL_SUB[2] = BG_BMP_BASE(0) | BG_BMP8_256x256;
	BGCTRL_SUB[3] = BG_BMP_BASE(1) | BG_BMP8_256x256;

	// 1) VRAM Configuration for MAIN engine
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	// 2) Main engine configuration in rotoscale mode
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG0_ACTIVE;
	// 3) Configure the background
	BGCTRL[2] = BG_BMP_BASE(0) | BG_BMP8_256x256;

	show_logo();
	init_sub_screen();
}

void init_sub_screen() {
	// Transfer image and palette to the corresponding memory locations
	swiCopy(play_modeBitmap, BG_GFX_SUB, play_modeBitmapLen/2);
	swiCopy(play_modePal, BG_PALETTE_SUB, play_modePalLen/2);
	// Set up affine matrix
	REG_BG2PA_SUB = 256;
	REG_BG2PC_SUB = 0;
	REG_BG2PB_SUB = 0;
	REG_BG2PD_SUB = 256;
}


void show_logo(){
	// Transfer image and palette to the corresponding memory locations
	swiCopy(streetfighterBitmap, BG_GFX, streetfighterBitmapLen/2);
	swiCopy(streetfighterPal, BG_PALETTE, streetfighterPalLen/2);
	//Affine Marix Transformation
	#ifndef	NEW_LIBNDS_VERSION
		bgTransform[2]->xdx = 1*256;
		bgTransform[2]->ydx = 0*256;
		bgTransform[2]->xdy = 0*256;
		bgTransform[2]->ydy = 1*256;
		bgTransform[2]->dx = 0*256;
		bgTransform[2]->dy = 0*256;
	#else
		bgTransform[2]->hdx = 1*256;
		bgTransform[2]->vdx = 0*256;
		bgTransform[2]->hdy = 0*256;
		bgTransform[2]->vdy = 1*256;
		bgTransform[2]->dx = 0*256;
		bgTransform[2]->dy = 0*256;
	#endif
}


void init_main_screen(Player* t){
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG0_ACTIVE;
	//Activate and configure VRAM bank to work in background mode
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	VRAM_G_CR = VRAM_ENABLE | VRAM_G_MAIN_SPRITE_0x06400000;
	//BG0 configuration for the background
	BGCTRL[0] = BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_32x32;
	//Copy data to display background (tiles, palette and map)
	swiCopy(paysageTiles, BG_TILE_RAM(1), paysageTilesLen/2);
	swiCopy(paysagePal, BG_PALETTE, paysagePalLen/2);
	swiCopy(paysageMap, BG_MAP_RAM(0), paysageMapLen/2);
	//sprite_pos_local(t);
	//sprite_pos_remote(t);
}

void show_timer(){

	//Enable a suitable VRAM block and map it to the sub engine
	VRAM_H_CR = VRAM_ENABLE
			| VRAM_H_SUB_BG;
	//Configure the engine in Mode 0 and use the BG0
	REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE;
	//Configure the engine to be used as a 32x32 grid of tiles of 256 colors
	BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

	//Copy the tiles and the palette to the corresonding location
	swiCopy(numbersTiles, BG_TILE_RAM_SUB(1), numbersTilesLen);
	swiCopy(numbersPal, BG_PALETTE_SUB, numbersPalLen);

	manage_timer();
}



void manage_timer(){
	//min = sec = msec = 0;
	TIMER_DATA(0) = TIMER_FREQ_1024(1000);
	TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqSet(IRQ_TIMER0, &ISR_TIMER0);
	irqEnable(IRQ_TIMER0);
}

//void change_background() {}

//void set_background(int new_background) {}

int set_time_remaining(int min, int sec, int msec){
	int time_passed = 1000*60*min + 1000*sec + msec;
	//time_remaining = time_round - time_passed;
	return time_round - time_passed;;
}

void show_settings(int games_played, int games_won){
	printf("\n\nGames Played : %d", games_played);
	printf("\n\nGames Won : %d", games_won);
}


void sprite_pos_local(Player* const player) {

	// Set up memory bank to work in sprite mode (offset since we are using VRAM
    // A for backgrounds)
	//VRAM_G_CR = VRAM_ENABLE | VRAM_G_MAIN_SPRITE_0x06400000;

	u16* gfx;
	//u16* gfx1;


	// Initialize sprite manager and the engine
	//oamInit(&oamMain, SpriteMapping_1D_32, true);
	// Allocate space for the graphic to show in the sprite
	gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	//gfx1 = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	dmaCopy(playerTiles, gfx, playerTilesLen);

	bool remote;
  // while (1)
   //{
	   set_stage();
	   //swiWaitForVBlank();
	   wifi_announce_lfg();
	   WifiMsg msg;
	   if (msg.msg == WIFI_REQ_LFG)
	   {
		   send_ctrl_instruction(START_GAME | IS_PLAY | SET_STAGE | RESET_GAME, 0, 0);
		}
		reset_game(remote);
		u32 keys;
		//while (1) // game
		//{
			RequestedAction   a;
			RequestedMovement m;
			a = REQ_ACTION_NONE;
			scanKeys();
			keys = keysHeld();
			if (keys & KEY_A)
			{
				a = REQ_ACTION_JUMP;
			//	printf("Key pressed A\n");
			}
			if (keys / KEY_Y)
			{
				a = REQ_ACTION_BLOCK;
				//printf("Key pressed Y\n");
			}
			if (keys & KEY_X)
			{
				a = REQ_ACTION_ATTACK;
			}
			m = REQ_MOVE_NONE;
			if (keys & KEY_LEFT)
			{
				m = REQ_MOVE_LEFT;
				//printf("Key pressed left\n");
			}
			if (keys & KEY_RIGHT)
			{
				m = REQ_MOVE_RIGHT;
				//printf("Key pressed right\n");
			}

			if (receive_messages(&msg))
			{
				//printf("received wifi msg\n");
				update_game_complete(a, m, msg);
			}
			else
			{
				msg.msg = WIFI_NULL_MSG;
				update_game_complete(a, m, msg);
			}
			Player l = get_player_local();
			send_status(&l);
			oamSet(&oamMain, // oam handler
			   0,        // Number of sprite
			   get_player_local().pos_x,
			   get_player_local().pos_y, // Coordinates
			   0,                          // Priority
			   0,                          // Palette to use
			   SpriteSize_32x32,           // Sprite size
			   SpriteColorFormat_256Color, // Color format
			   gfx,          // Loaded graphic to display
			   -1,           // Affine rotation to use (-1 none)
			   false,        // Double size if rotating
			   false,        // Hide this sprite
			   false, false, // Horizontal or vertical flip
			   false         // Mosaic
			);

			/*oamSet(&oamMain, // oam handler
				1,        // Number of sprite
				translate_remote_x(get_player_remote().pos_x),
				get_player_remote().pos_y,  // Coordinates
				0,                          // Priority
				1,                          // Palette to use
				SpriteSize_32x32,           // Sprite size
				SpriteColorFormat_256Color, // Color format
				gfx1,         // Loaded graphic to display
				-1,           // Affine rotation to use (-1 none)
				false,        // Double size if rotating
				false,        // Hide this sprite
				false, false, // Horizontal or vertical flip
				false         // Mosaic
			);*/
			// Update the sprites
			swiWaitForVBlank();
			oamUpdate(&oamMain);
		  }
	//}
//}

void sprite_pos_remote(Player* const player){
	//VRAM_G_CR = VRAM_ENABLE | VRAM_G_MAIN_SPRITE_0x06400000;
	//using extended palettes:
	/*vramSetBankF(VRAM_F_LCD);
	dmaCopy(playerPal, &VRAM_F_EXT_PALETTE[0], playerPalLen);
	dmaCopy(player2Pal, &VRAM_F_EXT_PALETTE[1], player2PalLen);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);*/

	u16* gfx1;

	//Initialize sprite manager and the engine
	//oamInit(&oamMain, SpriteMapping_1D_32, false);
	//Allocate space for the graphic to show in the sprite
	gfx1 = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	//Copy data for the graphic (palette and bitmap)
	dmaCopy(player2Pal, SPRITE_PALETTE, player2PalLen);
	dmaCopy(player2Tiles, gfx1, player2TilesLen);

	oamSet(&oamMain, // oam handler
			1,        // Number of sprite
			//translate_remote_x(get_player_remote().pos_x),
			//get_player_remote().pos_y,  // Coordinates
			90,90,
			0,                          // Priority
			1,                          // Palette to use
			SpriteSize_32x32,           // Sprite size
			SpriteColorFormat_256Color, // Color format
			gfx1,         // Loaded graphic to display
			-1,           // Affine rotation to use (-1 none)
			false,        // Double size if rotating
			false,        // Hide this sprite
			false, false, // Horizontal or vertical flip
			false         // Mosaic
		);
	oamUpdate(&oamMain);

}

void sprite_initializer(){
	VRAM_G_CR = VRAM_ENABLE | VRAM_G_MAIN_SPRITE_0x06400000;

	oamInit(&oamMain, SpriteMapping_1D_32, true);

	//using extended palettes:
	vramSetBankF(VRAM_F_LCD);
	dmaCopy(playerPal, SPRITE_PALETTE , playerPalLen);
	dmaCopy(player2Pal, &SPRITE_PALETTE[playerPalLen] , player2PalLen);
	dmaCopy(playerPal, &VRAM_F_EXT_PALETTE[0], playerPalLen);
	dmaCopy(player2Pal, &VRAM_F_EXT_PALETTE[1], player2PalLen);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
}



void gameover(){
	// Configure the SUB engine in Rotoscale Mode
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE |  DISPLAY_BG3_ACTIVE;
	// Configure the corresponding VRAM memory bank correctly
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
	// Configure background BG2 and BG3 in rotoscale mode using 8bit pixels
	BGCTRL_SUB[2] = BG_BMP_BASE(0) | BG_BMP8_256x256;
	BGCTRL_SUB[3] = BG_BMP_BASE(0) | BG_BMP8_256x256;
	swiCopy(gameoverBitmap, BG_GFX_SUB, gameoverBitmapLen/2);
	swiCopy(gameoverPal, BG_PALETTE_SUB, gameoverPalLen/2);
	// Set up affine matrix
	REG_BG3PA_SUB = 256;
	REG_BG3PC_SUB = 0;
	REG_BG3PB_SUB = 0;
	REG_BG3PD_SUB = 256;

}
