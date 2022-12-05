/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

#include "game/game_controller.h"


int main(void)
{

    consoleDemoInit();

    printf("MEGA SWAGs\n");

    set_stage();
    print_game_state();
    int i;
    for (i = 0; i < 3; i++)
        {
            update_game();
            print_players();
        }


    while (1)
        swiWaitForVBlank();
}
