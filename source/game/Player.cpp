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
	const float _life,
	const float _fury,
	Manager* _manager) :
		Rectangle(TANK_LAYER,TANK_HEIGHT,TANK_WIDTH,0,0,TANK_HEIGHT/2,-PI/2,0,1,App::imageBank->get(TXT_TANK)),
		playerNumber(_playerNumber),
		recoil(0),
		score(0),
		life(_life),
		fury(_fury),
		nbGamesWon(0),
		terrain(_terrain)
{
	children.reserve(2);
	addChild(new Cannon(_angleMin, _angleMax, _angle, _rotationStep,_wind, this, _playerNumber, _manager));
}

int Player::getPlayerNumber() const{
	return playerNumber;
}

int Player::getCol() const{
	return originX/terrain->getCellWidth();
}

int Player::getRow() const{
	return originY/terrain->getCellHeight();
}

float Player::getLife() const {
	return life;
}

float Player::getFury() const{
	return fury;
}

float* Player::getPLife(){
	return &life;
}

float* Player::getPFury(){
	return &fury;
}

int Player::getScore() const {
	return score;
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

void Player::moveLeft(float speed){
	float oldOriginX = originX;
	float newOriginX = originX - speed*getSpeed(terrain->getGround(originX/terrain->getCellWidth()).getType(), LEFT);
	if (newOriginX < getHeight()/2) newOriginX = getHeight()/2;
	initPosition(newOriginX);
	if (intersect(getOpponent())) initPosition(oldOriginX);
}

void Player::moveRight(float speed){
	float oldOriginX = originX;
	float newOriginX = originX + speed*getSpeed(terrain->getGround(originX/terrain->getCellWidth()).getType(), RIGHT);
	if (newOriginX > terrain->getCols()*terrain->getCellWidth() - getHeight()/2) newOriginX = terrain->getCols()*terrain->getCellWidth() - getHeight()/2;
	initPosition(newOriginX);
	if (intersect(getOpponent())) initPosition(oldOriginX);
}

void Player::init() {
	nbGamesWon = 0;
	initGame();
}

void Player::initPosition(float _originX){
	originY = terrain->getHeight(originX = _originX);
	angle = terrain->getAngle(originX) - PI/2; // -PI/2 pour l'othogonalité au terrain
}

void Player::initGame() {
	recoil = 0;
	life = 100;
	getCannon()->init();
}

void Player::setScore(const int _score) {
	score = _score;
}

void Player::incScore() {
	score++;
}

void Player::setLife(const int _life){
	life = _life;
}

void Player::winLife(float lifeAmount){
	life += lifeAmount;
	if (life > 100) life = 100;
}

void Player::loseLife(float lifeAmount) {
	life -= lifeAmount;
	if (life < 0) life = 0;
}

void Player::winFury(float furyAmount){
	fury += furyAmount;
	if (fury > 100) fury = 100;
}

void Player::loseFury(float furyAmount){
	fury -= furyAmount;
	if (fury < 0) fury = 0;
}

void Player::computeDamage(Ammo* ammo){
    float x = ammo->getAbsoluteX() - getAbsoluteX();
    float y = ammo->getAbsoluteY() - getAbsoluteY();
    int distance = sqrt(x*x+y*y);
    if (distance > MINIMUM_LENGTH_FOR_DAMAGE) return;
    int degat = (MINIMUM_LENGTH_FOR_DAMAGE - distance)*DAMAGE_COEF;
    int intensity = (MINIMUM_LENGTH_FOR_DAMAGE - distance)*RECOIL_COEF;

    //Debug
    char buffer[100];
    sprintf(buffer, "Distance = %d; Degat = %d;", distance, degat);
    App::console->addDebug(buffer);

    loseLife(degat);
    if (x < 0) addRecoil(-intensity);
    else addRecoil(intensity);
}

void Player::computeRecoil(){
	if (recoil > 0) {
		App::console->addDebug("<-- Recoil");
		moveLeft(recoil);
		recoil--;
	}
	if (recoil < 0) {
		App::console->addDebug("Recoil -->");
		moveRight(-recoil);
		recoil++;
	}
}

void Player::addRecoil(int intensity){
	recoil += intensity;
}

}
