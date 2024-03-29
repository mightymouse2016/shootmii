#ifndef CLOUD_H_
#define CLOUD_H_

#include "GRRLIB.h"
#include <cstdlib>
#include "../math/Rectangle.h"

namespace shootmii {

class Wind;

const int CLOUD_SPACE(25); // 0->100

const int FRONT_CLOUD_SPEED_COEF(4);
const int FRONT_CLOUD_HEIGHT(64);
const int FRONT_CLOUD_WIDTH(64);

const int BACK_CLOUD_SPEED_COEF(1);
const int BACK_CLOUD_HEIGHT(48);
const int BACK_CLOUD_WIDTH(64);

class Cloud : public Rectangle{
private:
	Wind* wind;
public:
	Cloud(
		const LayerPriority layer,
		Wind* wind,
		GRRLIB_texImg* image,
		const int width,
		const int height);
	void compute();
	void randomX();
	void randomY();
	void init();
};

}

#endif /*CLOUD_H_*/
