#ifndef HOMINGMISSILE_H_
#define HOMINGMISSILE_H_

#include "../ShootMii.h"

namespace shootmii{

const int HOMING_GROUND_EXPLOSION_WIDTH(64);
const int HOMING_GROUND_EXPLOSION_HEIGHT(64);
const int HOMING_GROUND_EXPLOSION_DEPTH(10);
const int HOMING_GROUND_EXPLOSION_DURATION(28);

const int HOMING_AIR_EXPLOSION_WIDTH(48);
const int HOMING_AIR_EXPLOSION_HEIGHT(48);
const int HOMING_AIR_EXPLOSION_DEPTH(0);
const int HOMING_AIR_EXPLOSION_DURATION(12);

const int HOMING_HIT_EXPLOSION_WIDTH(64);
const int HOMING_HIT_EXPLOSION_HEIGHT(64);
const int HOMING_HIT_EXPLOSION_DEPTH(0);
const int HOMING_HIT_EXPLOSION_DURATION(16);

class HomingMissile : public Ammo {
public:
	HomingMissile(
		const float angle,
		Wind* wind,
		GRRLIB_texImg* ammoLook,
		Player* owner,
		Terrain* terrain,
		Manager* manager,
		const float vInitX = DEFAULT_POWER,
		const float vInitY = DEFAULT_POWER,
		const float xInit = 0,
		const float yInit = 0);
	Animation* destruction(explosionType _type, Player* _playerHit = NULL);
};

}

#endif /* HOMINGMISSILE_H_ */