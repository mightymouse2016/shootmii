#include "../ShootMii.h"

namespace shootmii {

Ammo::Ammo(const float _angle, GRRLIB_texImg* _ammoLook, Function* _calcX, Function* _calcY, Player* _owner) :
	Cell(AMMO_WIDTH, AMMO_HEIGHT),
	calcX(_calcX),
	calcY(_calcY),
	t(0),
	angle(_angle),
	destroyed(false),
	outOfCannon(false),
	ammoLook(_ammoLook),
	owner(_owner)
{

}

Ammo::~Ammo() {
	// NOTHING TO DO
}

void Ammo::incT() {
	t += TIME_STEP;
}

void Ammo::decT() {
	t -= TIME_STEP;
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
	if (!isOutOfCannon())if (!cellIntersect(owner)) out();
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
