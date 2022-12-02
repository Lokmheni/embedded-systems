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


void get_input(RequestedAction* action, RequestedMovement* movement);


void get_touch_input();


#endif // __INPUT_H_
