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


typedef enum
{
    SOUND_EFFECT_ATTACK,
    SOUND_EFFECT_BLOCK,
    SOUND_EFFECT_HURT,
    SOUND_EFFECT_MOVE,
    SOUND_EFFECT_JUMP
} SoundEffect;


void init_sound();

void play_music();

void stop_music();

void play_sound_effect(SoundEffect sound);


#endif // __SOUND_H
