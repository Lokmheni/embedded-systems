
#include <nds.h>
#include <stdio.h>
#include "field.h"
#include "ball.h"

#define SCREEN_WIDTH	256
#define	SCREEN_HEIGHT	192

#define	SPRITE_WIDTH	32
#define	SPRITE_HEIGHT	32

//Pointer to the graphic buffer where to store the sprite
u16* gfx;

void configureBG0() {
	//Activate and configure VRAM bank to work in background mode
	//...

	//BG0 configuration for the background
	//...

	//Copy data to display background (tiles, palette and map)
	//...
	//...
	//...
}


void configureSprites() {
	//Set up memory bank to work in sprite mode (offset since we are using VRAM A for backgrounds)
	//...

	//Initialize sprite manager and the engine
	//...

	//Allocate space for the graphic to show in the sprite
	//...

	//Copy data for the graphic (palette and bitmap)
	//...
	//...
}

int main(void) {

	//MAIN engine
	//...

	//Configure and fill BG0
	configureBG0();

	//Configure sprites and fill graphics
	configureSprites();

	//Position
	int x = 0, y = 0, keys;
    while(1){
    	//Read held keys
    	scanKeys();
    	keys = keysHeld();

    	//Modify position of the sprite accordingly
    	if((keys & KEY_RIGHT) && (x < (SCREEN_WIDTH - SPRITE_WIDTH))) x+=2;
    	if((keys & KEY_DOWN) && (y < (SCREEN_HEIGHT - SPRITE_HEIGHT))) y+=2;
    	if((keys & KEY_LEFT) && (x  > 0)) x-=2;
    	if((keys & KEY_UP) && (y  > 0)) y-=2;

    	oamSet(&oamMain, 	// oam handler
    		0,				// Number of sprite
    		x, y,			// Coordinates
    		0,				// Priority
    		0,				// Palette to use
    		SpriteSize_32x32,			// Sprite size
    		SpriteColorFormat_256Color,	// Color format
    		gfx,			// Loaded graphic to display
    		-1,				// Affine rotation to use (-1 none)
    		false,			// Double size if rotating
    		false,			// Hide this sprite
    		false, false,	// Horizontal or vertical flip
    		false			// Mosaic
    		);
    	swiWaitForVBlank();
    	//Update the sprites
		oamUpdate(&oamMain);
    }
}
