/**
 * @file graphics.c
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 1.0
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "graphics.h"

#include "paysage.h"
#include "player.h"
#include "play_mode.h"
#include "player2.h"
#include "streetfighter.h"
#include "numbers.h"
#include "chrono_display.h"
#include "gameover.h"
#include "health.h"
#include "youwin.h"
#include "youlose.h"
#include "statistics.h"
#include "player_attack_normal.h"
#include "player_attack_special.h"
#include "player2_attack_normal.h"
#include "player2_attack_special.h"

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

u8 YellowTile[64] =
{
	6,6,6,6,6,6,6,6,
	6,6,6,6,6,6,6,6,
	6,6,6,6,6,6,6,6,
	6,6,6,6,6,6,6,6,
	6,6,6,6,6,6,6,6,
	6,6,6,6,6,6,6,6,
	6,6,6,6,6,6,6,6,
	6,6,6,6,6,6,6,6,
};

int min = 0, sec = 0, msec = 0, time_round = 1000*60*2; // 120 seconds for each round

int colore_cornice;

u16 *gfx, *gfx1, *gfx_atk, *gfx_spc,*gfx1_atk,*gfx1_spc;

bool timer_timeout;

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
	}
	else
        timer_timeout = true;
}

void updateChrono(const Player* t, const Player* s){
	updateChronoDisp(BG_MAP_RAM_SUB(0), min, sec, msec);
	set_healthbars();
	show_health(t, s);
}

void init_screens(){

	// Configure the SUB engine in Rotoscale Mode
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;
	// Configure the corresponding VRAM memory bank correctly
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
	// Configure background BG2 in rotoscale mode using 8bit pixels
	BGCTRL_SUB[2] = BG_BMP_BASE(0) | BG_BMP8_256x256;

	// 1) VRAM Configuration for MAIN engine
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	// 2) Main engine configuration in rotoscale mode
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE; //|  DISPLAY_BG3_ACTIVE ;
	// 3) Configure the background
	BGCTRL[2] = BG_BMP_BASE(0) | BG_BMP8_256x256;
	show_logo();
	init_sub_screen();
}

void init_sub_screen() {
	// Transfer image and palette to the corresponding memory locations
	swiCopy(play_modeBitmap, BG_BMP_RAM_SUB(0), play_modeBitmapLen/2);
	swiCopy(play_modePal, BG_PALETTE_SUB, play_modePalLen/2);
	// Set up affine matrix
	REG_BG2PA_SUB = 256;
	REG_BG2PC_SUB = 0;
	REG_BG2PB_SUB = 0;
	REG_BG2PD_SUB = 256;
}


void show_logo(){
	// Transfer image and palette to the corresponding memory locations
	swiCopy(streetfighterBitmap, BG_MAP_RAM(0), streetfighterBitmapLen/2);
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
	//BG0 configuration for the background
	BGCTRL[0] = BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_32x32;
	//Copy data to display background (tiles, palette and map)
	swiCopy(paysageTiles, BG_TILE_RAM(1), paysageTilesLen/2);
	swiCopy(paysagePal, BG_PALETTE, paysagePalLen/2);
	swiCopy(paysageMap, BG_MAP_RAM(0), paysageMapLen/2);
}

bool get_timer_timeout() {
	return timer_timeout;
}

void show_timer(){
	int i;
	for(i = 0; i < 468*2; i++){
		BG_MAP_RAM_SUB(0)[i] = -1;
	}
	//Configure the engine in Mode 5 and use the BG1
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG1_ACTIVE;
	//Configure the engine to be used as a 32x32 grid of tiles of 256 colors
	BGCTRL_SUB[1] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);
	//Copy the tiles and the palette to the corresonding location
	swiCopy(numbersTiles, BG_TILE_RAM_SUB(1), numbersTilesLen);
	swiCopy(numbersPal, BG_PALETTE_SUB, numbersPalLen);
	manage_timer();
}

void manage_timer(){
	timer_timeout=false;
	min = sec = msec = 0;
	TIMER_DATA(0) = TIMER_FREQ_1024(1000);
	TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqSet(IRQ_TIMER0, &ISR_TIMER0);
	irqEnable(IRQ_TIMER0);
}

int set_time_remaining(int min, int sec, int msec){
	int time_passed = 1000*60*min + 1000*sec + msec;
	return (time_round - time_passed);
}

void show_settings(int games_played, int games_won, int higher_played, int higher_won){
	// Configure the SUB engine in Rotoscale Mode
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE;
	BGCTRL_SUB[2] = BG_BMP_BASE(5) | BG_BMP8_256x256;
	swiCopy(statisticsBitmap, BG_BMP_RAM_SUB(5), statisticsBitmapLen/2);
	swiCopy(statisticsPal, BG_PALETTE_SUB, statisticsPalLen/2);

	int i;
	for(i = 0; i < 468*2; i++){
		BG_MAP_RAM_SUB(0)[i] = -1;
	}

	//int games_played_hundreds = games_played / 100;
	int games_played_dozens = (games_played)/10;
	int games_played_units = (games_played)%10;

	//int games_won_hundreds = games_won / 100;
	int games_won_dozens = (games_won)/10;
	int games_won_units = (games_won)%10;

	int higher_played_hundreds = higher_played / 100;
	int higher_played_dozens = (higher_played%100)/10;
	int higher_played_units = (higher_played%100)%10;

	int higher_won_hundreds = higher_won/ 100;
	int higher_won_dozens = (higher_won%100)/10;
	int higher_won_units = (higher_won%100)%10;

	BGCTRL_SUB[1] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);
	//Copy the tiles and the palette to the corresonding location
	swiCopy(numbersTiles, BG_TILE_RAM_SUB(1), numbersTilesLen);

	u8 pal_l8, pal_h8;
	u16* image = BG_TILE_RAM_SUB(1);
	for(i=0; i<numbersTilesLen/2; i++){
		pal_l8 = (u8) (image[i]);
		pal_h8 = (u8)(image[i] >> 4);
		if(pal_l8 != 0)
			pal_l8 = 0;
		else
			pal_l8 = 2;
		if(pal_h8 != 0)
			pal_h8 = 0;
		else
			pal_h8 = 2;
		image[i] = pal_h8<<4 | pal_l8;
	}

	printDigit(BG_MAP_RAM_SUB(0) , games_played_dozens, 8, 0);
	printDigit(BG_MAP_RAM_SUB(0) , games_played_units, 12, 0);
	printDigit(BG_MAP_RAM_SUB(0) , games_won_dozens, 24, 0);
	printDigit(BG_MAP_RAM_SUB(0) , games_won_units, 28, 0);
	printDigit(BG_MAP_RAM_SUB(0) , higher_played_hundreds, 10, 8);
	printDigit(BG_MAP_RAM_SUB(0) , higher_played_dozens, 14, 8);
	printDigit(BG_MAP_RAM_SUB(0) , higher_played_units, 18, 8);
	printDigit(BG_MAP_RAM_SUB(0) , higher_won_hundreds, 10, 16);
	printDigit(BG_MAP_RAM_SUB(0) , higher_won_dozens, 14, 16);
	printDigit(BG_MAP_RAM_SUB(0) , higher_won_units, 18, 16);
}

void sprite_initializer(){
	VRAM_G_CR = VRAM_ENABLE | VRAM_G_MAIN_SPRITE_0x06400000;
	oamInit(&oamMain, SpriteMapping_1D_32, true);
	//using extended palettes:



    vramSetBankF(VRAM_F_LCD);

#ifndef NEW_LIBNDS_VERSION
    gfx =
        oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(playerTiles, gfx, playerTilesLen);
    dmaCopy(playerPal, &VRAM_F_EXT_PALETTE[0], playerPalLen);


    gfx_atk =
        oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(player_attack_normalTiles, gfx_atk, player_attack_normalTilesLen);
    dmaCopy(player_attack_normalPal, &VRAM_F_EXT_PALETTE[1],
            player_attack_normalPalLen);

    gfx_spc =
        oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(player_attack_specialTiles, gfx_spc, player_attack_specialTilesLen);
    dmaCopy(player_attack_specialPal, &VRAM_F_EXT_PALETTE[2],
            player2_attack_specialPalLen);

    gfx1 =
        oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(player2Tiles, gfx1, player2TilesLen);
    dmaCopy(player2Pal, &VRAM_F_EXT_PALETTE[3], player2PalLen);


    gfx1_atk =
        oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(player2_attack_normalTiles, gfx1_atk,
            player2_attack_normalTilesLen);
    dmaCopy(player2_attack_normalPal, &VRAM_F_EXT_PALETTE[4],
            player2_attack_normalPalLen);

    gfx1_spc =
        oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(player2_attack_specialTiles, gfx1_spc,
            player2_attack_specialTilesLen);
    dmaCopy(player2_attack_specialPal, &VRAM_F_EXT_PALETTE[5],
            player2_attack_specialPalLen);

#else
	gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	dmaCopy(playerTiles, gfx, playerTilesLen);
    dmaCopy(playerPal, &VRAM_F_EXT_SPR_PALETTE[0], playerPalLen);

    gfx_atk = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(player_attack_normalTiles, gfx_atk, player_attack_normalTilesLen);
    dmaCopy(player_attack_normalPal, &VRAM_F_EXT_SPR_PALETTE[1],
            player_attack_normalPalLen);

	gfx_spc = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(player_attack_specialTiles, gfx_spc, player_attack_specialTilesLen);
    dmaCopy(player_attack_specialPal, &VRAM_F_EXT_SPR_PALETTE[2],
            player2_attack_specialPalLen);

	gfx1 = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	dmaCopy(player2Tiles, gfx1, player2TilesLen);
    dmaCopy(player2Pal, &VRAM_F_EXT_SPR_PALETTE[3], player2PalLen);


    gfx1_atk= oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(player2_attack_normalTiles, gfx1_atk, player2_attack_normalTilesLen);
    dmaCopy(player2_attack_normalPal, &VRAM_F_EXT_SPR_PALETTE[4],
            player2_attack_normalPalLen);

	gfx1_spc= oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	dmaCopy(player2_attack_specialTiles, gfx1_spc, player2_attack_specialTilesLen);
	dmaCopy(player2_attack_specialPal, &VRAM_F_EXT_SPR_PALETTE[5],player2_attack_specialPalLen);
#endif

    vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
}

void sprite_pos_local(const Player*  player) {
    u16* _gfx;
    int  pal;

    switch (player->action)
        {
        case ACTION_TYPE_NORMAL_ATTACK:
            _gfx = gfx_atk;
            pal  = 1;
            break;
        case ACTION_TYPE_SPECIAL_ATTACK:
            _gfx = gfx_spc;
            pal  = 2;
            break;
        default:
            _gfx = gfx;
            pal  = 0;
            break;
        }
//idle
	oamSet(&oamMain, // oam handler
		   0,        // Number of sprite
		  player->pos_x,
		  player->pos_y, // Coordinates
		   0,                          // Priority
		   pal,                          // Palette to use
		   SpriteSize_32x32,           // Sprite size
		   SpriteColorFormat_256Color, // Color format
		   _gfx,          // Loaded graphic to display
		   -1,           // Affine rotation to use (-1 none)
		   false,        // Double size if rotating
		   false,        // Hide this sprite
		   player->dir==DIRECTION_LEFT, false, // Horizontal or vertical flip
		   false         // Mosaic
		);


    oamUpdate(&oamMain);
}


void sprite_pos_remote(const Player* player){
    u16* _gfx;
    int  pal;

    switch (player->action)
	{
	case ACTION_TYPE_NORMAL_ATTACK:
        _gfx = gfx1_atk;
        pal  = 4;
        break;
    case ACTION_TYPE_SPECIAL_ATTACK:
        _gfx = gfx1_spc;
        pal  = 5;
        break;
    default:
        _gfx = gfx1;
        pal  = 3;
        break;
    }


    oamSet(&oamMain, // oam handler
			1,        // Number of sprite
			player->pos_x,
			player->pos_y,  // Coordinates
			0,                          // Priority
			pal,                          // Palette to use
			SpriteSize_32x32,           // Sprite size
			SpriteColorFormat_256Color, // Color format
			_gfx,         // Loaded graphic to display
			-1,           // Affine rotation to use (-1 none)
			false,        // Double size if rotating
			false,        // Hide this sprite
			player->dir==DIRECTION_LEFT, false, // Horizontal or vertical flip
			false         // Mosaic
		);

	oamUpdate(&oamMain);
}

void set_healthbars(){
	// 1) VRAM configuration for SUB engine
	//VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE;
	// 3) Configure the background
	BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(3);
	// 4) Copy the tiles to the tile base
	swiCopy(GreenTile, &BG_TILE_RAM_SUB(3)[32], 32);
	swiCopy(BlueTile, &BG_TILE_RAM_SUB(3)[64], 32);
	swiCopy(WhiteTile, &BG_TILE_RAM_SUB(3)[96], 32);
	swiCopy(BlackTile, &BG_TILE_RAM_SUB(3)[128], 32);
	swiCopy(RedTile, &BG_TILE_RAM_SUB(3)[160], 32);
	swiCopy(YellowTile, &BG_TILE_RAM_SUB(3)[192], 32);
    dmaCopy(TransTile, &BG_TILE_RAM_SUB(3)[0], 64);
	// 5) Initialize the palette (5 components)
	BG_PALETTE_SUB[1] = GREEN;
	BG_PALETTE_SUB[2] = BLUE;
	BG_PALETTE_SUB[3] = WHITE;
	BG_PALETTE_SUB[4] = BLACK;
	BG_PALETTE_SUB[5] = RED;
	BG_PALETTE_SUB[6] = YELLOW;

	int i;
	for(i = 0; i < 468*2; i++){
		BG_MAP_RAM_SUB(1)[i] = 0;
	}

}

void show_health(const Player *t, const Player* s){
	// 6) Generate the map
	int i,j;
	for(j = 1; j < 6; j++){
		if(j == 1 || j == 5){
			for (i = 2; i < 14; i++)
				BG_MAP_RAM_SUB(1)[j*32+i] = colore_cornice;
			for (i = 19; i < 31; i++)
				BG_MAP_RAM_SUB(1)[j*32+i] = colore_cornice;
			}
		else{
			for(i = 2; i < 14; i++)
				if(i == 2 || i == 13)
					BG_MAP_RAM_SUB(1)[j*32+i] = colore_cornice;
				else
					BG_MAP_RAM_SUB(1)[j*32+i] = 3;
			for(i = 19; i < 31; i++)
				if(i == 19 || i == 30)
					BG_MAP_RAM_SUB(1)[j*32+i] = colore_cornice;
				else
					BG_MAP_RAM_SUB(1)[j*32+i] = 3;
		}
	}

	if((s->health) > 90){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+20] = 1;
			BG_MAP_RAM_SUB(1)[j*32+21] = 1;
			BG_MAP_RAM_SUB(1)[j*32+22] = 1;
			BG_MAP_RAM_SUB(1)[j*32+23] = 1;
			BG_MAP_RAM_SUB(1)[j*32+24] = 1;
			BG_MAP_RAM_SUB(1)[j*32+25] = 1;
			BG_MAP_RAM_SUB(1)[j*32+26] = 1;
			BG_MAP_RAM_SUB(1)[j*32+27] = 1;
			BG_MAP_RAM_SUB(1)[j*32+28] = 1;
			BG_MAP_RAM_SUB(1)[j*32+29] = 1;
		}
	}
	else if((s->health) > 80){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+29] = 1;
			BG_MAP_RAM_SUB(1)[j*32+21] = 1;
			BG_MAP_RAM_SUB(1)[j*32+22] = 1;
			BG_MAP_RAM_SUB(1)[j*32+23] = 1;
			BG_MAP_RAM_SUB(1)[j*32+24] = 1;
			BG_MAP_RAM_SUB(1)[j*32+25] = 1;
			BG_MAP_RAM_SUB(1)[j*32+26] = 1;
			BG_MAP_RAM_SUB(1)[j*32+27] = 1;
			BG_MAP_RAM_SUB(1)[j*32+28] = 1;
		}
	}

	else if((s->health) > 70){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+28] = 1;
			BG_MAP_RAM_SUB(1)[j*32+29] = 1;
			BG_MAP_RAM_SUB(1)[j*32+22] = 1;
			BG_MAP_RAM_SUB(1)[j*32+23] = 1;
			BG_MAP_RAM_SUB(1)[j*32+24] = 1;
			BG_MAP_RAM_SUB(1)[j*32+25] = 1;
			BG_MAP_RAM_SUB(1)[j*32+26] = 1;
			BG_MAP_RAM_SUB(1)[j*32+27] = 1;
		}
	}
	else if((s->health) > 60){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+27] = 1;
			BG_MAP_RAM_SUB(1)[j*32+28] = 1;
			BG_MAP_RAM_SUB(1)[j*32+29] = 1;
			BG_MAP_RAM_SUB(1)[j*32+23] = 1;
			BG_MAP_RAM_SUB(1)[j*32+24] = 1;
			BG_MAP_RAM_SUB(1)[j*32+25] = 1;
			BG_MAP_RAM_SUB(1)[j*32+26] = 1;
		}
	}

	else if((s->health) > 50){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+26] = 1;
			BG_MAP_RAM_SUB(1)[j*32+27] = 1;
			BG_MAP_RAM_SUB(1)[j*32+28] = 1;
			BG_MAP_RAM_SUB(1)[j*32+29] = 1;
			BG_MAP_RAM_SUB(1)[j*32+24] = 1;
			BG_MAP_RAM_SUB(1)[j*32+25] = 1;
		}
	}
	else if((s->health) > 40){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+29] = 1;
			BG_MAP_RAM_SUB(1)[j*32+28] = 1;
			BG_MAP_RAM_SUB(1)[j*32+27] = 1;
			BG_MAP_RAM_SUB(1)[j*32+26] = 1;
			BG_MAP_RAM_SUB(1)[j*32+25] = 1;
		}
	}
	else if((s->health) > 30){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+29] = 6;
			BG_MAP_RAM_SUB(1)[j*32+28] = 6;
			BG_MAP_RAM_SUB(1)[j*32+27] = 6;
			BG_MAP_RAM_SUB(1)[j*32+26] = 6;
		}
	}

	else if((s->health) > 20){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+29] = 6;
			BG_MAP_RAM_SUB(1)[j*32+28] = 6;
			BG_MAP_RAM_SUB(1)[j*32+27] = 6;
		}
	}
	else if((s->health) > 10){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+29] = 5;
			BG_MAP_RAM_SUB(1)[j*32+28] = 5;
		}
	}

	else if((s->health) > 0){
		for(j = 2; j < 5; j++)
			BG_MAP_RAM_SUB(1)[j*32+29] = 5;
	}


	if((t->health) > 90){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+3] = 1;
			BG_MAP_RAM_SUB(1)[j*32+4] = 1;
			BG_MAP_RAM_SUB(1)[j*32+5] = 1;
			BG_MAP_RAM_SUB(1)[j*32+6] = 1;
			BG_MAP_RAM_SUB(1)[j*32+7] = 1;
			BG_MAP_RAM_SUB(1)[j*32+8] = 1;
			BG_MAP_RAM_SUB(1)[j*32+9] = 1;
			BG_MAP_RAM_SUB(1)[j*32+10] = 1;
			BG_MAP_RAM_SUB(1)[j*32+11] = 1;
			BG_MAP_RAM_SUB(1)[j*32+12] = 1;
		}
	}
	else if((t->health) > 80){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+4] = 1;
			BG_MAP_RAM_SUB(1)[j*32+5] = 1;
			BG_MAP_RAM_SUB(1)[j*32+6] = 1;
			BG_MAP_RAM_SUB(1)[j*32+7] = 1;
			BG_MAP_RAM_SUB(1)[j*32+8] = 1;
			BG_MAP_RAM_SUB(1)[j*32+9] = 1;
			BG_MAP_RAM_SUB(1)[j*32+10] = 1;
			BG_MAP_RAM_SUB(1)[j*32+11] = 1;
			BG_MAP_RAM_SUB(1)[j*32+3] = 1;
		}
	}

	else if((t->health) > 70){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+5] = 1;
			BG_MAP_RAM_SUB(1)[j*32+6] = 1;
			BG_MAP_RAM_SUB(1)[j*32+7] = 1;
			BG_MAP_RAM_SUB(1)[j*32+8] = 1;
			BG_MAP_RAM_SUB(1)[j*32+9] = 1;
			BG_MAP_RAM_SUB(1)[j*32+10] = 1;
			BG_MAP_RAM_SUB(1)[j*32+4] = 1;
			BG_MAP_RAM_SUB(1)[j*32+3] = 1;
		}
	}
	else if((t->health) > 60){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+6] = 1;
			BG_MAP_RAM_SUB(1)[j*32+7] = 1;
			BG_MAP_RAM_SUB(1)[j*32+8] = 1;
			BG_MAP_RAM_SUB(1)[j*32+9] = 1;
			BG_MAP_RAM_SUB(1)[j*32+5] = 1;
			BG_MAP_RAM_SUB(1)[j*32+4] = 1;
			BG_MAP_RAM_SUB(1)[j*32+3] = 1;
		}
	}

	else if((t->health) > 50){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+7] = 1;
			BG_MAP_RAM_SUB(1)[j*32+8] = 1;
			BG_MAP_RAM_SUB(1)[j*32+6] = 1;
			BG_MAP_RAM_SUB(1)[j*32+5] = 1;
			BG_MAP_RAM_SUB(1)[j*32+4] = 1;
			BG_MAP_RAM_SUB(1)[j*32+3] = 1;
		}
	}
	else if((t->health) > 40){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+7] = 1;
			BG_MAP_RAM_SUB(1)[j*32+6] = 1;
			BG_MAP_RAM_SUB(1)[j*32+5] = 1;
			BG_MAP_RAM_SUB(1)[j*32+4] = 1;
			BG_MAP_RAM_SUB(1)[j*32+3] = 1;
		}
	}
	else if((t->health) > 30){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+6] = 6;
			BG_MAP_RAM_SUB(1)[j*32+5] = 6;
			BG_MAP_RAM_SUB(1)[j*32+4] = 6;
			BG_MAP_RAM_SUB(1)[j*32+3] = 6;
		}
	}

	else if((t->health) > 20){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+3] = 6;
			BG_MAP_RAM_SUB(1)[j*32+4] = 6;
			BG_MAP_RAM_SUB(1)[j*32+5] = 6;
		}
	}
	else if((t->health) > 10){
		for(j = 2; j < 5; j++){
			BG_MAP_RAM_SUB(1)[j*32+3] = 5;
			BG_MAP_RAM_SUB(1)[j*32+4] = 5;
		}
	}

	else if((t->health) > 0){
		for(j = 2; j < 5; j++)
			BG_MAP_RAM_SUB(1)[j*32+3] = 5;
	}

}

void gameover(){
	// Configure the SUB engine in Rotoscale Mode
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;
	// Configure the corresponding VRAM memory bank correctly
	VRAM_H_CR = VRAM_ENABLE | VRAM_H_SUB_BG;
	// Configure background BG2 in rotoscale mode using 8bit pixels
	BGCTRL_SUB[2] = BG_BMP_BASE(0) | BG_BMP8_256x256;

	swiCopy(gameoverBitmap, BG_GFX_SUB, gameoverBitmapLen/2);
	swiCopy(gameoverPal, BG_PALETTE_SUB, gameoverPalLen/2);
}

void youwin(){

	REG_DISPCNT = MODE_5_2D | DISPLAY_BG0_ACTIVE;
	//BG0 configuration for the background
	BGCTRL[0] = BG_COLOR_256 | BG_MAP_BASE(25) | BG_TILE_BASE(4) | BG_32x32;
	//Copy data to display background (tiles, palette and map)
	swiCopy(youwinTiles, BG_TILE_RAM(4), youwinTilesLen/2);
	swiCopy(youwinPal, BG_PALETTE, youwinPalLen/2);
	swiCopy(youwinMap, BG_MAP_RAM(25), youwinMapLen/2);
}

void youlose(){

	REG_DISPCNT = MODE_5_2D | DISPLAY_BG0_ACTIVE;
	//BG0 configuration for the background
	BGCTRL[0] = BG_COLOR_256 | BG_MAP_BASE(25) | BG_TILE_BASE(4) | BG_32x32;
	//Copy data to display background (tiles, palette and map)
	swiCopy(youloseTiles, BG_TILE_RAM(4), youloseTilesLen/2);
	swiCopy(youlosePal, BG_PALETTE, youlosePalLen/2);
	swiCopy(youloseMap, BG_MAP_RAM(25), youloseMapLen/2);
}
