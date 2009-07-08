#ifndef AMMO_H_
#define AMMO_H_

#include "../ShootMii.h"

namespace shootmii {

const float G(-9.81);
const float TIME_STEP(.1);
const int AMMO_WEIGHT(1);
const int AMMO_WIDTH(16);
const int AMMO_HEIGHT(16);
const int AMMO_OVERTAKE(50); // dépassement de la munition du canon

class Ammo: public Cell {
protected:
	Function* calcX;
	Function* calcY;
	float t;
	float angle;
	vector<Coordinates> skeleton;
	vector<float> rayons;
	vector<float> alphas;
	bool destroyed;
	bool outOfCannon; // pour que le gestionnaire de collision ignore le contact
	bool fired; // pour savoir si on incrémente le compteur de temps ou non
	GRRLIB_texImg* ammoLook;
	Player* owner;
	Terrain* terrain;
public:
	Ammo(
		const float _angle,
		GRRLIB_texImg* _ammoLook,
		Function* _calcX,
		Function* _calcY,
		Player* _owner);
	virtual ~Ammo();
	void incT();
	void decT();
	virtual void draw() const=0;
	Function* getCalcX();
	Function* getCalcY();
	int getCol() const;
	int getRow() const;
	void compute();
	void setAngle(const float _angle);
	void destruction();
	void out();
	bool isBeingDestroyed() const;
	bool isOutOfCannon() const;
	bool isOffScreen() const;
	bool isTooLow() const;
	bool hitTheGround(Terrain* terrain) const;
	Ammo* hitAnotherAmmo(list<Ammo*>* ammoList) const;
	Player* hitAPlayer(Player* player1, Player* player2) const;
	void drawSkeleton() const;
	void fire();
	bool ammoIntersect(const TerrainCell&) const;
};

}

#endif /*AMMO_H_*/
