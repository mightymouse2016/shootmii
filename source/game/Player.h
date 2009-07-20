#ifndef PLAYER_H_
#define PLAYER_H_

#include "../ShootMii.h"

namespace shootmii {

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
	int score;
	int life;	// 0->100
	bool fury;	// 0->100
	int nbGamesWon;
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
		const int life = 100,
		const bool fury = false);
	int getCol() const;
	int getRow() const;
	int getScore() const;
	int getLife() const;
	int getFury() const;
	int getNbGamesWon() const;
	Terrain* getTerrain();
	Terrain* getTerrain() const;
	Cannon* getCannon();
	Cannon* getCannon() const;
	Player* getOpponent();
	Player* getOpponent() const;
	float getSpeed(const CellType type, const Direction dir) const;
	void setOpponent(Player* _opponent);
	void moveLeft(Terrain* terrain);
	void moveRight(Terrain* terrain);
	void looseLife(u8 lifeAmount);
	void setScore(const int score);
	void incScore();
	void init();
	void initPosition(Terrain* terrain, float screenX);
	void initGame();

};

}

#endif /*PLAYER_H_*/
