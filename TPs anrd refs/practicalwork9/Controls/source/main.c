#include <nds.h>
#include <nds/arm9/input.h>
#include <nds/input.h>
#include <stdio.h>


// TODO run on device


void IsrKeys()
{
    u16 key = ~(REG_KEYINPUT);

    if (key & KEY_UP)
        printf("Key UP pressed    <ISR>\n");
    if (key & KEY_DOWN)
        printf("Key DOWN pressed  <ISR>\n");
    if (key & KEY_LEFT)
        printf("Key LEFT pressed  <ISR>\n");
    if (key & KEY_RIGHT)
        printf("Key RIGHT pressed <ISR>\n");
}

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
    // irqInit();

    // /*Configure the keys to throw an interrupt with the keys
    // UP, DOWN, LEFT or RIGHT*/
    // REG_KEYCNT = BIT(14) | KEY_LEFT | KEY_RIGHT | KEY_UP | KEY_DOWN;

    // // Set the ISR to the IRQ line and enable the IRQ line
    // irqSet(IRQ_KEYS, IsrKeys);
    // irqEnable(IRQ_KEYS);

    // // Do not forget to enable the IRQ line for the VBLANK
    // irqEnable(IRQ_VBLANK);
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


            /*************
             * Exercise 3 (Do not forget to comment exercise 2)
             *************/
            // Declare a touchPosition variable
            touchPosition touch;

            // Read the touchscreen
            touchRead(&touch);

            int x = touch.px;
            int y = touch.py;
            if (touch.px && touch.py)
                printf("Touch in <%d,%d>\n", x, y);


            /**************/
            swiWaitForVBlank();
        }
}
