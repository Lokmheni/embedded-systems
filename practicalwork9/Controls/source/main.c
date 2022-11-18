#include <nds.h>
#include <nds/arm9/input.h>
#include <nds/input.h>
#include <stdio.h>


//---------------------------------------------------------------------------------
int main(void)
{
    //---------------------------------------------------------------------------------

    // Do not forget to initialize the console
    consoleDemoInit();


    /*************
     * Exercise 2
     *************/
    // Initialize the interrupt system
    //...

    /*Configure the keys to throw an interrupt with the keys
    UP, DOWN, LEFT or RIGHT*/
    // REG_KEYCNT = ...

    // Set the ISR to the IRQ line and enable the IRQ line
    //...
    //...

    // Do not forget to enable the IRQ line for the VBLANK
    //...
    /********************/


    // The main infinite loop
    scanKeys();

    for (;;)
        {
            // GET KEYS
            scanKeys();

            // hanlde keys
            u32 k = keysUp();
            if (k & KEY_A)
                printf("Key A pressed\n");
            if (k & KEY_B)
                printf("Key B pressed\n");
            if (k & KEY_X)
                printf("Key X pressed\n");
            if (k & KEY_Y)
                printf("Key Y pressed\n");
            // end of loop
            swiWaitForVBlank();


            /*************
             * Exercise 3 (Do not forget to comment exercise 2)
             *************/
            // Declare a touchPosition variable
            //...

            // Read the touchscreen
            //...

            // Identify a valid touched coordinates and print them
            //...

            /**************/
        }
}
