/////////////////////////////////////////////////////////
////	DO NOT MODIFY THIS FILE
/////////////////////////////////////////////////////////
#ifndef GRAPHICS_SUB_H_
#define GRAPHICS_SUB_H_
#include <nds.h>

/*
 * configureGraphics_Sub:
 *  configures the SUB engine in MODE 5 and activates BG2. It also sets-up the
 *  corresponding VRAM bank
 */
void configureGraphics_Sub();

/*
 * configBG2_Sub:
 * 	configures the background BG2 in extended rotoscale mode using the 16-bit pixel mode
 * (i.e. emulating framebuffer mode)
 */
void configBG2_Sub();

/*
 * fillScreen_Sub():
 * This function fills the full screen using the input color (color)
 */
void fillScreen_Sub(u16 color);

/*
 * fill_32x32_button:
 * draws a 32x32-pixel square starting by the top-left corner given by the coordinates (x,y)
 * and painted with the color 'out'. Then it draws a concentric 24x24-pixel square with the
 * color 'in'. Check example given within the function for more details.
 */
void fill_32x32_button(unsigned int top, unsigned int left, u16 out, u16 in);

#endif /* GRAPHICS_SUB_H_ */
