#ifndef CLOUD_H_
#define CLOUD_H_

#include "../ShootMii.h"

namespace shootmii {

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
	int t;
	int slow;
public:
	Cloud(Wind* wind, GRRLIB_texImg* image, const int width, const int height);
	void updateT();
	void updateX();
	void randomX();
	void randomY();
	void init();
};

}

#endif /*CLOUD_H_*/
