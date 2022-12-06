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
#include "play_mode.h"
#include "paysage.h"
#include "player.h"
#include "input.h"

#define	SPRITE_WIDTH	32
#define	SPRITE_HEIGHT	32

void init_screens(){
	REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;
	init_sub_screen();
}

void init_sub_screen() {
	// Configure the SUB engine in Rotoscale Mode
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;
	// Configure the corresponding VRAM memory bank correctly
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
	// Configure background BG2 in rotoscale mode using 8bit pixels
	BGCTRL_SUB[2] = BG_BMP_BASE(0) | BG_BMP8_256x256;

	// Transfer image and palette to the corresponding memory locations
	swiCopy(play_modeBitmap, BG_GFX_SUB, play_modeBitmapLen/2);
	swiCopy(play_modePal, BG_PALETTE_SUB, play_modePalLen/2);
	// Set up affine matrix
	REG_BG2PA_SUB = 256;
	REG_BG2PC_SUB = 0;
	REG_BG2PB_SUB = 0;
	REG_BG2PD_SUB = 256;
	get_touch_input();
}

void init_main_screen(){
	//Activate and configure VRAM bank to work in background mode
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	//BG0 configuration for the background
	BGCTRL[0] = BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_32x32;

	//Copy data to display background (tiles, palette and map)
	swiCopy(paysageTiles, BG_TILE_RAM(1), paysageTilesLen/2);
	swiCopy(paysagePal, BG_PALETTE, paysagePalLen/2);
	swiCopy(paysageMap, BG_MAP_RAM(0), paysageMapLen/2);
	configureSprites();
}

void configureSprites() {
	u16* gfx;
	//Set up memory bank to work in sprite mode (offset since we are using VRAM A for backgrounds)
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;

	//Initialize sprite manager and the engine
	oamInit(&oamMain, SpriteMapping_1D_32, false);

	//Allocate space for the graphic to show in the sprite
	gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

	//Copy data for the graphic (palette and bitmap)
	swiCopy(playerPal, SPRITE_PALETTE, playerPalLen/2);
	swiCopy(playerTiles, gfx, playerTilesLen/2);
	get_keys();
}


//void sprite_pos_local(PlayerState* const player) {}

//void sprite_pos_remote(PlayerState* const player) {}

void change_background() {}

void set_background(int new_background) {}

void set_time_remaining(int min, int sec, int msec) {}

void show_settings(int games_played, int games_won) {}
