#include "graphics_main.h"

void configureGraphics_Main() {
	// Configure the MAIN engine in Framebuffer Mode
	//...TO COMPLETE EXERCISE 1
	REG_DISPCNT = MODE_FB0;
	// Configure the corresponding VRAM memory bank correctly
	//...TO COMPLETE EXERCISE 1
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_LCD;
}

void fillRegion_Main(int region, u16 color){
	//...TO COMPLETE EXERCISE 1
	u16* Graphics_mainBuffer = VRAM_A;
	int i, j;
	for(i = 0; i<192; i++) {
		for(j = (0 + region*64); j < (64 + region*64); j++) {
		Graphics_mainBuffer[i*256 + j] = color;
		}
	}

}
