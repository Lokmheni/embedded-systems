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
#include "graphics/chrono_display.h"

int min, sec, msec;
int x1, y, x2;

int main(void)
{
    consoleDemoInit();
    //oamInit(&oamMain, SpriteMapping_1D_32, false);
    init_screens();


    //sprite_pos_remote(t);
    //sprite_pos_local(t);


    while(1) {
    	swiWaitForVBlank();
    	//oamUpdate(&oamMain);
    }
}





