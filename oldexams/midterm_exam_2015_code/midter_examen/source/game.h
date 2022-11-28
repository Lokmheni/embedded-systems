/////////////////////////////////////////////////////////
////	DO NOT MODIFY THIS FILE
/////////////////////////////////////////////////////////

#ifndef GAME_H_
#define GAME_H_

#include <nds.h>

#define BLACK	ARGB16(1,0,0,0)
#define WHITE	ARGB16(1,31,31,31)
#define RED		ARGB16(1,31,0,0)
#define GREEN	ARGB16(1,0,31,0)
#define BLUE	ARGB16(1,0,0,31)
#define YELLOW	ARGB16(1,31,31,0)
#define MAGENTA	ARGB16(1,31,0,31)
#define TRANSPARENT	ARGB16(0,0,0,0)


/*
 * initGame:
 * This function initializes the game. It can be called several times, and each
 * time it will restart the game. It generates a random set of 6x8 buttons and draws
 * them in the screen
 * IMPORTANT: It requires the correct implementation of the function
 * fill_32x32_button(...) prototyped in grahpics_sub.h
 */
void initGame();

/*
 * playerPlaysButton:
 * This function is called when the player has touched one of the 24x24-pixel central
 * square of a button. The input number indicates which button has been touched. Buttons are
 * ordered from 0 to 47 starting from the top left corner of the screen
 */
void playerPlaysButton(int button);

void changeColor();

#endif /* GAME_H_ */
