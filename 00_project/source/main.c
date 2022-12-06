/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "settings.h"

int main(void) {
	
    consoleDemoInit();
    //printf("\nTemplate nds\n");
    //set screens
    init_screens();
    while(1)
        swiWaitForVBlank();	
}
