#include "../ShootMii.h"

namespace shootmii {

Player::Player(
		const string & _nickName,
		const u32 _color,
		Terrain* _terrain,
		Wind* _wind,
		Player* _opponent,
		bool _player,
		const float _angleMin,
		const float _angleMax,
		const float _angle,
		const float _rotationStep,
		const u8 _life,
		const bool _fury,
		Bonus _bonus) :
	Cell(TANK_WIDTH,TANK_HEIGHT),
	nickName(_nickName),
	score(0),
	life(_life),
	fury(_fury),
	bonus(_bonus),
	cannon(new Cannon(_angleMin, _angleMax, _angle, _rotationStep,_wind, this, _player)),
	nbGamesWon(0),
	color(_color),
	opponent(_opponent),
	terrain(_terrain)
{
		  tankLook = App::imageBank->get(TXT_TANK);
}

Player::~Player() {
  delete cannon;
}

int Player::getCol() const{
	return (screenX+width/2-terrain->getCellWidth()/2)/terrain->getCellWidth();
}

int Player::getRow() const{
	return (screenY+height)/terrain->getCellHeight();
}

void Player::setIndexCoords(const int _colIndex, const int _rowIndex){
	screenX = _colIndex*terrain->getCellWidth()+terrain->getCellWidth()/2-width/2;
	screenY = _rowIndex*terrain->getCellHeight()-height;
}

void Player::setOpponent(Player* _opponent){
	opponent = _opponent;
}

float Player::getSpeed(const CellType type, const Direction dir) const {
  switch(type) {
      case GRASS_LEFT:
      case GRASS_MID:
      case GRASS_RIGHT:
        return SPEED_NORMAL;
      case SLOPE_UP_05_1:
      case SLOPE_UP_05_2:
        if(dir == LEFT) return SPEED_FAST;
        return SPEED_SLOW;
      case SLOPE_DOWN_05_1:
      case SLOPE_DOWN_05_2:
        if(dir == LEFT) return SPEED_SLOW;
        return SPEED_FAST;
      case SLOPE_UP_1:
        if(dir == LEFT) return SPEED_VERY_FAST;
        return SPEED_VERY_SLOW;
      case SLOPE_DOWN_1:
        if(dir == LEFT) return SPEED_VERY_SLOW;
        return SPEED_VERY_FAST;
      default:
        return SPEED_VERY_SLOW;
    }
  return SPEED_VERY_SLOW;
}

void Player::moveLeft(Terrain* terrain){
  TerrainCell cell = terrain->getGround(((int)screenX+width/2)/width);
  float newScreenX = screenX - getSpeed(cell.getType(), LEFT);
	if (newScreenX <= 0) return;
	if (newScreenX >= opponent->getScreenX() && newScreenX <= opponent->getScreenX() + width) return;
	initPosition(terrain, newScreenX);
}

void Player::moveRight(Terrain* terrain){
  TerrainCell cell = terrain->getGround(((int)screenX+width/2)/width);
  float newScreenX = screenX + getSpeed(cell.getType(), RIGHT);
	if (newScreenX + width >= terrain->getCols()*terrain->getCellWidth()) return;
	if (newScreenX + width >= opponent->getScreenX() && newScreenX + width <= opponent->getScreenX() + width) return;
	initPosition(terrain, newScreenX);
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

void Player::initPosition(Terrain* terrain, float _screenX){
	screenX = _screenX;
	screenY = terrain->getHeight(screenX+width/2) - height;
}

void Player::initGame() {
	life = 100;
	fury = false;
	bonus = NORMAL;
	cannon->init();
}

void Player::draw() const {
	cannon->draw(screenX, screenY);
	GRRLIB_DrawImg(screenX,screenY,*tankLook, 0, 1, 1, WHITE);
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
	if (life == 0) return;
	if (lifeAmount >= life) life = 0;
	else life -= lifeAmount;
}

}
