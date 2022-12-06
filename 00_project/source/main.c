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
    // 2) Main engine configuration in rotoscale mode
    REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;
    init_sub_screen();
    while(1)
        swiWaitForVBlank();	
}
