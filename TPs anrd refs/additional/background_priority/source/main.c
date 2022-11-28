#include <nds.h>
#include <stdio.h>
#include "image.h"


u8 mytile0[] = {
000, 000, 000, 000, 000, 000, 000, 000,
000, 000, 000, 000, 000, 000, 000, 000,
000, 000, 000, 000, 000, 000, 000, 000,
000, 000, 000, 254, 254, 000, 000, 000,
000, 000, 000, 254, 254, 000, 000, 000,
000, 000, 000, 000, 000, 000, 000, 000,
000, 000, 000, 000, 000, 000, 000, 000,
000, 000, 000, 000, 000, 000, 000, 000,
};

u8 mytile1[] = {
000, 000, 000, 000, 000, 000, 000, 000,
000, 000, 000, 000, 000, 000, 000, 000,
000, 000, 255, 255, 255, 255, 000, 000,
000, 000, 255, 255, 255, 255, 000, 000,
000, 000, 255, 255, 255, 255, 000, 000,
000, 000, 255, 255, 255, 255, 000, 000,
000, 000, 000, 000, 000, 000, 000, 000,
000, 000, 000, 000, 000, 000, 000, 000,
};

void configure_graphics_main() {
	int i;

	//Activate main engine in mode 5 and all backgrounds
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG3_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG0_ACTIVE;
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	//Configure background 0 (tiled)
	BGCTRL[0] = BG_MAP_BASE(1) | BG_TILE_BASE(0) | BG_32x32 | BG_COLOR_256;
	swiCopy(mytile0, &BG_TILE_RAM(0)[0], 32);
	for(i = 0; i < 32*24; i++) BG_MAP_RAM(1)[i] = 0;

	//Configure background 1 (tiled)
	BGCTRL[1] = BG_MAP_BASE(2) | BG_TILE_BASE(0) | BG_32x32 | BG_COLOR_256;
	swiCopy(mytile1, &BG_TILE_RAM(0)[32], 32);
	for(i = 0; i < 32*24; i++) BG_MAP_RAM(2)[i] = 1;

	//Configure background 2 (rotoscale)
	BGCTRL[2] = BG_BMP_BASE(1) | (u16)BgSize_B8_256x256;
	swiCopy(&imageBitmap[0],BG_BMP_RAM(1), imageBitmapLen/4);
	bgTransform[2]->xdx = (1 << 8);
	bgTransform[2]->ydx = 0;
	bgTransform[2]->xdy = 0;
	bgTransform[2]->ydy = (1 << 8);
	bgTransform[2]->dx = 0;
	bgTransform[2]->dy = 0;

	//Configure background 3 (rotoscale)
	BGCTRL[3] = BG_BMP_BASE(4) | (u16)BgSize_B8_256x256;
	swiCopy(&imageBitmap[256*48],BG_BMP_RAM(4), imageBitmapLen/4);
	bgTransform[3]->xdx = (1 << 8);
	bgTransform[3]->ydx = 0;
	bgTransform[3]->xdy = 0;
	bgTransform[3]->ydy = (1 << 8);
	bgTransform[3]->dx = 0;
	bgTransform[3]->dy = 0;

	//Set up palette
	swiCopy(imagePal, BG_PALETTE, imagePalLen/2);
	BG_PALETTE[254] = ARGB16(1,0,0,31);
	BG_PALETTE[255] = ARGB16(1,0,31,0);
}

void change_bckg_priority(u16 bckg, u16 priority) {
	//Sanity check
	if((bckg >= 4) || (priority >= 4))
		return;
	//Set up the priority of the background
	BGCTRL[bckg] = (BGCTRL[bckg] & 0xFFFC) | priority;
}


int main(void) {

	u16 priorities[4] = {0,0,0,0};
	u16 current_bckg = 0, i, keys;

	//Configure graphics
	configure_graphics_main();
	consoleDemoInit();

	scanKeys();
	while(1){
		//Read keys
		scanKeys();
		keys = keysDown();

		//Interpret keys
		if(keys & KEY_LEFT) current_bckg = (current_bckg + 3) % 4;
		if(keys & KEY_RIGHT) current_bckg = (current_bckg + 1) % 4;
		if(keys & KEY_UP) priorities[current_bckg] = (priorities[current_bckg] + 1) % 4;
		if(keys & KEY_DOWN) priorities[current_bckg] = (priorities[current_bckg] + 3) % 4;

		//Change priority accordingly
		change_bckg_priority(current_bckg,priorities[current_bckg]);

		//Print status
		consoleClear();
		printf("LEFT / RIGHT: Select background\n");
		printf("UP   / DOWN : Change priority\n\n");
		printf("\nPriorities:\n");
		for(i=0; i<4; i++)
			printf("BG%d:%d  ", i, priorities[i]);
		printf("\n\nSelected-> BG%d   Priority->%d", current_bckg, priorities[current_bckg]);

        swiWaitForVBlank();
    }
}
