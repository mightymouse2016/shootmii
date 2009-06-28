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

class Cloud {
private:
	Wind* wind;
	GRRLIB_texImg* cloudImg;
	int cloudWidth;
	int cloudHeight;
	int t;
	int slow;
	int screenX;
	int screenY;
public:
	Cloud(Wind* _wind, GRRLIB_texImg* _cloudImg, const int _cloudWidth, const int _cloudHeight);
	void updateT();
	void updateX();
	void randomX();
	void randomY();
	void init();
	void draw() const;
};

}

#endif /*CLOUD_H_*/
