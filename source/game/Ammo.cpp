#include "../ShootMii.h"

namespace shootmii {

Ammo::Ammo(const float _angle,GRRLIB_texImg* _ammoLook, Function* _calcX, Function* _calcY) :
	calcX(_calcX), calcY(_calcY), t(0), angle(_angle), destroyed(false), ammoLook(_ammoLook) {
}

Ammo::~Ammo() {
}

void Ammo::incT() {
	t += TIME_STEP;
}

void Ammo::decT() {
	t -= TIME_STEP;
}

CannonBall::CannonBall(const float _angle, Wind* wind, GRRLIB_texImg* _ammoLook, const float _vInitX, const float _vInitY,
		const float _xInit, const float _yInit) :
	Ammo(_angle,_ammoLook,
		new PolyDeg2(float(wind->getWindSpeed())*(wind->getWindDirection()*2-1)*WIND_INFLUENCE_ON_AMMO/(2*100*AMMO_WEIGHT),_vInitX,_xInit),
		new PolyDeg2(-G/(2*AMMO_WEIGHT),-_vInitY,_yInit)){
	}

	void CannonBall::draw() const {
		//GRRLIB_Rectangle(screenX, screenY, CELL_SIZE, CELL_SIZE, BLACK, true);
		// 4eme arg : degrees
		GRRLIB_DrawImg(screenX, screenY, *ammoLook, angle*180/PI+90, 1, 1, WHITE);
		/* GRRLIB_Line(screenX+CELL_SIZE/2,
				screenY+CELL_SIZE/2,
				screenX+CELL_SIZE/2+16*cos(angle),
				screenY+CELL_SIZE/2+16*sin(angle),
				WHITE); */
	}

	Function* Ammo::getCalcX() {
		return calcX;
	}

	Function* Ammo::getCalcY() {
		return calcY;
	}

	void Ammo::updateXYTAngle() {
		incT();
		screenX = (*calcX)(t);
		screenY = (*calcY)(t);
		angle = atan2((*calcY)[t],(*calcX)[t]);
	}

	void Ammo::setAngle(const float _angle){
		angle = _angle;
	}

	bool Ammo::isBeingDestroyed() const {
		return destroyed;
	}

	void Ammo::destruction() {
		destroyed = true;
	}
}
