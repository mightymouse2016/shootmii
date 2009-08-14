#ifndef PLAYER_H_
#define PLAYER_H_

#include "../ShootMii.h"

namespace shootmii {

const int SHOT_RECOIL(5);

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
const float SPEED_SLOW(0.5);
const float SPEED_VERY_SLOW(0.25);

const float FURY_DEC_STEP(.15);

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
	int playerNumber;
	int recoil; // Le recul : >0 recul vers la gauche <0 recul vers la gauche
	int score;
	float life;	// 0->100
	float fury;	// 0->100
	int nbGamesWon;
	bool furyMode;
	Terrain* terrain;
public:
	Player(
		Terrain* terrain,
		Wind* wind,
		int playerNumber,
		const float angleMin,
		const float angleMax,
		const float angle,
		const float rotationStep = ROTATION_STEP,
		const float life = 100,
		const float fury = 0,
		Manager* manager = NULL);

	int getPlayerNumber() const;
	int getCol() const;
	int getRow() const;
	int getScore() const;
	float getLife() const;
	float getFury() const;
	float* getPLife();
	float* getPFury();
	int getNbGamesWon() const;
	Terrain* getTerrain();
	Terrain* getTerrain() const;
	Cannon* getCannon();
	Cannon* getCannon() const;
	Player* getOpponent();
	Player* getOpponent() const;
	float getSpeed(const CellType type, const Direction dir) const;
	bool isInFuryMode() const;

	void setOpponent(Player* _opponent);
	void setScore(const int score);
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

	void addRecoil(int intensity);

	void init();
	void initGame();
	void initPosition(float screenX);

	void computeFuryMode();
	void computeDamage(Ammo* ammo);
	void computeRecoil();
	void compute();
};

}

#endif /*PLAYER_H_*/
