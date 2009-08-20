#include "../ShootMii.h"

namespace shootmii {

SoundBank::SoundBank(){
	// NOTHING TO DO
}

void SoundBank::play(SoundEffect soundEffectName, const float volumePercentage){
	int volume = (volumePercentage*(MAX_VOLUME-MIN_VOLUME)/100)+MIN_VOLUME;
	void* sound =  allSounds[soundEffectName].first;
	int length = allSounds[soundEffectName].second;
	ASND_SetVoice(ASND_GetFirstUnusedVoice(), VOICE_MONO_8BIT, 22050, 0, sound, length, volume, volume, NULL);
}

void SoundBank::init(){
	allSounds.reserve(NUMBER_OF_SOUNDS);
	allSounds[AMMO_SHOT] = pair<void*,int>((void*)ammo_shot,ammo_shot_size);
	allSounds[BIG_BOMB_SHOT] = pair<void*,int>((void*)big_bomb_shot,big_bomb_shot_size);
	allSounds[AMMO_BOOM] = pair<void*,int>((void*)ammo_boom,ammo_boom_size);
	allSounds[BIG_BOMB_BOOM] = pair<void*,int>((void*)big_bomb_boom,big_bomb_boom_size);
}

}
