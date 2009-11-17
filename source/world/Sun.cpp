#include "../ShootMii.h"

namespace shootmii{

Sun::Sun(float _a, float _b) :
	Rectangle(
		SUN_LAYER,
		SUN_WIDTH,
		SUN_HEIGHT,
		SCREEN_WIDTH/2,
		(SCREEN_HEIGHT-SCORE_PANEL_HEIGHT)*(static_cast<float>(TERRAIN_DOWN_LIMIT)/100),
		0,
		-PI/2,
		0,
		false,
		false,
		App::imageBank->get(TXT_SUN)),
		a(_a),
		e(sqrt(_b*_b-_a*_a)/_b)
{

}

void Sun::compute(){
	radial = a/sqrt(fabs(1-e*e*cos(angle+PI/2)*cos(angle+PI/2)));
	if (angle >= 0) angle = -PI;
	else angle += SUN_SLOW;
}

void Sun::init(){
	angle = - static_cast<float>(rand()%180)*PI/180;
}

}
