/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>

#include "graphics/graphics.h"


int main(void)
{
    //===================================================================
    // Setup (for graphics, ordering is necessary)
    //===================================================================
    init_screens();
    init_main_screen();
    sprite_initializer();
    init_sound();
    play_music();

    ///@todo move oamInit to graphics
    oamInit(&oamMain, SpriteMapping_1D_32, false);


    for (;;)
        {


            swiWaitForVBlank();

            /// @todo move oamUpdate to graphics
            oamUpdate(&oamMain);
        }
}
