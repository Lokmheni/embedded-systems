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

    oamInit(&oamMain, SpriteMapping_1D_32, false);

    Player* t;
    Player* s;

    (t->pos_x) = 0;
    (t->pos_y) = 90;

    (s->pos_x) = 250;
    (s->pos_y) = 90;
    init_screens();
    get_touch_input();
   // sprite_pos_local(t);
    //show_timer();

    x1 = 0;
    x2 = 256;

    y = 90;

    while(1) {
    	swiWaitForVBlank();
    	oamUpdate(&oamMain);
    }
}





