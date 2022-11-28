#ifndef GRAPHICS_MAIN_H_
#define GRAPHICS_MAIN_H_

#include <nds.h>

/*
 * configureGraphics_Main:
 * configures the MAIN graphical engine to work in FrameBuffer mode and sets-up
 * the corresponding VRAM bank accordingly
 */
void configureGraphics_Main();

/*
 * fillRegion_Main:
 * fills a given region of the screen with a given color. The input parameters
 * are the following:
 * 	 int region = specifies the region to fill (0, 1, 2 or 3)
 *   u16 color = color to use (i.e. RED or ARGB16(1,15,0,0))
 */
void fillRegion_Main(int region, u16 color);


#endif /* GRAPHICS_MAIN_H_ */
