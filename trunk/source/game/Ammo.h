#ifndef AMMO_H_
#define AMMO_H_

#include "../ShootMii.h"

namespace shootmii {

const float G(-9.81);
const float TIME_STEP(.1);
const int AMMO_WEIGHT(1);
const int AMMO_WIDTH(16);
const int AMMO_HEIGHT(16);
const int AMMO_OVERTAKE(5); // dépassement de la munition du canon

enum explosionType {
  HIT_THE_GROUND,
  HIT_ANOTHER_AMMO,
  HIT_A_PLAYER
};

class Ammo: public Cell {
protected:
	Function* calcX;
	Function* calcY;
	float t;
	float angle;
	vector<Coordinates> vertices;
	vector<float> radials;
	vector<float> thetas;
	bool destroyed;
	bool outOfCannon; // pour que le gestionnaire de collision ignore le contact
	bool fired; // pour savoir si on incrémente le compteur de temps ou non
	bool explosionFinished;
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
	void destroy();
	virtual Explosion* destruction(explosionType _type)=0;
	void out();
	bool isOutOfCannon() const;
	bool isOffScreen() const;
	bool isTooLow() const;
	bool isDestroyed() const;
	bool hitTheGround(Terrain* terrain) const;
	Ammo* hitAnotherAmmo(list<Ammo*>* ammoList) const;
	Player* hitAPlayer(Player* player1, Player* player2) const;
	void fire();
	bool ammoIntersect(const TerrainCell&) const;
	void initRadials();
	void initThetas();
};

}

#endif /*AMMO_H_*/
