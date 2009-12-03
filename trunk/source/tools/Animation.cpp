#include "../ShootMii.h"

namespace shootmii {

Animation::Animation(
		const LayerPriority _layer,
		GRRLIB_texImg* _tiles,
		const float _originX,
		const float _originY,
		const float _radial,
		const float _angle,
		const float _rectangleAngle,
		Polygon* _father,
		const int _width,
		const int _height,
		const int _duration,
		const int _spriteSlow,
		const int _loops,
		Function* _calcX,
		Function* _calcY,
		const float _step,
		const bool _fadeOut) :
	Rectangle(_layer, _width,_height,_originX,_originY, _radial, _angle, _rectangleAngle, true, true, _tiles, _father, 0, _width, _height),
	Timer(_spriteSlow,_step),
	loops(_loops),
	duration(_duration),
	fadeOut(_fadeOut),
	calcX(_calcX),
	calcY(_calcY)
{
	// NOTHING TO DO
}

Animation::~Animation(){
	delete calcX;
	delete calcY;
}

void Animation::compute(){
	Timer::compute();
	if (timeIsOver() && loops) {
		spriteIndex++;
	}
	if (spriteIndex == duration-1) {
		loops--;
		if (loops) spriteIndex = 0;
	}
	if (calcX) originX = (*calcX)(getT());
	if (calcY) originY = (*calcY)(getT());
}

bool Animation::isFinished(){
	if (loops == 0) return true;
	return false;
}

}
