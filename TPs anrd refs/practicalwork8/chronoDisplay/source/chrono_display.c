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

void updateChronoDisp(u16* map, int min, int sec, int msec)
{
    memset(map, 11 * 32, 1024 * 2);
#define X 0
#define Y 10

    // min
    printDigit(map, min / 10, X + 0, Y);
    printDigit(map, min % 10, X + 4, Y);
    // doppelpunkt
    int i, j;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 8; j++)
            map[X + 8 + i + 32 * (Y + j)] = i + (4 * j) + (32 * 10) + 2;
    // sec
    printDigit(map, sec / 10, X + 10, Y);
    printDigit(map, sec % 10, X + 14, Y);
    // punktfor (i = 0; i < 2; i++)
    for (i = 0; i < 2; i++)
        for (j = 0; j < 8; j++)
            map[X + 18 + i + (32 * (Y + j))] = i + (4 * j) + (32 * 10);


    // msec
    printDigit(map, msec / 100, X + 20, Y);
    printDigit(map, (msec % 100) / 10, X + 24, Y);
    printDigit(map, msec % 10, X + 28, Y);
}


void changeColorDisp(uint16 b, uint16 c)
{
    BG_PALETTE[0x00] = c;
    BG_PALETTE[0xff] = b;
}
