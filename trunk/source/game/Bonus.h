#ifndef BONUS_H_
#define BONUS_H_

#include "../ShootMii.h"

namespace shootmii{

const int BONUS_WIDTH(16);
const int BONUS_HEIGHT(16);
const int BONUS_DURATION(7);
const int BONUS_SPEED(30);
const int BONUS_ANIMATION_SLOW(5);
const int BONUS_OSCILLATIONS_RANGE(100);
const int BONUS_OSCILLATIONS_CENTER(100);

enum BonusType{
	HOMING,
	LIFE_RECOVERY
};

class Bonus : public Animation{
private:
	BonusType type;
public:
	Bonus();
	void compute();
};

}

#endif /* BONUS_H_ */
