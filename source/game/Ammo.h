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

class Ammo: public Polygon {
protected:
	Function* calcX;
	Function* calcY;
	float t;
	bool destroyed;
	bool outOfCannon; // pour que le gestionnaire de collisions ignore l'auto-contact
	bool fired; // pour savoir si on incrémente le compteur de temps ou non
	bool explosionFinished;
	Terrain* terrain;
	Player* owner;
public:
	Ammo(
		const float angle,
		GRRLIB_texImg* image,
		Function* calcX,
		Function* calcY,
		Player* owner,
		Terrain* terrain);
	virtual ~Ammo();
	void incT();
	void decT();
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
};

}

#endif /*AMMO_H_*/
