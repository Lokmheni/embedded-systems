/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

#include "game/game_controller.h"
#include "graphics/graphics.h"


int main(void)
{

    consoleDemoInit();
    init_screens();
    get_touch_input();
    //configureSprites();
    //printf("\nTemplate nds\n");
    //set screens

    Player t;
    t.pos_x = 100;
    t.pos_y = 50;
     //get_player_local(t);
    sprite_pos_local(&t);
    //printf(&t.pos_x);
    while(1){
       	swiWaitForVBlank();
       	oamUpdate(&oamMain);
    }
}
