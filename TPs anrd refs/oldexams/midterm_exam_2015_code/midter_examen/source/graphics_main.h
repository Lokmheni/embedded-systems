/////////////////////////////////////////////////////////
////	DO NOT MODIFY THIS FILE
/////////////////////////////////////////////////////////
#ifndef GRAPHICS_MAIN_H_
#define GRAPHICS_MAIN_H_

#include <nds.h>

/*
 * configureGraphics_Main:
 * This function sets up the main graphical engine to work in framebuffer mode.
 * It also sets up the corresponding VRAM bank
 */
void configureGraphics_Main();

/*
 * fillScreen_Main:
 * This function fills the full screen with the input color (color)
 */
void fillScreen_Main(u16 color);


#endif /* GRAPHICS_MAIN_H_ */
