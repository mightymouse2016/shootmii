#include "../ShootMii.h"

namespace shootmii {

Animation::Animation(
		GRRLIB_texImg* _tiles,
		const float _originX,
		const float _originY,
		const int _width,
		const int _height,
		const int _duration,
		const int _spriteSlow,
		const int _loops,
		Function* _calcX,
		Function* _calcY) :
	Rectangle(_width,_height,_originX,_originY, 0, 0, 0, 0, _tiles, NULL, 0, _width, _height),
	Timer(_spriteSlow),
	loops(_loops),
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
	if (timeIsOver()) spriteIndex++;
	if (spriteIndex == duration) {
		loops--;
		spriteIndex = 0;
	}
	if (dynamic_cast<NullFunction*>(calcX) == NULL) originX = (*calcX)(getT());
	if (dynamic_cast<NullFunction*>(calcY) == NULL) originY = (*calcY)(getT());
	Timer::compute();
}

bool Animation::isFinished(){
	if (loops == -1) return false;
	if (loops == 0) return true;
	return false;
}

}
