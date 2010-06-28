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
const int BONUS_LIFE_DURATION(8);
const int BONUS_LIFE_ANIMATION_SLOW(7);

const int BONUS_GUIDED_WIDTH(16);
const int BONUS_GUIDED_HEIGHT(16);
const int BONUS_GUIDED_DURATION(7);
const int BONUS_GUIDED_ANIMATION_SLOW(5);

const int BONUS_POISON_WIDTH(28);
const int BONUS_POISON_HEIGHT(24);
const int BONUS_POISON_DURATION(18);
const int BONUS_POISON_ANIMATION_SLOW(7);

const int BONUS_POTION_WIDTH(16);
const int BONUS_POTION_HEIGHT(24);
const int BONUS_POTION_DURATION(12);
const int BONUS_POTION_ANIMATION_SLOW(5);

const int BONUS_CROSS_HAIR_WIDTH(24);
const int BONUS_CROSS_HAIR_HEIGHT(24);
const int BONUS_CROSS_HAIR_DURATION(12);
const int BONUS_CROSS_HAIR_ANIMATION_SLOW(5);

const int BONUS_SHIELD_WIDTH(24);
const int BONUS_SHIELD_HEIGHT(24);
const int BONUS_SHIELD_DURATION(40);
const int BONUS_SHIELD_ANIMATION_SLOW(1);

const int BONUS_SPEED(30);
const int BONUS_OSCILLATIONS_RANGE(100);
const int BONUS_OSCILLATIONS_CENTER(100);

// TODO restaurer la probabilité à 30*60
const int BONUS_PROBABILITY (1*60); // apparition toutes les 30*60frames = 30 secondes en moyenne

const int BONUS_X(302);
const int BONUS_Y(SCREEN_HEIGHT-SCORE_PANEL_HEIGHT/2-15);

const int LASER_TIME(60*15);

enum BonusType{
	HOMING,
	LIFE_RECOVERY,
	GUIDED,
	POISON,
	POTION,
	CROSS_HAIR,
	SHIELD,
	
	NUMBER_OF_BONUSES // Pour les random
};

class Bonus : public Animation{
private:
	BonusType type;
	bool immediate;
	bool finished;
	bool possessed;
public:
	static int numberOfBonus;
	Bonus(
		BonusType type,
		bool immediate,
		GRRLIB_texImg* image,
		const int width,
		const int height,
		const int duration,
		const int slow,
		Function* calcX);
	BonusType getType() const;

	bool isFinished() const;
	bool isPossessed() const;
	bool isImmediate() const;

	void finish();
	void possess();

	void compute();
};

Bonus* randomBonus();

}

#endif /* BONUS_H_ */
