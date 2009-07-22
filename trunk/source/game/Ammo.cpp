#include "../ShootMii.h"

namespace shootmii {

Ammo::Ammo(
	const float _angle,
	GRRLIB_texImg* _image,
	Function* _calcX,
	Function* _calcY,
	Player* _owner,
	Terrain* _terrain,
	Manager* _manager):
		Polygon(TANK_HEIGHT/4, 0, AMMO_OVERTAKE, _angle, 0, 1, _owner, Coordinates(-AMMO_WIDTH/2,-AMMO_HEIGHT/2), _image),
		calcX(_calcX),
		calcY(_calcY),
		t(0),
		destroyed(false),
		outOfCannon(false),
		fired(false),
		explosionFinished(false),
		terrain(_terrain),
		owner(_owner),
		manager(_manager)
{
	// NOTHING TO DO
}

Ammo::~Ammo() {
	vertices.clear();
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
	return originX/terrain->getCellWidth();
}

int Ammo::getRow() const{
	return originY/terrain->getCellHeight();
}

void Ammo::compute() {
	if (fired) {
		incT();
		originX = (*calcX)(t);
		originY = (*calcY)(t);
		angle = atan2((*calcY)[t],(*calcX)[t]);
		if (!(static_cast<int>(t/TIME_STEP)%TIME_BETWEEN_TWO_SMOKLET)){
			manager->addAnimationsToDraw(
				new Animation(
					App::imageBank->get(TXT_SMOKE),
					originX,
					originY,
					SMOKE_WIDTH,
					SMOKE_HEIGHT,
					SMOKE_DURATION));
		}
	}
	if (!isOutOfCannon()) if (!intersect(owner)) out();

}

void Ammo::setAngle(const float _angle){
	angle = _angle;
}

void Ammo::destroy() {
	destroyed = true;
}

void Ammo::out(){
	outOfCannon = true;
}

bool Ammo::isOutOfCannon() const{
	return outOfCannon;
}

bool Ammo::isOffScreen() const{
	for (unsigned int i=0,size=vertices.size();i<size;i++){
		if (vertices[i].getX() >= 0 && vertices[i].getX() < terrain->getCols()*terrain->getCellWidth()) return false;
	}
	return true;
}

bool Ammo::isTooLow() const{
	return (originY > SCREEN_HEIGHT);
}

bool Ammo::isDestroyed() const{
  return destroyed;
}

bool Ammo::hitTheGround(Terrain* terrain) const{
	if (isOffScreen()) return false;
	for (int i=0,size=vertices.size();i<size;i++){
		if (vertices[i].getY()+getAbsoluteY() >= terrain->getHeight(vertices[i].getX()+getAbsoluteX())) return true;
	}
	return false;
}

Ammo* Ammo::hitAnotherAmmo(list<Ammo*>* ammoList) const{
	list<Ammo*>::iterator it;
	for (it = ammoList->begin();it!=ammoList->end();it++)
		if (this != *it && intersect(*it)) return *it;
	return NULL;
}

Player* Ammo::hitAPlayer(Player* player1, Player* player2) const{
	if (!isOutOfCannon()) return NULL;
	if (intersect(player1)) return player1;
	if (intersect(player2)) return player2;
	return NULL;
}

void Ammo::fire(){
	fired = true;
}

}


