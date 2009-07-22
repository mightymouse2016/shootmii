#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "../ShootMii.h"

namespace shootmii{

class Animation : public Rectangle{
private:
	int duration;
public:
	Animation(
		GRRLIB_texImg* _tiles,
		const float _originX,
		const float _originY,
		const int _width,
		const int _height,
		const int _duration);
	void compute();
	bool isFinished();
};

}

#endif /* ANIMATION_H_ */
