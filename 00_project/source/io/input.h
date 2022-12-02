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


enum RequestedAction
{
    ATTACK,
    SPECIAL_ATTACK,
    BLOCK,
    JUMP,
    NONE
};

enum RequestedMovement
{
    LEFT,
    RIGHT,
    NONE
};

enum TouchInput
{
    NONE,
    MULTI_PLAYER,
    SINGLE_PLAYER,
    PLAY
};


void get_input( RequestedAction* action, RequestedMovement* movement );


void get_touch_input();


#endif  // __INPUT_H_
