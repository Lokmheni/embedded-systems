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


void Audio_Init()
{
	//Init the sound library
	mmInitDefaultMem((mm_addr)soundbank_bin);
	//Load module
	mmLoad(MOD_MAINTITLE);
	//Load effect
	//mmLoadEffect(SFX_MAINTITLE);
	mmLoadEffect(SFX_PUNCH);
}

void Audio_PlaySoundEX( int i )
{
	//Declare a sound effect
	mm_sound_effect sound;
	//Set the id of the sound effect with the input parameter
	sound.id = i;
	//Set the rate to the default one (1024)
	sound.rate = 1024;
	//Set the volume to the maximum (range 0...255)
	sound.volume = 255;
	//Set the panning depending on the effect (0-left....255-right)
	if(i == SFX_PUNCH)
		sound.panning = 0;
	if(i == SFX_BOING)
		sound.panning = 255;

	//Play the effect using the sound structure
	mmEffectEx(&sound);
}

void Audio_PlayMusic()
{
	//Start playing music in a loop
	mmStart(MOD_MAINTITLE, MM_PLAY_LOOP);
	//Set module volume to 512 (range 0...1024) using the function mmSetModuleVolume(...)
	mmSetModuleVolume(512);
}



void init_sound() {
	//Init the sound library
	mmInitDefaultMem((mm_addr)soundbank_bin);
	//Load module
	mmLoad(MOD_MAINTITLE);
	//Load effect
	//mmLoadEffect(SFX_MAINTITLE);
	mmLoadEffect(SFX_PUNCH);
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
	//Declare a sound effect
	//mm_sound_effect sound;
	//Set the id of the sound effect with the input parameter
	//sound.id = i;
	//Set the rate to the default one (1024)
	//sound.rate = 1024;
	//Set the volume to the maximum (range 0...255)
	//sound.volume = 255;
	//Set the panning depending on the effect (0-left....255-right)
	//if(i == SFX_PUNCH)
	//	sound.panning = 0;
	//if(i == SFX_BOING)
	//	sound.panning = 255;
	//Play the effect using the sound structure
	if(sound == SOUND_EFFECT_ATTACK)
		mmEffect(SFX_PUNCH);
}
