/**
 * @file input.h
 * @author Simon Thür and Lokman Mheni
 * @brief
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __INPUT_H_
#define __INPUT_H_

#include <nds.h>
#include "sound.h"

#define SCREEN_WIDTH	256
#define	SCREEN_HEIGHT	192

#define	SPRITE_WIDTH	32
#define	SPRITE_HEIGHT	32


typedef enum
{
    REQ_ACTION_ATTACK,
    REQ_ACTION_SPECIAL_ATTACK,
    REQ_ACTION_BLOCK,
    REQ_ACTION_JUMP,
    REQ_ACTION_NONE
} RequestedAction;

typedef enum
{
    REQ_MOVE_LEFT,
    REQ_MOVE_RIGHT,
    REQ_MOVE_NONE
} RequestedMovement;

typedef enum
{
    TOUCH_INPUT_NONE,
    TOUCH_INPUT_MULTI_PLAYER,
    TOUCH_INPUT_SINGLE_PLAYER,
    TOUCH_INPUT_PLAY
} TouchInput;


int get_keys();

void manage_key(int key);

void get_input(RequestedAction* action, RequestedMovement* movement);


bool get_touch_input(TouchInput* touchinput);

bool get_touch_to_restart(TouchInput* touchinput);


#endif // __INPUT_H_
