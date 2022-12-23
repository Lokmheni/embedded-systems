/*
 * Template Nintendo DS
 * May 2011
 */

#include <math.h>
#include <nds.h>
#include <stdio.h>

#include "game/game_controller.h"
#include "graphics/graphics.h"
#include "numbers.h"
#include "paysage.h"
#include "play_mode.h"
#include "player.h"
#include "player2.h"
#include "streetfighter.h"
#include "string.h"
int main(void)
{
    consoleDemoInit();
    Player* t;
    init_screens();

    //sprite_pos_local(t);
    //configureSprites();
    get_touch_input();
    // configureSprites();
    // printf("\nTemplate nds\n");
    // set screens


    // do sprites in main

}

