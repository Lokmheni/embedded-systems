#include <nds.h>
#include <stdio.h>
#include "P_Graphics.h"

extern int x1, y, x2, y2, x3, y3;

int main(void) {
	
	x1 = 0;
	y = 0;

	x2=64;
	y2=64;

	x3=128;
	y3=128;

	configureGraphics_Main();
	configSprites_Main();

    while(1){
    	swiWaitForVBlank();
    	oamUpdate(&oamMain);

    }

}

