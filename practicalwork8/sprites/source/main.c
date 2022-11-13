
#include <nds.h>
#include <nds/arm9/background.h>
#include <nds/arm9/sprite.h>
#include <nds/arm9/video.h>
#include <stdio.h>

#include "ball.h"
#include "field.h"

#define SCREEN_WIDTH  256
#define SCREEN_HEIGHT 192

#define SPRITE_WIDTH  32
#define SPRITE_HEIGHT 32

// Pointer to the graphic buffer where to store the sprite
u16* gfx;

void configureBG0()
{
    // Activate and configure VRAM bank to work in background mode
    VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

    // BG0 configuration for the background
    BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

    // Copy data to display background (tiles, palette and map)
    dmaCopy(fieldTiles, BG_TILE_RAM(1), fieldTilesLen / 2);
    dmaCopy(fieldPal, BG_PALETTE, fieldPalLen / 2);
    dmaCopy(fieldMap, BG_MAP_RAM(0), fieldMapLen / 2);
}


void configureSprites()
{
    // Set up memory bank to work in sprite mode (offset since we are using VRAM
    // A for backgrounds)
    VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE;
    // Initialize sprite manager and the engine
    oamInit(&oamMain, SpriteMapping_1D_32, false);

    // Allocate space for the graphic to show in the sprite
    gfx =
        oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

    // Copy data for the graphic (palette and bitmap)
    dmaCopy(ballPal, SPRITE_PALETTE, ballPalLen / 2);
    dmaCopy(ballTiles, gfx, ballTilesLen / 2);
}

int main(void)
{

    // MAIN engine
    REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;

    // Configure and fill BG0
    configureBG0();

    // Configure sprites and fill graphics
    configureSprites();

    // Position
    int x = 0, y = 0, keys;
    while (1)
        {
            // Read held keys
            scanKeys();
            keys = keysHeld();

            // Modify position of the sprite accordingly
            if ((keys & KEY_RIGHT) && (x < (SCREEN_WIDTH - SPRITE_WIDTH)))
                x += 2;
            if ((keys & KEY_DOWN) && (y < (SCREEN_HEIGHT - SPRITE_HEIGHT)))
                y += 2;
            if ((keys & KEY_LEFT) && (x > 0))
                x -= 2;
            if ((keys & KEY_UP) && (y > 0))
                y -= 2;

            oamSet(&oamMain,                   // oam handler
                   0,                          // Number of sprite
                   x, y,                       // Coordinates
                   0,                          // Priority
                   0,                          // Palette to use
                   SpriteSize_32x32,           // Sprite size
                   SpriteColorFormat_256Color, // Color format
                   gfx,                        // Loaded graphic to display
                   -1,           // Affine rotation to use (-1 none)
                   false,        // Double size if rotating
                   false,        // Hide this sprite
                   false, false, // Horizontal or vertical flip
                   false         // Mosaic
            );
            swiWaitForVBlank();
            // Update the sprites
            oamUpdate(&oamMain);
        }
}
