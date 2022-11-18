#include <nds.h>
#include <stdio.h>


//---------------------------------------------------------------------------------
int main(void)
{
    //---------------------------------------------------------------------------------

    // Do not forget to initialize the console
    //...

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
    while (1)
        {
            /*************
             * Exercise 1
             *************/
            // Scan the keys
            //...
            // Identify which key was pressed and print it in the console
            // u16 keys = ...
            //...


            /*******************/


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
