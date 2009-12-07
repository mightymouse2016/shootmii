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
		Rectangle(TANK_LAYER,TANK_HEIGHT,TANK_WIDTH,0,0,TANK_HEIGHT/2,-PI/2,0,true,true,App::imageBank->get(TXT_TANK),NULL,0,TANK_HEIGHT,TANK_WIDTH),
		playerNumber(_playerNumber),
		recoil(0),
		score(0),
		life(_life),
		fury(_fury),
		laserRemainingTime(0),
		shieldRemainingTime(0),
		furyMode(false),
		terrain(_terrain),
		manager(_manager),
		bonus(NULL)
{
	children.reserve(2);
	addChild(new Cannon(_angleMin, _angleMax, _angle, _rotationStep,_wind, this, _playerNumber, _manager));
}

Player::~Player(){
	// On lib�re le bonus car on est le Manager ne s'en occupe plus
	delete bonus;
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

float Player::getSpeed(const CellType type, const Direction dir) const {
  switch(type) {
      case GRASS_LEFT:
      case GRASS_MID:
      case GRASS_RIGHT:		return SPEED_NORMAL;
      case SLOPE_UP_05_1:
      case SLOPE_UP_05_2: 	return dir == LEFT ? SPEED_FAST : SPEED_SLOW;
      case SLOPE_DOWN_05_1:
      case SLOPE_DOWN_05_2: return dir == LEFT ? SPEED_SLOW : SPEED_FAST;
      case SLOPE_UP_1: 		return dir == LEFT ? SPEED_VERY_FAST : SPEED_VERY_SLOW;
      case SLOPE_DOWN_1: 	return dir == LEFT ? SPEED_VERY_SLOW : SPEED_VERY_FAST;
      default: 				return SPEED_VERY_SLOW;
    }
  return SPEED_VERY_SLOW;
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

bool Player::isInLaserMode() const{
	return laserRemainingTime > 0;
}

bool Player::isInShieldMode() const{
	return shieldRemainingTime > 0;
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
	Manager::jaugeManager->addIncrease(&life,lifeAmount);
}

void Player::loseLife(const float lifeAmount) {
	Manager::jaugeManager->addDecrease(&life,lifeAmount);
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
	else if (bonus) { 		//< si le joueur a d�j� un bonus (surtout pas de delete de
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

void Player::init() {
	score = 0;
	fury = 0;
	laserRemainingTime = 0;
	shieldRemainingTime = 0;
	if (bonus) delete bonus;
	bonus = NULL;
	initGame();
}

void Player::initGame() {
	// on conserve son bonus d'une manche � l'autre
	if (isInFuryMode()) {	//< Si le joueur �tait en mode fury, on lui enl�ve toute sa fury
		fury = 0;
		stopFuryMode();
	}
	laserRemainingTime = 0;
	shieldRemainingTime = 0;
	recoil = 0;
	life = 100;
	getCannon()->init();
}

void Player::initPosition(float _originX){
	originY = terrain->getHeight(originX = _originX);
	angle = terrain->getAngle(originX) - PI/2; // -PI/2 pour l'othogonalit� au terrain
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
	if (life > 50) return;
	if (rand()%static_cast<int>(life)) return;
	float projectionAngle = PI/4 + (rand()%1000)*PI/(2*1000);
	manager->addAnimation(
			new Animation(
				SMOKLET_LAYER,
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
				new PolyDeg2(-(GRAVITY* SMOKE_WEIGHT*SMOKE_AIR_RESISTANCE/2-ARCHIMEDE)/GRAVITY,-DAMAGE_SMOKLET_INITIAL_SPEED*sin(projectionAngle),originY+getWidth()*sin(getAbsoluteAngle())/2)));

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

void Player::compute(){
	getCannon()->compute();
	computeRecoil();
	computeFuryMode();
	computeLaserMode();
	computeShieldMode();
	computeDegradation();
}

void Player::draw(){
	setSprite(0);
	setColorFilter(WHITE);
	Rectangle::draw();
	setSprite(1);
	setColorFilter(applyRatioToRGBA(WHITE,(100-getLife())/100,0,0,0,1));
	Rectangle::draw();
}

void Player::dealEvent(const u32* playerEvents){
	const u32 padHeld = playerEvents[HELD];
	const u32 padDown = playerEvents[DOWN];
	const u32 padUp = playerEvents[UP];


	if (padHeld & WPAD_BUTTON_UP) 		KeyUp(HELD);
	if (padHeld & WPAD_BUTTON_DOWN) 	KeyDown(HELD);
	if (padHeld & WPAD_BUTTON_LEFT) 	KeyLeft(HELD);
	if (padHeld & WPAD_BUTTON_RIGHT) 	KeyRight(HELD);
	if (padHeld & WPAD_BUTTON_A) 		KeyA(HELD);
	if (padDown & WPAD_BUTTON_A) 		KeyA(DOWN);
	if (padUp & WPAD_BUTTON_A) 			KeyA(UP);
	if (padDown & WPAD_BUTTON_B) 		KeyB(DOWN);
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
	case DOWN:break;
	case UP:break;
	}
}


}
