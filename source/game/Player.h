#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdlib>
#include <wiiuse/wpad.h>
#include "../tools/Tools.h"
#include "../math/Interval.h"
#include "../math/Rectangle.h"

namespace shootmii {

class Terrain;
class Cannon;
class Manager;
class Ammo;
class Timer;
class Pulse;
class Wind;
class Bonus;
class IA;

const int SHOT_RECOIL(5);

const float ROTATION_STEP(.01);
const int TANK_WIDTH(16);
const int TANK_HEIGHT(32);
const int TANK_ROTATION_AXIS_X(8);
const int TANK_ROTATION_AXIS_Y(8);
const int ANGLE_MIN = 0;
const int ANGLE_MAX = PI/2;
const int ANGLE_INIT = PI/4;
const float SPEED_VERY_FAST(1.5);
const float SPEED_FAST(1.25);
const float SPEED_NORMAL(1);
const float SPEED_SLOW(.75);
const float SPEED_VERY_SLOW(.5);

const float FURY_DEC_STEP(.4);
const float LASER_DEC_STEP(.1);
const float SHIELD_DEC_STEP(.1);
const float SHIELD_IMPACT_DEC_STEP(2);

const int DAMAGE_SMOKLET_STATES(5);
const int BACK_SMOKLETS_RATIO(4);
const float DAMAGE_SMOKLET_INITIAL_SPEED(5);
const float ARCHIMEDE(5);

const float DAMAGE_PULSE_R1(.25);
const float DAMAGE_PULSE_R2(.5);
const float DAMAGE_PULSE_PERIOD(10);

const float DAMAGE_SPEED_LIFE_LIMIT(50); // 20/100

enum Direction {
  LEFT,
  RIGHT
};

enum PlayerChild{
	CHILD_CANNON,
	CHILD_OPPONENT
};

class Player: public Rectangle {
private:
	unsigned int playerNumber;
	unsigned int score;
	int recoil; 		//< Le recul : >0 vers la droite <0 vers la gauche
	bool lifeModificationFlag;
	float life;			//<  0->100
	float fury;			//<  0->100
	float laserRemainingTime;
	float shieldRemainingTime;
	bool furyMode;
	bool iaMode;
	Terrain* terrain;
	Manager* manager;
	Bonus* bonus;
	Timer* damageSmokletTimer;
	Timer* damagePulseTimer;
	Pulse* damagePulse;
	IA* ia;
public:
	Player(
		Terrain* terrain,
		Wind* wind,
		const unsigned int playerNumber,
		const float angleMin,
		const float angleMax,
		const float angle,
		const float rotationStep = ROTATION_STEP,
		const float life = 100,
		const float fury = 0,
		Manager* manager = NULL);
	~Player();

	unsigned int getPlayerNumber() const;
	unsigned int getScore() const;
	int getCol() const;
	int getRow() const;
	float getLife() const;
	float getFury() const;
	float* getPLife();
	float* getPFury();
	bool* getPFuryMode();
	float* getPLaserRemainingTime();
	float* getPShieldRemainingTime();
	Terrain* getTerrain();
	Terrain* getTerrain() const;
	Cannon* getCannon();
	Cannon* getCannon() const;
	Player* getOpponent();
	Player* getOpponent() const;
	float getSpeed(const int cellYype, const Direction dir) const;
	Bonus* getBonus();
	Bonus** getPBonus();
	Interval getAngularInterval() const;
	bool isInFuryMode() const;
	bool isInIAMode() const;
	bool isInLaserMode() const;
	bool isInShieldMode() const;

	void setOpponent(Player* _opponent);
	void setScore(const unsigned int score);
	void incScore();
	void moveLeft(const float speed = 1);
	void moveRight(const float speed = 1);
	void setLife(const float lifeAmount);
	void winLife(const float lifeAmount);
	void loseLife(const float lifeAmount);
	void setFury(const float furyAmount);
	void winFury(const float furyAmount);
	void loseFury(const float furyAmount);
	void beginFuryMode();
	void stopFuryMode();
	void setIA(const bool ia);
	void beginLaserMode();
	void stopLaserMode();
	void beginShieldMode();
	void stopShieldMode();

	void addRecoil(int intensity);
	void addBonus(Bonus* bonus);

	void initGame();						//< Initialise une partie
	void initRound();					//< Initialise une manche
	void initPosition(float screenX);	//< Pose le player sur le terrain

	void useBonus(Bonus* bonus);	//< en pressant A
	void shieldImpact();

	void computeFuryMode();
	void computeLaserMode();
	void computeShieldMode();
	void computeDamage(Ammo* ammo);
	void computeDegradation();
	void computeRecoil();
	void computeIA();
	void compute();

	void draw();

	// Binds
	void dealEvent(const u32* playerEvents);

	void KeyUp(EventType type);
	void KeyDown(EventType type);
	void KeyLeft(EventType type);
	void KeyRight(EventType type);

	void KeyA(EventType type);
	void KeyB(EventType type);
	void KeyMinus(EventType type);
	void KeyPlus(EventType type);
};

}

#endif /*PLAYER_H_*/
