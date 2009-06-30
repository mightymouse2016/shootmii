#ifndef PLAYER_H_
#define PLAYER_H_

#include "../ShootMii.h"

namespace shootmii {

const int TANK_WIDTH(16);
const int TANK_HEIGHT(32);
const int TANK_ROTATION_AXIS_X(8);
const int TANK_ROTATION_AXIS_Y(8);

enum Bonus {
	NORMAL, FIRE, FREEZE,
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
	GRRLIB_texImg tankLook;
public:
	Player(const string & _nickName, const u32 _color, Wind* _wind,
			const float _angleOffSet = ANGLE_OFFSET, const float _angleRange =
					ROTATION_RANGE, const float _angle = INIT_ANGLE,
			const float _rotationStep = ROTATION_STEP, const u8 _life = 100,
			const bool _fury = false, Bonus _bonus = NORMAL);
	// Accesseurs
	Cannon* getCannon();
	Cannon* getCannon() const;
	void init();
	void initGame();
	void draw() const;
	u8 getLife() const;
	int getScore() const;
	void setScore(const int _score);
	void incScore();
	void looseLife(u8 lifeAmount);
};

}
#endif /*PLAYER_H_*/
