#ifndef GAME_H_
#define GAME_H_

#include <nds.h>

#define RED		ARGB16(1,31,0,0)
#define GREEN	ARGB16(1,0,31,0)
#define BLUE 	ARGB16(1,0,0,31)
#define YELLOW	ARGB16(1,31,31,0)
#define GREY	ARGB16(1,25,25,25)
#define BLACK	ARGB16(1,0,0,0)

/*
 * initGame:
 * 	Initializes the game logic by setting up the random generator and the first
 * 	color sequence
 */
void initGame();

/*
 * hideColorSequence:
 *  hides the color sequence from the upper screen by filling all the regions
 *  with BLACK. This function depends on the implementation of the function
 *  fillRegion_Main(...) in order to work
 */
void hideColorSequence();

/*
 * tryColor:
 *  this function checks if the input color is the correct one in the secret
 *  sequence. The function unveils the colored region of the secret sequence
 *  in the upper screen if the introduced color is correct. Otherwise, it
 *  regenerates another sequence and displays it for 2 seconds.
 */
void tryColor(u16 color);

#endif /* GAME_H_ */
