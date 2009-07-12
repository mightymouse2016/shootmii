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
	fired(false),
	ammoLook(_ammoLook),
	owner(_owner)
{
	skeleton.reserve(5);
	skeleton.push_back(Coordinates(8,0));
	skeleton.push_back(Coordinates(2,-7));
	skeleton.push_back(Coordinates(-8,-7));
	skeleton.push_back(Coordinates(-8,7));
	skeleton.push_back(Coordinates(2,7));


	rayons.reserve(skeleton.size());
	alphas.reserve(skeleton.size());
	// pr�calculs, passage en coordonn�es polaires
	for(int i=0,x,y;i<5;i++){
		x = skeleton[i].getX();
		y = skeleton[i].getY();
		rayons.push_back(sqrt(x*x+y*y)); // Module
		alphas.push_back(atan2(y,x)); // Angle initial
	}
}

Ammo::~Ammo() {
	skeleton.clear();
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
	if (fired) {
		incT();
		screenX = (*calcX)(t);
		screenY = (*calcY)(t);
		angle = atan2((*calcY)[t],(*calcX)[t]);
	}

	int centerX = screenX+width/2;
	int centerY = screenY+height/2;
	for (unsigned int i=0;i<skeleton.size();i++){
		skeleton[i].setX(centerX+rayons[i]*cos(alphas[i]+angle));
		skeleton[i].setY(centerY+rayons[i]*sin(alphas[i]+angle));
	}

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
	/*
	if (ammoIntersect(terrain->getGrille()[getRow()][getCol()])) return true;
	if (ammoIntersect(terrain->getGrille()[getRow()+1][getCol()])) return true;
	if (ammoIntersect(terrain->getGrille()[getRow()][getCol()+1])) return true;
	if (ammoIntersect(terrain->getGrille()[getRow()-1][getCol()])) return true;
	if (ammoIntersect(terrain->getGrille()[getRow()][getCol()-1])) return true;
	*/
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
	if (cellIntersect(player1)) return player1;
	if (cellIntersect(player2)) return player2;
	return NULL;
}

void Ammo::drawSkeleton() const{
	int s = skeleton.size();
	for(int i=0,j;i<s;i++){
		if (i+1 == s) j = 0;
		else j = i+1;
		GRRLIB_Line(skeleton[i].getX(),skeleton[i].getY(),skeleton[j].getX(),skeleton[j].getY(),WHITE);
	}
}

void Ammo::fire(){
	fired = true;
}

bool Ammo::ammoIntersect(const TerrainCell& c) const{
	int screenX = c.getScreenX();
	int screenY = c.getScreenY();
	int x,y;
	//Pour chaque point on v�rifie qu'il n'est pas dans le quadrilat�re.
	for (unsigned int i=0;i<skeleton.size();i++){
		x = skeleton[i].getX();
		y = skeleton[i].getY();
		if (x >= screenX &&
			x <= screenX + c.getWidth() &&
			y <= screenY + c.getHeight() &&
			y >= c.getAbsoluteHeight(x)) return true;
	}
	return false;
}

}

