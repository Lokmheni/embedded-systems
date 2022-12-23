/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "graphics/graphics.h"

#include "game/game_controller.h"
#include "graphics/graphics.h"


int main(void)
{

    consoleDemoInit();
    init_screens();
    get_touch_input();
    // configureSprites();
    // printf("\nTemplate nds\n");
    // set screens
    Player t;
    get_player_local(t);
    while (1)
        swiWaitForVBlank();
}
