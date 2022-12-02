/**
 * @file sound.h
 * @author Simon Thür and Lokman Mheni
 * @brief sound controller
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __SOUND_H
#define __SOUND_H


enum SoundEffect
{
    ATTACK,
    BLOCK,
    HURT,
    MOVE,
    JUMP
};


void init_sound();

void play_music();

void stop_music();

void play_sound_effect( SoundEffect sound );


#endif  // __SOUND_H
