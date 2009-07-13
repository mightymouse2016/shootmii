#include "../ShootMii.h"

namespace shootmii {

CannonBall::CannonBall(
		const float _angle,
		Wind* wind,
		GRRLIB_texImg* _ammoLook,
		Player* _owner,
		const float _vInitX,
		const float _vInitY,
		const float _xInit,
		const float _yInit) :
	Ammo(
		_angle,
		_ammoLook,
		new PolyDeg2(float(wind->getWindSpeed())*(wind->getWindDirection()*2-1)*WIND_INFLUENCE_ON_AMMO/(2*100* AMMO_WEIGHT ),_vInitX,_xInit),
		new PolyDeg2(-G/(2*AMMO_WEIGHT),-_vInitY,_yInit),
		_owner)
{
	vertices.reserve(5);
	vertices.push_back(Coordinates(8,0));
	vertices.push_back(Coordinates(2,-7));
	vertices.push_back(Coordinates(-8,-7));
	vertices.push_back(Coordinates(-8,7));
	vertices.push_back(Coordinates(2,7));

	// précalculs, passage en coordonnées polaires
	initRadials();
	initThetas();

}

void CannonBall::draw() const {
	GRRLIB_DrawImg(screenX,screenY,*ammoLook,angle*180/PI,1,1,WHITE);
	Ammo::draw();
}

}
