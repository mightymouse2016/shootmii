#ifndef SUN_H_
#define SUN_H_

#include "../ShootMii.h"

namespace shootmii{

const float SUN_LIGHT_INFLUENCE(0.7); // 0 -> 1
const float SUN_SLOW(0.0003);
const int SUN_WIDTH(64);
const int SUN_HEIGHT(64);

const int SUN_HORIZONTAL_RADIAL((SCREEN_WIDTH-SUN_WIDTH)/2);
const int SUN_VERTICAL_RADIAL((SCREEN_HEIGHT-SCORE_PANEL_HEIGHT)*(static_cast<float>(CENTER_TERRAIN+AMPLITUDE_TERRAIN)/100)-SUN_HEIGHT/2);

class Sun : public Rectangle{
private:
	// Coefficients de la trajectoire élliptique
	float a;
	float e;
public:
	Sun(float a = SUN_HORIZONTAL_RADIAL, float b = SUN_VERTICAL_RADIAL);
	void init();
	void compute();
};

}

#endif /*SUN_H_*/
