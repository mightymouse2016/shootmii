#ifndef SUN_H_
#define SUN_H_

#include "../ShootMii.h"

namespace shootmii{

const float SUN_LIGHT_INFLUENCE(0.9); // 0 -> 1
const float SUN_SLOW(0.001);
const int SUN_WIDTH(64);
const int SUN_HEIGHT(64);

class Sun : public Rectangle{
public:
	Sun();
	void init();
	void compute();
};

}

#endif /*SUN_H_*/
