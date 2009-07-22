#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "../ShootMii.h"

namespace shootmii{

class Animation : public Rectangle{
private:
	int t;
	int loops; // -1 -> infinite
	int spriteSlow;
	int duration;
	float timeStep; // example : originX = (*calcX)(t*timeStep)
	Function* calcX;
	Function* calcY;
public:
	Animation(
		GRRLIB_texImg* tiles,
		const float originX,
		const float originY,
		const int width,
		const int height,
		const int duration,
		const int spriteSlow = 1,
		const int loops = 1,
		Function* calcX = new NullFunction,
		Function* calcY = new NullFunction,
		float timeStep = .1);
	~Animation();
	void compute();
	bool isFinished();
};

}

#endif /* ANIMATION_H_ */
