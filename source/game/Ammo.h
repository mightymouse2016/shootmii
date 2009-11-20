#ifndef AMMO_H_
#define AMMO_H_

#include "../ShootMii.h"

namespace shootmii {

const float RECOIL_COEF(.25);

const float SMOKE_WEIGHT(1);
const float WIND_INFLUENCE_ON_SMOKE(.5);
const float SMOKE_AIR_RESISTANCE(.3);

const int MINIMUM_LENGTH_FOR_DAMAGE(TERRAIN_CELL_WIDTH*3);
const float DAMAGE_COEF(.5);
const int HIT_DAMAGE_BONUS(20);

const float GRAVITY(-9.81);
const float TIME_STEP(.1);
const int AMMO_WEIGHT(1);
const int AMMO_WIDTH(16);
const int AMMO_HEIGHT(16);
const int AMMO_OVERTAKE(5); // dépassement de la munition du canon

const int GHOST_WIDTH(60);
const int GHOST_HEIGHT(52);
const int GHOST_OFFSET_X(5);
const int GHOST_MARGIN(GHOST_WIDTH-GHOST_HEIGHT/2);
const int GHOST_DISTANCE(100);	// Distance sur laquelle le fondu en transparence s'opère

enum explosionType {
  HIT_THE_GROUND,
  HIT_ANOTHER_AMMO,
  HIT_A_PLAYER,
  HIT_A_SHIELD
};

enum AmmoChild{
	CHILD_GHOST_BUBBLE
};

class Ammo: public Polygon, public Timer {
protected:
	Function* calcX;
	Function* calcY;
	bool destroyed;
	bool outOfCannon; 		//< pour que le gestionnaire de collisions ignore l'auto-contact
	bool outOfShield; 		//< pour que le gestionnaire de collisions ignore l'auto-contact
	bool fired; 			//< pour savoir si on incrémente le compteur de temps ou non
	bool explosionFinished;
	Terrain* terrain;
	Player* owner;
	Manager* manager;
	bool toDelete;
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
	Function* getCalcX();
	Function* getCalcY();
	int getCol() const;
	int getRow() const;
	Rectangle* getGhostAmmo();
	Rectangle* getGhostAmmo() const;
	Rectangle* getGhostBubble();
	Rectangle* getGhostBubble() const;
	Player* getOwner();
	Player* getOwner() const;
	void computeOut();
	void computeGhost();
	virtual void computeSmoklets();
	virtual void computePosition();
	void compute();
	void setAngle(const float _angle);
	void destroy();
	virtual Animation* destruction(explosionType _type, Player* _playerHit = NULL)=0;
	void outCannon();
	void outShield();
	/*
	 * Cette méthode set toDelete à true pour que le gestionnaire de collision la supprime
	 * après seulement avoir geré toutes les collisions entre ammos, sinon crash !
	 */
	virtual void deleteMe();
	bool isToDelete();
	bool isOutOfCannon() const;
	bool isOutOfShield() const;
	bool isOffScreen() const;
	bool isTooLow() const;
	bool isDestroyed() const;
	bool hitTheGround(Terrain* terrain) const;
	bool hitABonus(list<Bonus*>* bonusList) const;
	Ammo* hitAnotherAmmo(list<Ammo*>* ammoList) const;
	Player* hitAPlayer(Player* player1, Player* player2) const;
	bool hitAShield(Player* player);
	void addShieldEffect(Player* player,float angle) const;

	void init(float strength);

	void fire();

	void draw();
};

}

#endif /*AMMO_H_*/
