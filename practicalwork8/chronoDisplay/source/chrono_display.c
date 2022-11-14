#include "chrono_display.h"

#include <nds/arm9/background.h>

void printDigit(u16* map, int number, int x, int y)
{
    int i, j;
    for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 8; j++)
                {
                    map[(32 * (y + j)) + (x + i)] = 32 * number + (4 * j) + i;
                }
        }
}

void updateChronoDisp(u16* map, int min, int sec, int msec) {}


void changeColorDisp(uint16 b, uint16 c) {}
