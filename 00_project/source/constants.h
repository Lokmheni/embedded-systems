/**
 * @file constants.h
 * @author Simon Thür and Lokman Mheni
 * @brief Defines and constants
 * @version 0.1
 * @date 2022-12-04
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __CONSTANS_H
#define __CONSTANS_H

//===================================================================
// SCREEN
//===================================================================
// screen anad sprite width used in game.c to limit player positions
#define SCREEN_WIDTH  256
#define SCREEN_HEIGHT 192

#define SPRITE_WIDTH  32
#define SPRITE_HEIGHT 32

#define GAME_FLOOR_HEIGHT 32 // subject to change, just a placehold value
#define SPRITE_FLOOR_HEIGHT                                                    \
    (SCREEN_HEIGHT - (GAME_FLOOR_HEIGHT + SPRITE_HEIGHT))


//===================================================================
// GAME
//===================================================================
#define SPEED          5 // number of pixels to move per game iteration
#define SPEED_BLOCKING (SPEED / 2)
#define JUMP_SPEED     18
#define GRAVITY        2 // to see in relation to jump_speed

#define DAMAGE_NORMAL  5
#define DAMAGE_SPECIAL 10
#define MAX_HEALTH     100
#define BLOCK_FACTOR   2

#define SPRITE_START_POS 10 // distance from left screen border

#define ATTACK_DELAY_FREQ         10 // normal attack, movement impediment: 1/10=10ms
#define SPECIAL_ATK_CHARGEUP_FREQ 3 // special attack, mov impediment: 1/3=333ms


//===================================================================
// CONTROLS
//===================================================================
#define KEY_MOVE_LEFT      KEY_LEFT
#define KEY_MOVE_RIGHT     KEY_RIGHT
#define KEY_JUMP           KEY_A
#define KEY_ATTACK         KEY_B
#define KEY_BLOCK          KEY_X
#define KEY_SPECIAL_ATTACK KEY_Y

#endif // __CONSTANS_H
