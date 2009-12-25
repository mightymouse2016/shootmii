#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "../ShootMii.h"

namespace shootmii{

class Animation : public Rectangle, public Timer{
protected:
	int loops; // <0 = infinite
	int duration;
	bool fadeOut;
	Function* calcX;
	Function* calcY;
	u32	fadeOutStartColor;
	u32 fadeOutEndColor;
public:
	Animation(
		const LayerPriority layer,
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
		const float step = DEFAULT_TIME_STEP,
		const bool fadeOut = false,
		const u32 fadeOutStartColor = WHITE,
		const u32 fadeOutEndColor = TRANSPARENT);
	~Animation();
	float getProgress() const;
	virtual void compute();
	virtual bool isFinished() const;
};

}

#endif /* ANIMATION_H_ */
