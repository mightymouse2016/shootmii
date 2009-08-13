#ifndef GUIDEDMISSILE_H_
#define GUIDEDMISSILE_H_

#include "../ShootMii.h"

namespace shootmii{

const int GUIDED_GROUND_EXPLOSION_WIDTH(64);
const int GUIDED_GROUND_EXPLOSION_HEIGHT(64);
const int GUIDED_GROUND_EXPLOSION_DEPTH(10);
const int GUIDED_GROUND_EXPLOSION_DURATION(28);

const int GUIDED_AIR_EXPLOSION_WIDTH(48);
const int GUIDED_AIR_EXPLOSION_HEIGHT(48);
const int GUIDED_AIR_EXPLOSION_DEPTH(0);
const int GUIDED_AIR_EXPLOSION_DURATION(12);

const int GUIDED_HIT_EXPLOSION_WIDTH(64);
const int GUIDED_HIT_EXPLOSION_HEIGHT(64);
const int GUIDED_HIT_EXPLOSION_DEPTH(0);
const int GUIDED_HIT_EXPLOSION_DURATION(16);

const float GUIDED_SPEED(7);
const float GUIDED_SPIN_ANGLE(PI/16);
const float GUIDED_ROTATION_STEP(PI/32);
const float GUIDED_ACTIVATION_DELAY(30*DEFAULT_TIME_STEP); // 1/2 seconde

class GuidedMissile : public Ammo {
private:
	bool active;
public:
	GuidedMissile(
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
	void deleteMe();
	void rotateRight();
	void rotateLeft();
	void compute();
};

}

#endif /* GUIDEDMISSILE_H_ */
