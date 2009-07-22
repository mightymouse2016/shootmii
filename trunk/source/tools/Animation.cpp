#include "../ShootMii.h"

namespace shootmii {

Animation::Animation(
		GRRLIB_texImg* _tiles,
		const float _originX,
		const float _originY,
		const int _width,
		const int _height,
		const int _duration) :
	Rectangle(_width,_height,_originX,_originY, 0, 0, 0, 0, _tiles, NULL, 0, _width, _height)
{
	// NOTHING TO DO
}

void Animation::compute(){
	spriteIndex++;
}

bool Animation::isFinished(){
	return (spriteIndex == duration);
}

}
