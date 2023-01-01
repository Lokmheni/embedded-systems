/*
 * Template Nintendo DS
 * May 2011
 */

#include <math.h>
#include <nds.h>
#include <stdio.h>

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

void configureSprites(){
	u16* gfx;
	u16* gfx1;

	gfx =	oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	gfx1 =	oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

	dmaCopy(playerPal, &SPRITE_PALETTE[player2PalLen/2 + 1], playerPalLen);
	dmaCopy(playerTiles, gfx, playerTilesLen);
	dmaCopy(player2Pal, SPRITE_PALETTE, player2PalLen);
	dmaCopy(player2Tiles, gfx1, player2TilesLen);

	oamSet(&oamMain, 	// oam handler
					0,				// Number of sprite
					x1, y,			// Coordinates
					0,				// Priority
					0,				// Palette to use
					SpriteSize_32x32,			// Sprite size
					SpriteColorFormat_16Color,	// Color format
					gfx,			// Loaded graphic to display
					-1,				// Affine rotation to use (-1 none)
					false,			// Double size if rotating
					false,			// Hide this sprite
					false, false,	// Horizontal or vertical flip
					false			// Mosaic
					);

	oamSet(&oamMain, 	// oam handler
					1,				// Number of sprite
					x2, y,			// Coordinates
					0,				// Priority
					1,				// Palette to use
					SpriteSize_32x32,			// Sprite size
					SpriteColorFormat_16Color,	// Color format
					gfx1,			// Loaded graphic to display
					-1,				// Affine rotation to use (-1 none)
					false,			// Double size if rotating
					false,			// Hide this sprite
					false, false,	// Horizontal or vertical flip
					false			// Mosaic
					);
}


int main(void)
{
    consoleDemoInit();

    oamInit(&oamMain, SpriteMapping_1D_32, false);

    Player* t;
    //init_screens();
    //get_touch_input();
   // sprite_pos_local(t);
    //show_timer();

    x1 = 0;
    x2 = 256;

    y = 90;

    init_main_screen(t);
    //configureSprites();
    sprite_pos_local(t);

    while(1) {
    	swiWaitForVBlank();
    	oamUpdate(&oamMain);
    }
}





