#include "../ShootMii.h"

namespace shootmii {

Player::Player(const string & _nickName, const u32 _color, Wind* _wind,
		const float _angleOffSet, const float _angleRange, const float _angle,
		const float _rotationStep, const u8 _life, const bool _fury,
		Bonus _bonus) :
	Cell(TANK_WIDTH,TANK_HEIGHT),
	nickName(_nickName),
	score(0),
	life(_life),
	fury(_fury),
	bonus(_bonus),
	cannon(new Cannon(_angleOffSet, _angleRange, _angle, _rotationStep,_wind, this)),
	nbGamesWon(0),
	color(_color),
	tankLook(GRRLIB_LoadTexture(tank))
{

}

int Player::getCol() const{
	return (screenX+width/2-TERRAIN_CELL_WIDTH/2)/TERRAIN_CELL_WIDTH;
}

int Player::getRow() const{
	return (screenY+height)/TERRAIN_CELL_HEIGHT;
}

void Player::setIndexCoords(const int _colIndex, const int _rowIndex){
	screenX = _colIndex*TERRAIN_CELL_WIDTH+TERRAIN_CELL_WIDTH/2-width/2;
	screenY = _rowIndex*TERRAIN_CELL_HEIGHT-height;
}

Cannon* Player::getCannon() {
	return cannon;
}

Cannon* Player::getCannon() const {
	return cannon;
}

void Player::init() {
	nbGamesWon = 0;
	initGame();
}

void Player::initGame() {
	life = 100;
	fury = false;
	bonus = NORMAL;
	cannon->init();
}

void Player::draw() const {
	cannon->draw(screenX, screenY);
	GRRLIB_DrawImg(screenX,screenY,tankLook, 0, 1, 1, WHITE);
}

u8 Player::getLife() const {
	return life;
}

int Player::getScore() const {
	return score;
}

void Player::setScore(const int _score) {
	score = _score;
}

void Player::incScore() {
	score++;
}

void Player::looseLife(u8 lifeAmount) {
	// Il est deja mort
	if (life == 0) return;
	// Il meurt
	if (lifeAmount >= life) life = 0;
	// Il est toujours vivant
	else life -= lifeAmount;
}

}
