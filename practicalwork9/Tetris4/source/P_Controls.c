#include "P_Controls.h"

#include "Tetris/TetrisGameplay.h"

/*
 * This function handles the input by monitoring the keys and the touchscreen
 * and invoking the function Gameplay_HandleInput(...) with the correct input
 * value
 */
void handleInput()
{
    // Scan the keys
    //....

    /* Identify the keys and map the action according to the table given in
     * the manual. Call the function Gameplay_handleInput(..) to send an action
     * to the logic of the game */
    //....


    // Call the touch-handling function
    //...

    // Update the game and redraw the blocks
    Gameplay_update();
    Gameplay_draw();
}
