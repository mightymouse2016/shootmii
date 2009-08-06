#include "../ShootMii.h"

namespace shootmii {

Bonus::Bonus() :
	Animation(
			App::imageBank->get(TXT_BONUS_HOMING),
			0,
			0,
			0,
			0,
			0,
			NULL,
			BONUS_WIDTH,
			BONUS_HEIGHT,
			BONUS_DURATION,
			BONUS_ANIMATION_SLOW,
			-1,
			new Affine(BONUS_SPEED),
			new Cosinus(BONUS_OSCILLATIONS_RANGE/2,1,BONUS_OSCILLATIONS_CENTER),
			.01)
{
	type = HOMING; // Pour le moment
}

void Bonus::compute(){
	Animation::compute();
	if (originX > SCREEN_WIDTH) t = 0;
}

}
