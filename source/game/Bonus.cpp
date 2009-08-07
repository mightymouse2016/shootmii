#include "../ShootMii.h"

namespace shootmii {

Bonus::Bonus(
		BonusType _type,
		GRRLIB_texImg* _image,
		const int _width,
		const int _height,
		const int _duration,
		const int _slow) :
			Animation(
				_image,0,0,0,0,0,NULL,
				_width,
				_height,
				_duration,
				_slow,
				-1,
				new Affine(BONUS_SPEED),
				new Cosinus(BONUS_OSCILLATIONS_RANGE/2,1,BONUS_OSCILLATIONS_CENTER),
				.01),
				type(_type),
				finished(false)
{
	// NOTHING TO DO
}

BonusType Bonus::getType() const{
	return type;
}

void Bonus::finish(){
	finished = true;
}

bool Bonus::isFinished() const{
	return (finished || (originX - getWidth()/2 > SCREEN_WIDTH));
}

Bonus* randomBonus(){
	int _type = rand()%NUMBER_OF_BONUS;
	switch(_type){
		case HOMING:
			return new Bonus(
				static_cast<BonusType>(_type),
				App::imageBank->get(TXT_BONUS_HOMING),
				BONUS_HOMING_WIDTH,
				BONUS_HOMING_HEIGHT,
				BONUS_HOMING_DURATION,
				BONUS_HOMING_ANIMATION_SLOW);
		case LIFE_RECOVERY:
			return new Bonus(
				static_cast<BonusType>(_type),
				App::imageBank->get(TXT_BONUS_LIFE),
				BONUS_LIFE_WIDTH,
				BONUS_LIFE_HEIGHT,
				BONUS_LIFE_DURATION,
				BONUS_LIFE_ANIMATION_SLOW);
		default:
			return NULL;
	}
}

}
