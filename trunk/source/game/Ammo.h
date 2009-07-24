#ifndef AMMO_H_
#define AMMO_H_

#include "../ShootMii.h"

namespace shootmii {

const float RECOIL_COEF(.25);

const int TIME_BETWEEN_TWO_SMOKLET(5);
const int SMOKE_SLOW(2);
const float SMOKE_WEIGHT(1);
const float WIND_INFLUENCE_ON_SMOKE(.5);
const float SMOKE_AIR_RESISTANCE(.3);

const int MINIMUM_LENGTH_FOR_DAMAGE(TERRAIN_CELL_WIDTH*3);
const float DAMAGE_COEF(.5);
const int HIT_DAMAGE_BONUS(20);

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
	Manager* manager;
public:
	Ammo(
		const float angle,
		GRRLIB_texImg* image,
		Function* calcX,
		Function* calcY,
		Player* owner,
		Terrain* terrain,
		Manager* manager);
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
