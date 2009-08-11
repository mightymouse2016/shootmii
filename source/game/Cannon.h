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

const int HEAT_STEP(25);
const u8 HEAT_COOL_FAST(4);
const u8 HEAT_COOL_SLOW(10);
const u32 CLOCK_RANGE(5000);
const u32 BLOCKING_TIME(2000);
const u32 FLICKERING_TIME(500);
const u8 RELOAD_TIME(60);

enum CannonChild{
	CHILD_CROSSHAIR,
	CHILD_AMMO,
	CHILDREN_STRENGTH
};

class Cannon : public Rectangle{
private:
	float angleMin;
	float angleMax;
	float rotationStep;
	Wind* wind;
	float strength; // 0 -> 100
	float heat; // 0 -> 100
	u32 blockedTime;
	u8 heatCool;
	u8 reloadTime;
	bool stillHeld;
	Manager* manager;
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
	void init();
	float getStrength() const;
	float getHeat() const;
	float* getPStrength();
	float* getPHeat();
	int getBlockedTime() const;
	Ammo* getAmmo();
	Ammo* getAmmo() const;
	void setAmmo(Ammo* ammo);
	void up();
	void decHeat();
	void draw(const int screenX, const int screenY) const;
	void rotateLeft();
	void rotateRight();
	void incStrength();
	void shoot();
	void reload();
	void loadHoming();
	bool isLoaded() const;
};

}

#endif /*CANNON_H_*/
