#include "../math/Affine.h"
#include "../math/Cosinus.h"
#include "../math/Polygon.h"
#include "../tools/Tools.h"
#include "../App.h"
#include "Bonus.h"
#include "../tools/ImageBank.h"

namespace shootmii {

int Bonus::numberOfBonus = 0;

Bonus::Bonus(
		BonusType _type,
		bool _immediate,
		GRRLIB_texImg* _image,
		const int _width,
		const int _height,
		const int _duration,
		const int _slow,
		Function* _calcX) :
			Animation(
				BONUS_LAYER,
				_image,0,0,0,0,0,NULL,
				_width,
				_height,
				_duration,
				_slow,
				-1,
				_calcX,
				new Cosinus(BONUS_OSCILLATIONS_RANGE/2,1,BONUS_OSCILLATIONS_CENTER),
				.01),
			type(_type),
			immediate(_immediate),
			finished(false),
			possessed(false)
{
	numberOfBonus++;
}

BonusType Bonus::getType() const{
	return type;
}

bool Bonus::isFinished() const{
	if (possessed) return finished;
	return (finished || (originX - getWidth()/2 > SCREEN_WIDTH) || (originX + getWidth()/2 < 0));
}

bool Bonus::isPossessed() const{
	return possessed;
}

bool Bonus::isImmediate() const{
	return immediate;
}

void Bonus::finish(){
	finished = true;
}

void Bonus::possess(){
	possessed = true;
	delete calcX;
	delete calcY;
	calcX = NULL;	// NULL : originX inchang�
	calcY = NULL;	// NULL : originY inchang�
}

void Bonus::compute(){
	Animation::compute();
}

Bonus* randomBonus(){
	int _type = rand()%NUMBER_OF_BONUSES;
	Function* calcX;
	if (Bonus::numberOfBonus%2) calcX = new Affine(BONUS_SPEED,-BONUS_HOMING_WIDTH/2);
	else calcX = new Affine(-BONUS_SPEED,SCREEN_WIDTH+BONUS_HOMING_WIDTH/2);
	switch(_type){
		case HOMING:
			return new Bonus(
				static_cast<BonusType>(_type),
				false,
				App::imageBank->get(TXT_BONUS_HOMING),
				BONUS_HOMING_WIDTH,
				BONUS_HOMING_HEIGHT,
				BONUS_HOMING_DURATION,
				BONUS_HOMING_ANIMATION_SLOW,
				calcX);
		case LIFE_RECOVERY:
			return new Bonus(
				static_cast<BonusType>(_type),
				true,
				App::imageBank->get(TXT_BONUS_LIFE),
				BONUS_LIFE_WIDTH,
				BONUS_LIFE_HEIGHT,
				BONUS_LIFE_DURATION,
				BONUS_LIFE_ANIMATION_SLOW,
				calcX);
		case GUIDED:
			return new Bonus(
				static_cast<BonusType>(_type),
				false,
				App::imageBank->get(TXT_BONUS_GUIDED),
				BONUS_GUIDED_WIDTH,
				BONUS_GUIDED_HEIGHT,
				BONUS_GUIDED_DURATION,
				BONUS_GUIDED_ANIMATION_SLOW,
				calcX);
		case POISON:
			return new Bonus(
				static_cast<BonusType>(_type),
				true,
				App::imageBank->get(TXT_BONUS_POISON),
				BONUS_POISON_WIDTH,
				BONUS_POISON_HEIGHT,
				BONUS_POISON_DURATION,
				BONUS_POISON_ANIMATION_SLOW,
				calcX);
		case POTION:
			return new Bonus(
				static_cast<BonusType>(_type),
				true,
				App::imageBank->get(TXT_BONUS_POTION),
				BONUS_POTION_WIDTH,
				BONUS_POTION_HEIGHT,
				BONUS_POTION_DURATION,
				BONUS_POTION_ANIMATION_SLOW,
				calcX);
		case CROSS_HAIR:
			return new Bonus(
				static_cast<BonusType>(_type),
				false,
				App::imageBank->get(TXT_BONUS_CROSS_HAIR),
				BONUS_CROSS_HAIR_WIDTH,
				BONUS_CROSS_HAIR_HEIGHT,
				BONUS_CROSS_HAIR_DURATION,
				BONUS_CROSS_HAIR_ANIMATION_SLOW,
				calcX);
		case SHIELD:
				return new Bonus(
					static_cast<BonusType>(_type),
					false,
					App::imageBank->get(TXT_BONUS_SHIELD),
					BONUS_SHIELD_WIDTH,
					BONUS_SHIELD_HEIGHT,
					BONUS_SHIELD_DURATION,
					BONUS_SHIELD_ANIMATION_SLOW,
					calcX);
		default:
			return new Bonus(
				static_cast<BonusType>(_type),
				true,
				App::imageBank->get(TXT_BONUS_LIFE),
				BONUS_LIFE_WIDTH,
				BONUS_LIFE_HEIGHT,
				BONUS_LIFE_DURATION,
				BONUS_LIFE_ANIMATION_SLOW,
				calcX);
	}
}

}
