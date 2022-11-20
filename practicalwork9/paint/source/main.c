/*-----------------------------------------------------------------------------

Basic template code for starting a DS app

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include <string.h>

int main(void)
{

    // Configure the Engine in FB mode
    REG_DISPCNT = MODE_FB0;
    // Configure the VRAM block
    VRAM_A_CR   = VRAM_ENABLE | VRAM_A_LCD;
    // Swap the LCD
    REG_POWERCNT ^= BIT(15);
    // Fill the canvas with WHITE color
    memset(VRAM_A, 0xFF, 256 * 192 * 2);


    // Declaration of the touch struct
    touchPosition touch, lastTouchPos;
    bool          lastTouch;
    while (1)
        {
            scanKeys();
            // Poll the touch-screen
            touchRead(&touch);
            // If the touch is different to (0,0), change the color of the pixel
            if (touch.px || touch.py)
                {
                    if (lastTouch)
                        {
                            int x = lastTouchPos.px;
                            int y = lastTouchPos.py;
                            while (x != touch.px || y != touch.py)
                                {
                                    VRAM_A[y * 256 + x] = ARGB16(1, 0, 0, 0);
                                    x += x < touch.px ? 1
                                       : x > touch.px ? -1
                                                      : 0;
                                    y += y < touch.py ? 1
                                       : y > touch.py ? -1
                                                      : 0;
                                }
                        }
                    else
                        {
                            VRAM_A[touch.py * 256 + touch.px] =
                                ARGB16(1, 0, 0, 0);
                        }
                    lastTouch    = true;
                    lastTouchPos = touch;
                }
            else
                {
                    lastTouch = false;
                }

            swiWaitForVBlank();
        }
}
