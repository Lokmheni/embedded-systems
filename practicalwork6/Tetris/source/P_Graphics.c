#include "P_Graphics.h"

#include <nds.h>


void P_Graphics_setup_main()
{
#ifdef FB0
    // Graphics (Part 1)
    // Set the mode to FB0
    REG_DISPCNT = MODE_FB0;

    // Set the coresponding VRAM bank
    VRAM_A_CR = VRAM_A_LCD | VRAM_ENABLE;

#endif

#ifdef ROTOSCALE
    // Graphics (Part 2)
#endif

#ifdef TILES
    // Graphics (Part 3)
#endif
}

void P_Graphics_assignBuffer(enum BUFFER_TYPE bT, u16* buffer, int w, int h)
{
    switch (bT)
        {
        case MAIN:
            P_Graphics_mainBuffer = buffer;
            P_Graphics_mainW      = w;
            P_Graphics_mainH      = h;
            break;
        case SUB:
            P_Graphics_subBuffer = buffer;
            P_Graphics_subW      = w;
            P_Graphics_subH      = h;
            break;
        }
}

void FillScreen(enum BUFFER_TYPE t, u16 color)
{
    int i;
    switch (t)
        {
        case MAIN:
            // Fill the whole screen (256*192) with the given color
            for (i = 0; i < P_Graphics_mainH * P_Graphics_mainW; i++)
                P_Graphics_mainBuffer[i] = color;
            break;
        case SUB:

            break;
        default:
            return;
            break;
        }
}

void FillRectangle(enum BUFFER_TYPE bT, int top, int bottom, int left,
                   int right, u16 color)
{
    // since we only use framebuffer for the moment...
    switch (bT)
        {
        case MAIN:
            int i, j;
            for (i = top; i <= bottom; i++)
                {
                    for (j = left; j < right; j++)
                        {
                            P_Graphics_mainBuffer[P_Graphics_mainW * i + j] =
                                color;
                        }
                }
            break;
        default:
            break;
        }
}

void DrawHorizontalLine(enum BUFFER_TYPE bT, int x, int x2, int y, u16 color)
{
    switch (bT)
        {
        case MAIN:
            int i;
            for (i = x % P_Graphics_mainW; i < x2 % P_Graphics_mainW; i++)
                {
                    P_Graphics_mainBuffer[y * P_Graphics_mainW + i] = color;
                }
            break;

        default:
            break;
        }
}
void DrawVerticalLine(enum BUFFER_TYPE bT, int y, int y2, int x, u16 color)
{
    switch (bT)
        {
        case MAIN:
            int i;
            for (i = (y % P_Graphics_mainH); i < (y2 % P_Graphics_mainH); i++)
                {
                    P_Graphics_mainBuffer[P_Graphics_mainW * i + x] = color;
                }
            break;

        default:
            break;
        }
}

void DrawRectangle(enum BUFFER_TYPE bT, int top, int bottom, int left,
                   int right, u16 color)
{
    DrawVerticalLine(bT, top, bottom, left, color);
    DrawVerticalLine(bT, top, bottom, right, color);
    DrawHorizontalLine(bT, left, right, top, color);
    DrawHorizontalLine(bT, left, right, bottom, color);
}
