#ifndef CANNON_H_
#define CANNON_H_

#include "../ShootMii.h"

namespace shootmii {

const float PI(3.14159265);

const int CANNON_WIDTH(16);
const int CANNON_HEIGHT(16);

const int CROSSHAIR_WIDTH(24);
const int CROSSHAIR_HEIGHT(24);
const int CROSSHAIR_OVERTAKE(100);

const int STRENGHT_JAUGE_STATES(12);
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
	CHILD_AMMO
};

class Cannon : public Rectangle{
private:
	float angleMin;
	float angleMax;
	float rotationStep;
	Wind* wind;
	float strength; // 0 -> 100
	int heat; // 0 -> 100
	u32 blockedTime;
	u8 heatCool;
	u8 reloadTime;
	GRRLIB_texImg* ammoLook;
	Ammo* loadedAmmo;
	bool stillHeld;
public:
	Cannon(
		const float angleMin,
		const float angleMax,
		const float angle,
		const float rotationStep,
		Wind* wind,
		Player* owner,
		int playerNumber);
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
