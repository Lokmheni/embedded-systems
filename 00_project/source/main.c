/**
 * @file main.c
 * @authors Simon Thür and Lokman Mheni
 * @brief Project **Street-fighter** for embedded systems EE-310
 * @version 0.1
 * @date 2023-01-13
 *
 * @copyright Copyright (c) 2023
 *
 *
 *
 * This is the project **Street-fighter** by Simon Thür and Lokman Mheni. The
 * main aim is a multiplayer 1v1 fighter game through wifi connection. As an
 * 'afterthought' the game also features a very basic single player mode.
 *
 * ### Here is a list of where requirements can be found
 * (Only examples, not all references)
 * 1. Arm9 Arm7 processors both used
 *    - Arm9
 *      - Arrow keys: @ref input.c
 *      - Permanent storage: @ref memory.c
 *    - Arm7
 *      - Wifi: @ref wifi.c
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


#include <fat.h>
#include <nds.h>

#include "constants.h"
#include "game/game_controller.h"
#include "game/game_sync_fsm.h"
#include "graphics/chrono_display.h"
#include "graphics/graphics.h"
#include "io/input.h"
#include "numbers.h"


int main(void)
{
    //===================================================================
    // Setup Graphics (ordering relevant)
    //===================================================================
    init_screens();

    ///@todo move oamInit to graphics
    oamInit(&oamMain, SpriteMapping_1D_32, false);

    //===================================================================
    // Setup Sound (ordering relevant)
    //===================================================================
    init_sound();
    play_music();

    //===================================================================
    // Setup FAT
    //===================================================================
    fatInitDefault();

    //===================================================================
    // Setup Game
    //===================================================================
    TouchInput ti;


    if (get_touch_input(&ti))
        if (ti == TOUCH_INPUT_SINGLE_PLAYER)
            {
                go_for_singleplayer();
            }
        else
            {
                consoleDemoInit();
                printf("\nWait for wifi connection\n");
                go_for_multiplayer();
            }


    //===================================================================
    // Switch to game screens
    //===================================================================
    set_stage();
    swiWaitForVBlank();
    init_main_screen();
    sprite_initializer();
    show_timer();


    if (get_connection_state() == CONNECTION_TYPE_LFG)
        {
            consoleDemoInit(); // clear screen
            printf("\nWait for other player\n");
        }

    //===================================================================
    // Main game loop
    //===================================================================
    RequestedAction   a;
    RequestedMovement m;
    WifiMsg           msg;


    for (;;)
        {
            receive_messages(&msg);
            get_input(&a, &m);
            if (get_game_state() != GAME_IN_PROGRESS)
                {
                    if (keysHeld() & KEY_TOUCH)
                        a = REQ_ACTION_START_GAME;
                }
            exec_sync_fsm(a, m, msg, get_timer_timeout());
            swiWaitForVBlank();

            sprite_pos_local(get_player_local());
            sprite_pos_remote(get_player_remote());
            if (get_game_state() == GAME_IN_PROGRESS)
                {
                    updateChrono(get_player_local(), get_player_remote());
                }

            /// @todo move oamUpdate to graphics
            // oamUpdate(&oamMain);
        }
}
