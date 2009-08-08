#ifndef BONUS_H_
#define BONUS_H_

#include "../ShootMii.h"

namespace shootmii{

const int BONUS_HOMING_WIDTH(16);
const int BONUS_HOMING_HEIGHT(16);
const int BONUS_HOMING_DURATION(7);
const int BONUS_HOMING_ANIMATION_SLOW(5);

const int BONUS_LIFE_WIDTH(28);
const int BONUS_LIFE_HEIGHT(24);
const int BONUS_LIFE_DURATION(9);
const int BONUS_LIFE_ANIMATION_SLOW(5);

const int BONUS_SPEED(30);
const int BONUS_OSCILLATIONS_RANGE(100);
const int BONUS_OSCILLATIONS_CENTER(100);

const int BONUS_PROBABILITY (60); // apparition toutes les 30*60frames = 30 secondes en moyenne

enum BonusType{
	HOMING,
	LIFE_RECOVERY,
	NUMBER_OF_BONUS
};

class Bonus : public Animation{
private:
	BonusType type;
	bool finished;
public:
	static int numberOfBonus;
	Bonus(
		BonusType type,
		GRRLIB_texImg* image,
		const int width,
		const int height,
		const int duration,
		const int slow,
		Function* calcX);
	BonusType getType() const;
	void finish();
	bool isFinished() const;
};

Bonus* randomBonus();

}

#endif /* BONUS_H_ */
