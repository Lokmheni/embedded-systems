/**
 * @file main.c
 * @author Simon Thür and Lokman Mheni
 * @brief Project for embedded systems EE-310
 * @version 0.1
 * @date 2023-01-13
 *
 * @copyright Copyright (c) 2023
 *
 *
 *
 * This is the project `Street-fighter` by Simon Thür and Lokman Mheni. The main
 * aim is a multiplayer 1v1 fighter game through wifi connection. As an
 * 'afterthought' the game also features a very basic single player mode.
 *
 * ### Here is a list of where requirements can be found
 * (Only examples, not all references)
 * 1. Arm9 Arm7 processors both used
 *    - Arm9
 *      - Arrow keys: @ref input.c
 *      - Permanent storage: @ref memory.c
 * 2. Timers/Interrupts
 *    - Game countdown: @ref graphics.c (@ref manage_timer())
 *    - Delayed attack: @ref game_controller.c (@ref local_attack())
 * 3. Both graphics engines, at least 2BGs on one of them
 *    - Timer and healthbars: @ref graphics.c (@ref show_timer() and
 *      @ref set_healthbars())
 * 4. Keypad at least one key used
 *    - User input: @ref input.c (@ref get_input())
 * 5. Touchscreen used
 *    - Select Singleplayer/multiplayer: @ref input.c (@ref get_touch_input())
 * 6. Sound (music and sound-effect)
 *    - Music and sound-effects: @ref sound.c (@ref play_music() and
 *      @ref play_sound_effect())
 * 7. Secondary storage
 *    - Storing and retrieving high-score: @ref memory.c (@ref store_stats() and
 *      @ref get_stats)
 * 8. Wifi
 *    - Transfer data between NDS: @ref wifi.c
 * 9. Sprites
 *    - Player characters displayed as sprites: @ref graphics.c
 *      (@ref sprite_pos_remote())
 *
 *
 *
 * @note The documentation can be generated with doxygen.
 * (On the repo see 00_PROJECT/html/index.html)
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
