/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "graphics.h"


int main(void) {
	
    consoleDemoInit();
    init_screens();
    get_touch_input();
    //configureSprites();
    //printf("\nTemplate nds\n");
    //set screens

    while(1)
        swiWaitForVBlank();	
}
