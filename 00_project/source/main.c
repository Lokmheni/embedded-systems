/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

#include "graphics.h"


int main(void)
{

    consoleDemoInit();
    init_screens();
    init_main_screen();
    init_sub_screen();
    configureSprites();


    for (;;)
        swiWaitForVBlank();
}
