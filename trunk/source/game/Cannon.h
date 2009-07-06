#ifndef CANNON_H_
#define CANNON_H_

#include "../ShootMii.h"

namespace shootmii {

const float PI(3.14159265);

const int CANNON_WIDTH(16);
const int CANNON_HEIGHT(16);

const float DEFAULT_POWER(75);
const float CANNON_LENGTH(20.);
const float INIT_ANGLE(45.);
const float ROTATION_STEP(1.);
const float ROTATION_RANGE(90.);
const float ANGLE_OFFSET(90.);

const int HEAT_STEP(25);
const u8 HEAT_COOL_FAST(4);
const u8 HEAT_COOL_SLOW(10);
const u32 CLOCK_RANGE(5000);
const u32 BLOCKING_TIME(2000);
const u32 FLICKERING_TIME(500);
const u8 RELOAD_TIME(60);

class Cannon {
private:
	float angleOffSet;
	float angleRange;
	float angle;
	float rotationStep;
	Wind* wind;
	int strength; // 0 -> 100
	int heat; // 0 -> 100
	u32 blockedTime;
	u8 heatCool;
	u8 reloadTime;
	GRRLIB_texImg ammoLook;
	GRRLIB_texImg cannonLook;
	Ammo* loadedAmmo;
	Player* owner;
	bool stillHeld;
public:
	Cannon(const float _angleOffSet, const float _angleRange, const float _angle, const float _rotationStep, Wind* _wind, Player* _owner);
	~Cannon();
	void init();
	int getStrength() const;
	int getHeat() const;
	int getBlockedTime() const;
	void up();
	void decHeat();
	void draw(const int screenX, const int screenY) const;
	void rotateLeft();
	void rotateRight();
	void incStrength(Manager*);
	void shoot(Manager*);
	void reload();
	bool isLoaded() const;
};

}

#endif /*CANNON_H_*/
