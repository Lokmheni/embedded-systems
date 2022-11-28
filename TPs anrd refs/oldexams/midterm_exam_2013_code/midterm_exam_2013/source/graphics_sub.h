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
 * 	configures the background BG2 in rotoscale mode and transfers the
 * 	corresponding image (bottom.png) to the background using a pixel depth
 * 	of 8 bits
 */
void configBG2_Sub();

/*
 * configBG0_Sub:
 * 	- configures the background BG0 in tiled mode using a 32x32 grid with 8bit
 *    pixels
 *  - transfer 2 bi-color custom tiles to the tile base
 *  - assigns the color to the 2 used components of the palette
 *  - composes the map to display a separation of 16 pixels (2 tiles) between
 *    the 4 regions
 */
void configBG0_Sub();

#endif /* GRAPHICS_SUB_H_ */
