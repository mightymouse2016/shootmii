#ifndef PLAYER_H_
#define PLAYER_H_

#include "../ShootMii.h"

namespace shootmii {

const int TANK_WIDTH(16);
const int TANK_HEIGHT(32);
const int TANK_ROTATION_AXIS_X(8);
const int TANK_ROTATION_AXIS_Y(8);
const float SPEED_VERY_FAST(1.5);
const float SPEED_FAST(1.25);
const float SPEED_NORMAL(1);
const float SPEED_SLOW(0.5);
const float SPEED_VERY_SLOW(0.25);

enum Bonus {
	NORMAL, FIRE, FREEZE
};

enum Direction {
  LEFT, RIGHT
};

class Player: public Cell {
private:
	std::string nickName;
	int score;
	u8 life; // 0 -> 100
	bool fury;
	Bonus bonus;
	Cannon* cannon;
	u8 nbGamesWon;
	u32 color;
	GRRLIB_texImg* tankLook;
	Player* opponent;
	Terrain* terrain;
public:
	Player(
		const string & _nickName,
		const u32 _color,
		Terrain* _terrain,
		Wind* _wind,
		Player* _opponent,
		bool _player,
		const float _angleMin,
		const float _angleMax,
		const float _angle,
		const float _rotationStep = ROTATION_STEP,
		const u8 _life = 100,
		const bool _fury = false,
		Bonus _bonus = NORMAL);
	~Player();
	int getCol() const;
	int getRow() const;
	u8 getLife() const;
	int getScore() const;
	Cannon* getCannon();
	Cannon* getCannon() const;
	void setIndexCoords(const int _colIndex, const int _rowIndex);
	void setOpponent(Player* _opponent);
	void moveLeft(Terrain* terrain);
	void moveRight(Terrain* terrain);
	void looseLife(u8 lifeAmount);
	void setScore(const int _score);
	void incScore();
	void init();
	void initPosition(Terrain* terrain, float _screenX);
	void initGame();
	void draw() const;
	float getSpeed(const CellType type, const Direction dir) const;
};

}

#endif /*PLAYER_H_*/