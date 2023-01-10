/**
 * @file sound.c
 * @author Simon Thür and Lokman Mheni
 * @brief sound controller
 * @version 0.1
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "sound.h"


void init_sound() {
	//Init the sound library
	mmInitDefaultMem((mm_addr)soundbank_bin);
	//Load module
	mmLoad(MOD_MAINTITLE);
	//Load effect
	//mmLoadEffect(SFX_MAINTITLE);
	mmLoadEffect(SFX_PUNCH);
	mmLoadEffect(SFX_BOING);
	mmLoadEffect(SFX_BLOCK);
	mmLoadEffect(SFX_MOVE);
}

void play_music() {
	//Start playing music in a loop
	mmStart(MOD_MAINTITLE, MM_PLAY_LOOP);
	//Set module volume to 512 (range 0...1024) using the function mmSetModuleVolume(...)
	mmSetModuleVolume(512);
}

void stop_music() {
	mmStop();
}

void play_sound_effect(SoundEffect sound) {
	if(sound == SOUND_EFFECT_ATTACK)
		mmEffect(SFX_PUNCH);
	if(sound == SOUND_EFFECT_JUMP)
		mmEffect(SFX_BOING);
	if(sound == SOUND_EFFECT_BLOCK)
		mmEffect(SFX_BLOCK);
	if(sound == SOUND_EFFECT_BLOCK)
		mmEffect(SFX_MOVE);
}
