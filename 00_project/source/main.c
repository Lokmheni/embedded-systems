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

void ISR_TIMER0()
{
	msec = (msec + 1)%1000;
	if(msec == 0)
	{
		sec = (sec+1) % 60;
		if(sec == 0)
			min++;
	}
	updateChronoDisp_Sub(min, sec, msec);
}


int main(void)
{
    consoleDemoInit();
    //Player* t;
    //init_screens();


    //sprite_pos_local(t);
    //configureSprites();
    //get_touch_input();
    // configureSprites();
    // printf("\nTemplate nds\n");
    // set screens


    // do sprites in main

    //displaying timer in sub in main.c

    initChronoDisp_Sub();
	changeColorDisp_Sub(RED);
	irqInit();
	min = sec = msec = 0;
	TIMER_DATA(0) = TIMER_FREQ_1024(1000);
	TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqSet(IRQ_TIMER0, &ISR_TIMER0);
	irqEnable(IRQ_TIMER0);

	while(1) {
			swiWaitForVBlank();
		}
}




