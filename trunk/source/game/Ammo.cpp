#include "../ShootMii.h"

namespace shootmii {

Ammo::Ammo(
	const float _angle,
	GRRLIB_texImg* _image,
	Function* _calcX,
	Function* _calcY,
	Player* _owner,
	Terrain* _terrain):
		Polygon(TANK_HEIGHT/4, 0, AMMO_OVERTAKE, _angle, 0, 1, _owner, Coordinates(-AMMO_WIDTH/2,-AMMO_HEIGHT/2), _image),
		calcX(_calcX),
		calcY(_calcY),
		t(0),
		destroyed(false),
		outOfCannon(false),
		fired(false),
		explosionFinished(false),
		terrain(_terrain)
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
	}
	// TODO Mise à jour
	//if (!isOutOfCannon())if (!cellIntersect(owner)) out();
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
	//TODO Mise à jour
	/*
	if (cellIntersect(player1)) return player1;
	if (cellIntersect(player2)) return player2;
	*/
	return NULL;
}

void Ammo::fire(){
	fired = true;
}

bool Ammo::ammoIntersect(const TerrainCell& c) const{
	/*
	int xGauche = c.getScreenX();
	int xDroite = xGauche + c.getWidth();
	int yBas = c.getScreenY() +  c.getHeight();
	int yHaut;
	int x,y;
	//Pour chaque point on vérifie qu'il n'est pas dans le quadrilatère.
	for (unsigned int i=0;i<vertices.size();i++){
		x = vertices[i].getX();
		y = vertices[i].getY();
		yHaut = yBas - c.getRelativeHeight(x-xGauche);
		if (x >= xGauche && // On est à droite de la bordure gauche
			x < xDroite && // On est à gauche de la bordure droite
			y >= yHaut && // On est au dessus de la bordure inférieure
			y < yBas) return true; // On est en dessous de la bordure supérieure
	}
	*/
	return false;
}

}


