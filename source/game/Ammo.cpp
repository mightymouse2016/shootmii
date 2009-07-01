#include "../ShootMii.h"

namespace shootmii {

Ammo::Ammo(
		const float _angle,
		GRRLIB_texImg* _ammoLook,
		Function* _calcX,
		Function* _calcY,
		Player* _owner) :
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

void Ammo::destruction() {
	destroyed = true;
}

void Ammo::out(){
	outOfCannon = true;
}

bool Ammo::isBeingDestroyed() const {
	return destroyed;
}

bool Ammo::isOutOfCannon() const{
	return outOfCannon;
}

bool Ammo::isOffScreen() const{
	return (screenX > SCREEN_WIDTH || screenX < -TERRAIN_CELL_WIDTH);
}

bool Ammo::isTooLow() const{
	return (screenY > SCREEN_HEIGHT);
}

bool Ammo::hitTheGround(Terrain* terrain) const{
	if (terrain->getType(getCol(), getRow()) == SKY) return false;
		return true;
}

Ammo* Ammo::hitAnotherAmmo(list<Ammo*>* ammoList) const{
	list<Ammo*>::iterator it;
	for (it = ammoList->begin();it!=ammoList->end();it++)
		if (this != *it && cellIntersect(*it)) return *it;
	return NULL;
}

Player* Ammo::hitAPlayer(Player* player1, Player* player2) const{
	if (!isOutOfCannon()) return NULL;
	if (cellIntersect(player1)) return player1;
	if (cellIntersect(player2)) return player2;
	return NULL;
}

}
