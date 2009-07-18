#include "../ShootMii.h"

namespace shootmii {

Ammo::Ammo(
		const float _angle,
		GRRLIB_texImg* _ammoLook,
		Function* _calcX,
		Function* _calcY,
		Player* _owner):
	Cell(AMMO_WIDTH, AMMO_HEIGHT),
	calcX(_calcX),
	calcY(_calcY),
	t(0),
	angle(_angle),
	destroyed(false),
	outOfCannon(false),
	fired(false),
	explosionFinished(false),
	ammoLook(_ammoLook),
	owner(_owner)
{

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
	return (screenX+width/2-terrain->getCellWidth()/2)/terrain->getCellWidth();
}

int Ammo::getRow() const{
	return (screenY+height)/terrain->getCellHeight();
}

void Ammo::compute() {
	if (fired) {
		incT();
		screenX = (*calcX)(t);
		screenY = (*calcY)(t);
		angle = atan2((*calcY)[t],(*calcX)[t]);
	}

	int centerX = screenX+width/2;
	int centerY = screenY+height/2;
	for (unsigned int i=0;i<vertices.size();i++){
		vertices[i].setX(centerX+radials[i]*cos(thetas[i]+angle));
		vertices[i].setY(centerY+radials[i]*sin(thetas[i]+angle));
	}

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
	return (screenX > SCREEN_WIDTH || screenX < - terrain->getCellWidth());
}

bool Ammo::isTooLow() const{
	return (screenY > SCREEN_HEIGHT);
}

bool Ammo::isDestroyed() const{
  return destroyed;
}

bool Ammo::hitTheGround(Terrain* terrain) const{
	int screenX, screenY;
	for (unsigned int i=0;i<vertices.size();i++){
		screenY = vertices[i].getY();
		screenX = vertices[i].getX();
		if (screenX >= 0 && screenX < terrain->getCols()*terrain->getCellWidth() && screenY >= terrain->getHeight(screenX)) return true;
	}
	return false;
}

Ammo* Ammo::hitAnotherAmmo(list<Ammo*>* ammoList) const{
	list<Ammo*>::iterator it;
	for (it = ammoList->begin();it!=ammoList->end();it++)
		if (this != *it && cellIntersect(*it)) return *it;
	return NULL;
}

Player* Ammo::hitAPlayer(Player* player1, Player* player2) const{
	if (!isOutOfCannon()) return NULL;
	/*
	if (cellIntersect(player1)) return player1;
	if (cellIntersect(player2)) return player2;
	*/
	return NULL;
}

void Ammo::draw() const{
	if (!App::console->isDebug()) return;
	int size = vertices.size();
	for(int i=0,j;i<size;i++){
		if (i+1 == size) j = 0;
		else j = i+1;
		GRRLIB_Line(vertices[i].getX(),vertices[i].getY(),vertices[j].getX(),vertices[j].getY(),RED);
	}
}

void Ammo::fire(){
	fired = true;
}

bool Ammo::ammoIntersect(const TerrainCell& c) const{
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
	return false;
}

void Ammo::initRadials(){
	int x,y,size = vertices.size();
	radials.reserve(size);
	for(int i=0;i<size;i++){
		x = vertices[i].getX();
		y = vertices[i].getY();
		radials.push_back(sqrt(x*x+y*y)); // Module
	}
}

void Ammo::initThetas(){
	int x,y,size = vertices.size();
	thetas.reserve(size);
	for(int i=0;i<size;i++){
		x = vertices[i].getX();
		y = vertices[i].getY();
		thetas.push_back(atan2(y,x)); // Angle initial
	}
}

}


