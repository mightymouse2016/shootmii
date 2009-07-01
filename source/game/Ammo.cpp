#include "../ShootMii.h"

namespace shootmii {

Ammo::Ammo(const float _angle, GRRLIB_texImg* _ammoLook, Function* _calcX,
		Function* _calcY, Player* _owner) :
	Cell(AMMO_WIDTH, AMMO_HEIGHT), calcX(_calcX), calcY(_calcY), t(0), angle(
			_angle), destroyed(false), outOfCannon(false), ammoLook(_ammoLook), owner(_owner) {
}

Ammo::~Ammo() {
}

void Ammo::incT() {
	t += TIME_STEP;
}

void Ammo::decT() {
	t -= TIME_STEP;
}

CannonBall::CannonBall(const float _angle, Wind* wind,
		GRRLIB_texImg* _ammoLook, Player* _owner, const float _vInitX, const float _vInitY,
		const float _xInit, const float _yInit) :
	Ammo(_angle, _ammoLook, new PolyDeg2(float(wind->getWindSpeed())
			* (wind->getWindDirection() * 2 - 1) * WIND_INFLUENCE_ON_AMMO / (2*
			100* AMMO_WEIGHT ),_vInitX,_xInit) ,new PolyDeg2(-G/(2*AMMO_WEIGHT),-_vInitY,_yInit),_owner){
}

	void CannonBall::draw() const {
		GRRLIB_DrawImg(screenX+AMMO_OVERTAKE*cos(angle), screenY+AMMO_OVERTAKE*sin(angle), *ammoLook, angle*180/PI+90, 1, 1, WHITE);
}

	Function* Ammo::getCalcX() {
		return calcX;
	}

	Function* Ammo::getCalcY() {
		return calcY;
	}

	int Ammo::getCol() const{
		return (screenX+width/2-TERRAIN_CELL_WIDTH/2)/TERRAIN_CELL_WIDTH;
	}

	int Ammo::getRow() const{
		return (screenY+height)/TERRAIN_CELL_HEIGHT;
	}

	void Ammo::compute() {
		incT();
		screenX = (*calcX)(t);
		screenY = (*calcY)(t);
		angle = atan2((*calcY)[t],(*calcX)[t]);
		/// TODO
		if (!isOutOfCannon()){
			if (!cellIntersect(owner)) out();
		}
	}

	void Ammo::setAngle(const float _angle){
		angle = _angle;
	}

	bool Ammo::isBeingDestroyed() const {
		return destroyed;
	}

	bool Ammo::isOutOfCannon() const{
		return outOfCannon;
	}

	void Ammo::destruction() {
		destroyed = true;
	}

	void Ammo::out(){
		outOfCannon = true;
	}
}
