

#include <nds.h>

#include "P_Graphics.h"


#define GREEN RGB15(0, 31, 0)

int main(void)
{
    P_Graphics_setup_main();
    P_Graphics_assignBuffer(MAIN, (u16*)VRAM_A, 256, 192);

    FillScreen(MAIN, GREEN);
    FillRectangle(MAIN, 1, 100, 1, 100, RGB15(31, 0, 0));
    DrawHorizontalLine(MAIN, 30, 200, 120, RGB15(0, 0, 0));
    DrawVerticalLine(MAIN, 40, 180, 220, RGB15(0, 0, 15));
    DrawRectangle(MAIN, 30, 120, 110, 200, RGB15(31, 31, 0));


    for (;;)
        ;

    return 0;
}
