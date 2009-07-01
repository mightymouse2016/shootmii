#ifndef CANNONBALL_H_
#define CANNONBALL_H_

#include "../ShootMii.h"

namespace shootmii {

class CannonBall: public Ammo {
public:
	CannonBall(
			const float _angle,
			Wind* wind,
			GRRLIB_texImg* _ammoLook,
			Player* _owner,
			const float _vInitX = DEFAULT_POWER,
			const float _vInitY = DEFAULT_POWER,
			const float _xInit = 0,
			const float _yInit = 0);
	void draw() const;
};

}

#endif /* CANNONBALL_H_ */
