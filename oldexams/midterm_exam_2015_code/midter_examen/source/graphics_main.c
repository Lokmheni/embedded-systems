#include "graphics_main.h"
#include "game.h"

void configureGraphics_Main() {
	// Configure the MAIN engine framebuffer mode
	//... TO COMPLETE EXERCISE 1
	REG_DISPCNT = MODE_FB0;
	// Configure a proper VRAM bank
	//... TO COMPLETE EXERCISE 1
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_LCD;
}

void fillScreen_Main(u16 color){
	//Fill the buffer of the screen with the given input color
	//... TO COMPLETE EXERCISE 1
	u16* Graphics_mainBuffer = VRAM_A;
	int i;
	for(i = 0; i<256*192; i++) {
		Graphics_mainBuffer[i] = color;
	}
}
