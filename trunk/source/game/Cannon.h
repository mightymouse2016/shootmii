#ifndef CANNON_H_
#define CANNON_H_

#include "../ShootMii.h"

namespace shootmii {

const int CANNON_WIDTH(16);
const int CANNON_HEIGHT(16);

const int SMOKE_SLOW(2);
const int SMOKE_WIDTH(16);
const int SMOKE_HEIGHT(16);
const int SMOKE_DURATION(28);
const int TIME_BETWEEN_TWO_SMOKLET(5);

const int HOMING_SMOKE_SLOW(20);
const int HOMING_SMOKE_WIDTH(12);
const int HOMING_SMOKE_HEIGHT(12);
const int HOMING_SMOKE_DURATION(6);
const int HOMING_SMOKE_OVERTAKE(-15);

const int CROSSHAIR_WIDTH(24);
const int CROSSHAIR_HEIGHT(24);
const int CROSSHAIR_OVERTAKE(100);

const int STRENGTH_JAUGE_STATES(12);
const int STRENGHT_JAUGE_SPRITE_WIDTH(24);
const int STRENGHT_JAUGE_SPRITE_HEIGHT(24);

const float DEFAULT_POWER(75);
const float CANNON_LENGTH(20.);
const float INIT_ANGLE(0);
const float ROTATION_STEP(.01);

const float STRENGTHEN_STEP(1.5);

const float HEAT_INC_STEP(25);
const float HEAT_COOL_FAST_STEP(.2);
const float HEAT_COOL_SLOW_STEP(.1);
const int CLOCK_RANGE(5000);
const int FLICKERING_TIME(500);

const int BLOCKING_TIME(3*60); // 3 secondes
const int RELOAD_TIME(60);
const int FURY_RELOAD_TIME(20);
const int FURY_HOMING_PROBABILITY(10);

const int SHOT_MINIMUM_SOUND(20);
const int SHOT_MINIMUM_STRENGTH(20);

const float LASER_STEP(.1);
const float LASER_MOVE_STEP(.002);

enum CannonChild{
	CHILD_CROSSHAIR,
	CHILD_AMMO,
	CHILDREN_STRENGTH
};

class Cannon : public Rectangle{
private:
	Wind* wind;
	float heat; 		//< 0 -> 100
	float strength; 	//< 0 -> 100
	float angleMin;
	float angleMax;
	float rotationStep;
	bool stillHeld;
	Timer reloadTime;
	Timer blockedCannon;
	Timer furyReloadTime;
	Manager* manager;
	Function* laserXMax;
	Function* laserYMax;
	Function* laserX;
	Function* laserY;
	int t_laser;
	GuidedMissile* guidedMissile; // Si le joueur possède un missile auto-guidé, c'est le lien qui permet de le contrôler
public:
	Cannon(
		const float angleMin,
		const float angleMax,
		const float angle,
		const float rotationStep,
		Wind* wind,
		Player* owner,
		int playerNumber,
		Manager* manager);
	~Cannon();
	void destroyGuidedMissile();
	void loseInfluenceOnMissile();
	void init();
	float getStrength() const;
	float getHeat() const;
	float* getPStrength();
	float* getPHeat();
	int getBlockedTime() const;
	Ammo* getAmmo();
	Ammo* getAmmo() const;
	GuidedMissile* getGuidedMissile();
	GuidedMissile* getGuidedMissile() const;
	Player* getOwner();
	Player* getOwner() const;
	void setAmmo(Ammo* ammo);
	void up();
	void decHeat();
	void draw(const int screenX, const int screenY);
	void rotateLeft();
	void rotateRight();
	void incStrength();
	void incHeat();
	void compute();
	void computeHeat();
	void computeStrengthJauge();
	void computeLaserMode();
	void shoot();
	void computeReload();
	void loadCannon();
	void loadHoming();
	void loadGuided();
	bool isLoaded() const;
	bool isGuidingMissile() const;
	void draw();
};

}

#endif /*CANNON_H_*/
