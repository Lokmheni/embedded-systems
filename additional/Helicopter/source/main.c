/*---------------------------------------------------------------------------------

	Basic template code for starting a DS app

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include <string.h>
#include "helicopter.h"

//This variable tells us which image to render (0,1 or 2)
int image = 0;

//Timer0 ISR for changing the image every 100 ms
void Timer0ISR()
{
	//Change image and copy it to the engin memory
	image = (image + 1) % 3;
	int offset = image*256*192/4;
	memcpy(BG_GFX, &helicopterBitmap[offset], 256*192);
}

//Our increasing / decreasing factor and a flag
int increasing=0;
float factor = 1.0;

//Timer1 ISR to change the scale of the affine transform matrix
void Timer1ISR()
{
	//Increas/decreas the factor by 0.1
	if(increasing)
		factor = factor + 0.1;
	else
		factor = factor - 0.1;

	//Check and update the flag if necessary
	if(factor <= 0.2) increasing = 1;
	if(factor >= 1) increasing = 0;

	//Change the Affine Transfomration Matrix
	bgTransform[2]->xdx = 256 / factor;
	bgTransform[2]->ydy = 256 / factor;
	bgTransform[2]->xdy = 0;
	bgTransform[2]->ydx = 0;
}

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	//Engine and background configuration
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	BGCTRL[2] = BG_MAP_BASE(0) | BgSize_B8_256x256;

	//Transfer of the image and the palette to the engine
	memcpy(BG_GFX, helicopterBitmap, 256*192);
	memcpy(BG_PALETTE, helicopterPal, helicopterPalLen);

	//Set the matrix affine transform
	bgTransform[2]->xdx = 256;
	bgTransform[2]->ydy = 256;
	bgTransform[2]->xdy = 0;
	bgTransform[2]->ydx = 0;

	//Interrupt initialization, enabling and handlers setup
	irqInit();
	irqEnable(IRQ_VBLANK);
	irqSet(IRQ_TIMER0, &Timer0ISR);
	TIMER_DATA(0) = TIMER_FREQ_1024(10);
	TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqEnable(IRQ_TIMER0);

	irqSet(IRQ_TIMER1, &Timer1ISR);
	TIMER_DATA(1) = TIMER_FREQ_1024(20);
	TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqEnable(IRQ_TIMER1);

	while(1) {
		swiWaitForVBlank();
	}
}

