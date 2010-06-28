#ifndef SOUNDBANK_H_
#define SOUNDBANK_H_

#include <vector>
#include <utility>
#include <mp3player.h>
#include "asndlib.h"

namespace shootmii{

enum SoundEffect {
	AMMO_SHOT,
	BIG_BOMB_SHOT,
	AMMO_BOOM,
	BIG_BOMB_BOOM,

	NUMBER_OF_SOUNDS
};

class SoundBank{
private:
	std::vector<std::pair<void*,int> > allSounds;
public:
	SoundBank();
	void play(SoundEffect soundEffectName, const float volume = 100); //1->100
	void init();
};

// TO PLAY A MP3 :
//MP3Player_PlayBuffer(Artillaryexp, Artillaryexp_size, NULL);

}

#endif /* SOUNDBANK_H_ */
