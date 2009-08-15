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
		furyMode(false),
		terrain(_terrain),
		bonus(NULL)
{
	children.reserve(2);
	addChild(new Cannon(_angleMin, _angleMax, _angle, _rotationStep,_wind, this, _playerNumber, _manager));
}

Player::~Player(){
	// On ne libère pas le bonus, le manager s'en charge
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

int Player::getScore() const {
	return score;
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

Bonus** Player::getPBonus(){
	return &bonus;
}

bool Player::isInFuryMode() const{
	return furyMode;
}

void Player::setOpponent(Player* _opponent){
	children[CHILD_OPPONENT] = _opponent;
}

void Player::setScore(const int _score) {
	score = _score;
}

void Player::incScore() {
	score++;
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

void Player::setLife(const float lifeAmount){
	life = lifeAmount;
}

void Player::winLife(const float lifeAmount){
	App::jaugeManager->addIncrease(&life,lifeAmount);
}

void Player::loseLife(const float lifeAmount) {
	App::jaugeManager->addDecrease(&life,lifeAmount);
}

void Player::setFury(const float furyAmount){
	fury = furyAmount;
}

void Player::winFury(const float furyAmount){
	App::jaugeManager->addIncrease(&fury,furyAmount);
}

void Player::loseFury(const float furyAmount){
	App::jaugeManager->addDecrease(&fury,furyAmount);
}

void Player::beginFuryMode(){
	furyMode = true;
}

void Player::stopFuryMode(){
	furyMode = false;
}

void Player::addRecoil(int intensity){
	recoil += intensity;
}

void Player::addBonus(Bonus* _bonus){
	if (bonus) { 			//< si le joueur a déjà un bonus (surtout pas de
		_bonus->finish();	//< delete de _bonus car le Manager s'en occupe !)
	}
	else {
		App::console->addDebug("Joueur %d : Bonus ajoute",getPlayerNumber());
		bonus = _bonus;
		bonus->possess();
		if (getPlayerNumber() == 1) bonus->setOriginX(SCREEN_WIDTH/2-BONUS_X);
		else bonus->setOriginX(SCREEN_WIDTH/2+BONUS_X);
		bonus->setOriginY(BONUS_Y);
	}
}

void Player::init() {
	nbGamesWon = 0;
	bonus = NULL;	//< Le manager fait déjà la destruction
	initGame();
}

void Player::initGame() {
	if (isInFuryMode()) {	//< Si le joueur était en mode fury, on lui enlève toute sa fury
		fury = 0;
		stopFuryMode();
	}
	recoil = 0;
	life = 100;
	getCannon()->init();
}

void Player::initPosition(float _originX){
	originY = terrain->getHeight(originX = _originX);
	angle = terrain->getAngle(originX) - PI/2; // -PI/2 pour l'othogonalité au terrain
}

void Player::computeFuryMode(){
	if (fury == 100) beginFuryMode();
	if (isInFuryMode()) {
		fury -= FURY_DEC_STEP;
		getCannon()->shoot();
	}
	if (fury < 0) {
		fury = 0;
		stopFuryMode();
	}
}

void Player::useBonus(){
	if (bonus == NULL) return;
	switch (bonus->getType()){
	case HOMING:
		getCannon()->loadHoming();
		App::console->addDebug("bonus : homing missile");break;
	case LIFE_RECOVERY:
		winLife(35);
		App::console->addDebug("bonus : life recovery");break;
	case GUIDED:
		getCannon()->loadGuided();
		App::console->addDebug("bonus : guided missile");break;
	case POISON:
		loseLife(35);
		App::console->addDebug("bonus : life loss");break;
	case POTION:
		winFury(25);
		App::console->addDebug("bonus : fury potion");break;
	default:
		App::console->addDebug("bonus : type inconnu");break;
	}
	bonus->finish();
	bonus = NULL;
}

void Player::computeDamage(Ammo* ammo){
    float x = ammo->getAbsoluteX() - getAbsoluteX();
    float y = ammo->getAbsoluteY() - getAbsoluteY();
    int distance = sqrt(x*x+y*y);
    if (distance > MINIMUM_LENGTH_FOR_DAMAGE) return;
    int degat = (MINIMUM_LENGTH_FOR_DAMAGE - distance)*DAMAGE_COEF;
    int intensity = (MINIMUM_LENGTH_FOR_DAMAGE - distance)*RECOIL_COEF;
    App::console->addDebug("Distance = %d; Degat = %d;", distance, degat);	//< Debug
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

void Player::compute(){
	getCannon()->compute();
	computeRecoil();
	computeFuryMode();
}

}
