#include "../world/Terrain.h"
#include "../world/Wind.h"
#include "../tools/ImageBank.h"
#include "../tools/Console.h"
#include "../tools/Colors.h"
#include "../tools/Tools.h"
#include "../math/PolyDeg2.h"
#include "../math/Pulse.h"
#include "../App.h"
#include "HomingMissile.h"
#include "GuidedMissile.h"
#include "JaugeManager.h"
#include "Manager.h"
#include "Cannon.h"
#include "Bonus.h"
#include "Ammo.h"
#include "IA.h"
#include "Player.h"

namespace shootmii {

Player::Player(
	Terrain* _terrain,
	Wind* _wind,
	const unsigned int _playerNumber,
	const float _angleMin,
	const float _angleMax,
	const float _angle,
	const float _rotationStep,
	const float _life,
	const float _fury,
	Manager* _manager) :
		Rectangle(TANK_LAYER,TANK_HEIGHT,TANK_WIDTH,0,0,TANK_HEIGHT/2,-PI/2,0,true,true,App::imageBank->get(TXT_TANK),NULL,0,TANK_HEIGHT,TANK_WIDTH),
		playerNumber(_playerNumber),
		score(0),
		recoil(0),
		lifeModificationFlag(false),
		life(_life),
		fury(_fury),
		laserRemainingTime(0),
		shieldRemainingTime(0),
		furyMode(false),
		iaMode(false),
		terrain(_terrain),
		manager(_manager),
		bonus(NULL),
		damageSmokletTimer(new Timer(DAMAGE_SMOKLET_STATES)),
		damagePulseTimer(new Timer),
		damagePulse(new Pulse(DAMAGE_PULSE_R1,DAMAGE_PULSE_R2,DAMAGE_PULSE_PERIOD)),
		ia(new IA(this))
{
	children.reserve(2);
	addChild(new Cannon(_angleMin, _angleMax, _angle, _rotationStep,_wind, this, _playerNumber, _manager));
}

Player::~Player(){
	// On libère le bonus car l'App ne s'en occupe plus
	delete bonus;
	delete damageSmokletTimer;
	delete damagePulseTimer;
	delete damagePulse;
	delete ia;
}

unsigned int Player::getPlayerNumber() const{
	return playerNumber;
}

unsigned int Player::getScore() const {
	return score;
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

bool* Player::getPFuryMode(){
	return &furyMode;
}

float* Player::getPLaserRemainingTime(){
	return &laserRemainingTime;
}

float* Player::getPShieldRemainingTime(){
	return &shieldRemainingTime;
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

float Player::getSpeed(const int type, const Direction dir) const {
	float speed;
	switch(type) {
		case GRASS_LEFT:
		case GRASS_MID:
		case GRASS_RIGHT:		speed = SPEED_NORMAL;break;
		case SLOPE_UP_05_1:
		case SLOPE_UP_05_2: 	speed = dir == LEFT ? SPEED_FAST : SPEED_SLOW;break;
		case SLOPE_DOWN_05_1:
		case SLOPE_DOWN_05_2:	speed = dir == LEFT ? SPEED_SLOW : SPEED_FAST;break;
		case SLOPE_UP_1: 		speed = dir == LEFT ? SPEED_VERY_FAST : SPEED_VERY_SLOW;break;
		case SLOPE_DOWN_1: 		speed = dir == LEFT ? SPEED_VERY_SLOW : SPEED_VERY_FAST;break;
		default: 				speed = SPEED_VERY_SLOW;break;
	}
	if (life < DAMAGE_SPEED_LIFE_LIMIT) return speed*life/DAMAGE_SPEED_LIFE_LIMIT;
	return speed;
}

Bonus* Player::getBonus(){
	return bonus;
}

Bonus** Player::getPBonus(){
	return &bonus;
}

bool Player::isInFuryMode() const{
	return furyMode;
}

bool Player::isInIAMode() const{
	return iaMode;
}

bool Player::isInLaserMode() const{
	return laserRemainingTime > 0;
}

bool Player::isInShieldMode() const{
	return shieldRemainingTime > 0;
}

void Player::setOpponent(Player* _opponent){
	children[CHILD_OPPONENT] = _opponent;
}

void Player::setScore(const unsigned int _score) {
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
	Manager::jaugeManager->addIncrease(&life,lifeAmount,&lifeModificationFlag);
}

void Player::loseLife(const float lifeAmount) {
	Manager::jaugeManager->addDecrease(&life,lifeAmount,&lifeModificationFlag);
}

void Player::setFury(const float furyAmount){
	fury = furyAmount;
}

void Player::winFury(const float furyAmount){
	Manager::jaugeManager->addIncrease(&fury,furyAmount);
}

void Player::loseFury(const float furyAmount){
	Manager::jaugeManager->addDecrease(&fury,furyAmount);
}

void Player::beginFuryMode(){
	furyMode = true;
}

void Player::stopFuryMode(){
	furyMode = false;
}

void Player::setIA(const bool ia){
	iaMode = ia;
}

void Player::beginLaserMode(){
	laserRemainingTime = 100;
}

void Player::stopLaserMode(){
	laserRemainingTime = 0;
}

void Player::beginShieldMode(){
	shieldRemainingTime = 100;
}

void Player::stopShieldMode(){
	shieldRemainingTime = 0;
}

void Player::addRecoil(int intensity){
	recoil += intensity;
}

void Player::addBonus(Bonus* _bonus){
	if (_bonus->isImmediate()){		//< Si immediat : consommation
		useBonus(_bonus);
		_bonus->finish();
	}
	else if (bonus) { 		//< si le joueur a déjà un bonus (surtout pas de delete de
		_bonus->finish();	//< _bonus car le Manager s'en occupe !) dans le cas
	}						//< contraire, crash possible (car le gestionnaire de collision
	else {					//< boucle sur la liste de bonus pour chaque munition)
		App::console->addDebug("Player %d : Bonus added",getPlayerNumber());
		bonus = _bonus;
		bonus->possess();
		if (getPlayerNumber() == 1) bonus->setOriginX(SCREEN_WIDTH/2-BONUS_X);
		else bonus->setOriginX(SCREEN_WIDTH/2+BONUS_X);
		bonus->setOriginY(BONUS_Y);
	}
}

void Player::initGame() {
	score = 0;
	fury = 0;
	laserRemainingTime = 0;
	shieldRemainingTime = 0;
	if (bonus) delete bonus;
	bonus = NULL;
	initRound();
}

void Player::initRound() {
	// on conserve son bonus d'une manche à l'autre
	if (isInFuryMode()) {	//< Si le joueur était en mode fury, on lui enlève toute sa fury
		fury = 0;
		stopFuryMode();
	}
	laserRemainingTime = 0;
	shieldRemainingTime = 0;
	recoil = 0;
	life = 100;
	damageSmokletTimer->init();
	damagePulseTimer->init();
	getCannon()->init();
}

void Player::initPosition(float _originX){
	originY = terrain->getHeight(originX = _originX);
	angle = terrain->getAngle(originX) - PI/2; // -PI/2 pour l'othogonalité au terrain
}

void Player::useBonus(Bonus* _bonus){
	if (_bonus == NULL) return;
	switch (_bonus->getType()){
	case HOMING:
		getCannon()->loadHoming();
		App::console->addDebug("bonus used : homing missile");break;
	case LIFE_RECOVERY:
		winLife(35);
		App::console->addDebug("bonus used : life recovery");break;
	case GUIDED:
		getCannon()->loadGuided();
		App::console->addDebug("bonus used : guided missile");break;
	case POISON:
		loseLife(35);
		App::console->addDebug("bonus used : life loss");break;
	case POTION:
		winFury(25);
		App::console->addDebug("bonus used : fury potion");break;
	case CROSS_HAIR:
		beginLaserMode();
		App::console->addDebug("bonus used : cross hair");break;
	case SHIELD:
		beginShieldMode();
		App::console->addDebug("bonus used : cross hair");break;
	default:
		App::console->addDebug("bonus used : unknown type");break;
	}
}

void Player::shieldImpact(){
	shieldRemainingTime -=SHIELD_IMPACT_DEC_STEP;
	if (shieldRemainingTime < 0) shieldRemainingTime = 0;
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

void Player::computeLaserMode(){
	if (laserRemainingTime == 0) return;
	laserRemainingTime -= LASER_DEC_STEP;
	if (laserRemainingTime < 0) laserRemainingTime = 0;
}

void Player::computeShieldMode(){
	shieldRemainingTime -= SHIELD_DEC_STEP;
	if (shieldRemainingTime < 0) shieldRemainingTime = 0;
}

void Player::computeDamage(Ammo* ammo){
    float x = ammo->getAbsoluteX() - getAbsoluteX();
    float y = ammo->getAbsoluteY() - getAbsoluteY();
    int distance = sqrt(x*x+y*y);
    if (distance > MINIMUM_LENGTH_FOR_DAMAGE) return;
    int degat = (MINIMUM_LENGTH_FOR_DAMAGE - distance)*DAMAGE_COEF;
    int intensity = (MINIMUM_LENGTH_FOR_DAMAGE - distance)*RECOIL_COEF;
    loseLife(degat);
    if (x < 0) addRecoil(-intensity);
    else addRecoil(intensity);
    App::console->addDebug("Distance = %d; Damage = %d;", distance, degat);
}

void Player::computeDegradation(){
	if (life >= 100*(DAMAGE_SMOKLET_STATES-1)/DAMAGE_SMOKLET_STATES) return;

	damageSmokletTimer->compute();
	if (damageSmokletTimer->timeIsOver()){
		damageSmokletTimer->setSlow(life*DAMAGE_SMOKLET_STATES/100+1);
		float projectionAngle = PI/4 + (rand()%1000)*PI/(2*1000);
		LayerPriority smokletLayer = (rand()%BACK_SMOKLETS_RATIO) ? SMOKLET_LAYER : FRONT_SMOKLET_LAYER;
		manager->addAnimation(
			new Animation(
					smokletLayer,
					App::imageBank->get(TXT_HOMING_SMOKE),
					originX+getHeight()*cos(getAbsoluteAngle())/2,
					originY+getWidth()*sin(getAbsoluteAngle())/2,
					0,0,0,NULL,
					HOMING_SMOKE_WIDTH,
					HOMING_SMOKE_HEIGHT,
					HOMING_SMOKE_DURATION,
					HOMING_SMOKE_SLOW,
					1,
					new PolyDeg2(manager->getWind()->getWindSpeed()*WIND_INFLUENCE_ON_SMOKE/(2*100* SMOKE_WEIGHT),DAMAGE_SMOKLET_INITIAL_SPEED*cos(projectionAngle),originX+getHeight()*cos(getAbsoluteAngle())/2),
					new PolyDeg2(-(GRAVITY* SMOKE_WEIGHT*SMOKE_AIR_RESISTANCE/2-ARCHIMEDE)/GRAVITY,-DAMAGE_SMOKLET_INITIAL_SPEED*sin(projectionAngle),originY+getWidth()*sin(getAbsoluteAngle())/2),
					DEFAULT_TIME_STEP,
					true,
					colorFadeOut(TRANSPARENT, 0xffffff77, life/100),
					BLACK & TRANSPARENT));
	}

	damagePulseTimer->compute();
	if (!lifeModificationFlag){
		damagePulse->setR2(1-life/100);
		damagePulse->setAmplitude(1-life/100);
		damagePulse->setPeriod(DAMAGE_PULSE_PERIOD*life/100);
	}
}

void Player::computeRecoil(){
	if (recoil > 0) {
		moveLeft(recoil);
		recoil--;
		App::console->addDebug("<-- Recoil");
	}
	if (recoil < 0) {
		moveRight(-recoil);
		recoil++;
		App::console->addDebug("Recoil -->");
	}
}

void Player::computeIA(){
	if (isInIAMode()) ia->compute();
}

void Player::compute(){
	getCannon()->compute();
	computeRecoil();
	computeFuryMode();
	computeLaserMode();
	computeShieldMode();
	computeDegradation();
	computeIA();
}

void Player::draw(){
	if (isInIAMode()) ia->draw();
	setSprite(0);
	setColorFilter(WHITE);
	Rectangle::draw();
	setSprite(1);
	setColorFilter(colorFadeOut(WHITE,TRANSPARENT,(100-getLife())/100));
	Rectangle::draw();
	setSprite(2);
	setColorFilter(colorFadeOut(RED & TRANSPARENT, RED, 1-(*damagePulse)(damagePulseTimer->getT())));
	Rectangle::draw();
}

void Player::dealEvent(const u32* playerEvents){
	const u32 padHeld = playerEvents[HELD];
	const u32 padDown = playerEvents[DOWN];
	const u32 padUp = playerEvents[UP];

	//if (isInIAMode()) return;

	if (padHeld & WPAD_BUTTON_UP) 		KeyUp(HELD);
	if (padHeld & WPAD_BUTTON_DOWN) 	KeyDown(HELD);
	if (padHeld & WPAD_BUTTON_LEFT) 	KeyLeft(HELD);
	if (padHeld & WPAD_BUTTON_RIGHT) 	KeyRight(HELD);
	if (padHeld & WPAD_BUTTON_A) 		KeyA(HELD);
	if (padDown & WPAD_BUTTON_A) 		KeyA(DOWN);
	if (padUp & WPAD_BUTTON_A) 			KeyA(UP);
	if (padDown & WPAD_BUTTON_B) 		KeyB(DOWN);
	if (padDown & WPAD_BUTTON_PLUS) 	KeyPlus(DOWN);
}

void Player::KeyUp(EventType type){
	switch (type){
	case HELD:
		if (playerNumber == 1) getCannon()->rotateLeft();
		else getCannon()->rotateRight();
		break;
	case DOWN:break;
	case UP:break;
	}
}

void Player::KeyDown(EventType type){
	switch (type){
	case HELD:
		if (playerNumber == 1) getCannon()->rotateRight();
		else getCannon()->rotateLeft();
		break;
	case DOWN:break;
	case UP:break;
	}
}

void Player::KeyLeft(EventType type){
	switch (type){
		case HELD:
			if (getCannon()->isGuidingMissile()) getCannon()->getGuidedMissile()->rotateLeft();
			else moveLeft();
			break;
		case DOWN:break;
		case UP:break;
	}
}

void Player::KeyRight(EventType type){
	switch (type){
	case HELD:
		if (getCannon()->isGuidingMissile()) getCannon()->getGuidedMissile()->rotateRight();
		else moveRight();
		break;
	case DOWN:break;
	case UP:break;
	}
}

void Player::KeyA(EventType type){
	switch (type){
	case HELD:
		getCannon()->incStrength();
		break;
	case DOWN:
		if (getCannon()->isGuidingMissile()) getCannon()->destroyGuidedMissile();
		//WPAD_Rumble(WPAD_CHAN_0, 1);
		break;
	case UP:
		getCannon()->up();
		getCannon()->shoot();
		//WPAD_Rumble(WPAD_CHAN_0, 0);
		break;
	}
}

void Player::KeyB(EventType type){
	switch (type){
	case HELD:break;
	case DOWN:
		useBonus(bonus);
		if (bonus) delete bonus;
		bonus = NULL;
		break;
	case UP:break;
	}
}

void Player::KeyMinus(EventType type){
	switch (type){
	case HELD:break;
	case DOWN:break;
	case UP:break;
	}
}

void Player::KeyPlus(EventType type){
	switch (type){
	case HELD:break;
	case DOWN:
		if(GRRLIB_ScrShot("Screenshot.png")) App::console->addDebug("A screenshot was taken!!!");
		else App::console->addDebug("Screenshot did not work!!!");break;
	case UP:break;
	}
}


}
