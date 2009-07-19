#include "../ShootMii.h"

namespace shootmii {

Player::Player(
	Terrain* _terrain,
	Wind* _wind,
	int _playerNumber,
	const float _angleMin,
	const float _angleMax,
	const float _angle,
	const float _rotationStep,
	const int _life,
	const bool _fury) :
		Rectangle(TANK_HEIGHT,TANK_WIDTH,0,0,TANK_HEIGHT/2,-PI/2,0,1,App::imageBank->get(TXT_TANK)),
		score(0),
		life(_life),
		fury(_fury),
		nbGamesWon(0),
		terrain(_terrain)
{
	children.reserve(2);
	addChild(new Cannon(_angleMin, _angleMax, _angle, _rotationStep,_wind, this, _playerNumber));
}

int Player::getCol() const{
	return originX/terrain->getCellWidth();
}

int Player::getRow() const{
	return originY/terrain->getCellHeight();
}

int Player::getLife() const {
	return life;
}

int Player::getScore() const {
	return score;
}

int Player::getFury() const{
	return fury;
}

int Player::getNbGamesWon() const{
	return nbGamesWon;
}

Terrain* Player::getTerrain(){
	return terrain;
}

Terrain* Player::getTerrain() const{
	return terrain;
}

Cannon* Player::getCannon() {
	return static_cast<Cannon*>(children[CHILD_CANNON]);
}

Cannon* Player::getCannon() const {
	return static_cast<Cannon*>(children[CHILD_CANNON]);
}

Player* Player::getOpponent(){
	return static_cast<Player*>(children[CHILD_OPPONENT]);
}

Player* Player::getOpponent() const{
	return static_cast<Player*>(children[CHILD_OPPONENT]);
}

float Player::getSpeed(const CellType type, const Direction dir) const {
  switch(type) {
      case GRASS_LEFT:
      case GRASS_MID:
      case GRASS_RIGHT:		return SPEED_NORMAL;
      case SLOPE_UP_05_1:
      case SLOPE_UP_05_2: 	if(dir == LEFT) return SPEED_FAST; else return SPEED_SLOW;
      case SLOPE_DOWN_05_1:
      case SLOPE_DOWN_05_2: if(dir == LEFT) return SPEED_SLOW; else return SPEED_FAST;
      case SLOPE_UP_1: 		if(dir == LEFT) return SPEED_VERY_FAST; else return SPEED_VERY_SLOW;
      case SLOPE_DOWN_1: 	if(dir == LEFT) return SPEED_VERY_SLOW; else return SPEED_VERY_FAST;
      default: 				return SPEED_VERY_SLOW;
    }
  return SPEED_VERY_SLOW;
}

void Player::setOpponent(Player* _opponent){
	children[CHILD_OPPONENT] = _opponent;
}

/* Modification */
void Player::moveLeft(Terrain* terrain){
	float newOriginX = originX - getSpeed(terrain->getGround(originX/terrain->getCellWidth()).getType(), LEFT);
	initPosition(terrain, newOriginX);
}

void Player::moveRight(Terrain* terrain){
	float newOriginX = originX + getSpeed(terrain->getGround(originX/terrain->getCellWidth()).getType(), RIGHT);
	initPosition(terrain, newOriginX);
}

void Player::init() {
	nbGamesWon = 0;
	initGame();
}

void Player::initPosition(Terrain* terrain, float _originX){
	originY = terrain->getHeight(originX = _originX);
	angle =
		- PI/2 // -PI/2 car on est orthogonal au terrain !
		// Moyenne de pente de dans 1/4 de cell et de dans - 1/4  de cell
		+ terrain->getGround((originX+getHeight()/4)/terrain->getCellWidth()).getAngle()/2
		+ terrain->getGround((originX-getHeight()/4)/terrain->getCellWidth()).getAngle()/2;
	// TODO améliorer la continuité !
}

void Player::initGame() {
	life = 100;
	fury = false;
	getCannon()->init();
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
