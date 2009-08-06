#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "../ShootMii.h"

namespace shootmii{

class Animation : public Rectangle, public Timer{
private:
	int loops; // <0 = infinite
	int duration;
	Function* calcX;
	Function* calcY;
public:
	Animation(
		GRRLIB_texImg* tiles,
		const float originX,
		const float originY,
		const float radial,
		const float angle,
		const float rectangleAngle,
		Polygon* father,
		const int width,
		const int height,
		const int duration,
		const int spriteSlow = 1,
		const int loops = 1,
		Function* calcX = NULL,
		Function* calcY = NULL,
		float step = DEFAULT_TIME_STEP);
	~Animation();
	void compute();
	bool isFinished();
};

}

#endif /* ANIMATION_H_ */
