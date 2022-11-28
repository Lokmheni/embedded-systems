#include "P_Graphics.h"
#include <nds.h>
#include <stdio.h>

#include "arrow.h"
#include "hexagon.h"
#include "star.h"

u16* gfx;
u16* gfx1;
u16* gfx2;




void configureGraphics_Main() {

	REG_DISPCNT = MODE_5_2D | DISPLAY_BG0_ACTIVE;

	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;

	oamInit(&oamMain, SpriteMapping_1D_32, false);
	gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color );
	gfx1 = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color );
	gfx2 = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color );

}

void configSprites_Main(){
	dmaCopy(arrowPal,SPRITE_PALETTE,arrowPalLen);
	dmaCopy(hexagonPal,&SPRITE_PALETTE[arrowPalLen/2],hexagonPalLen);
	dmaCopy(starPal,&SPRITE_PALETTE[(arrowPalLen+hexagonPalLen)/2],starPalLen);

	dmaCopy(arrowTiles,gfx,arrowTilesLen);
	dmaCopy(hexagonTiles,gfx1,hexagonTilesLen);
	dmaCopy(starTiles,gfx2,starTilesLen);

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
				x2, y2,			// Coordinates
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

	oamSet(&oamMain, 	// oam handler
				2,				// Number of sprite
				x3, y3,			// Coordinates
				0,				// Priority
				2,				// Palette to use
				SpriteSize_32x32,			// Sprite size
				SpriteColorFormat_16Color,	// Color format
				gfx2,			// Loaded graphic to display
				-1,				// Affine rotation to use (-1 none)
				false,			// Double size if rotating
				false,			// Hide this sprite
				false, false,	// Horizontal or vertical flip
				false			// Mosaic
				);
}


