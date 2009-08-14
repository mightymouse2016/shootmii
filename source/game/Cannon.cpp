#include "../ShootMii.h"

namespace shootmii {

Cannon::Cannon(
		const float _angleMin,
		const float _angleMax,
		const float _angle,
		const float _rotationStep,
		Wind* _wind,
		Player* _owner,
		int _playerNumber,
		Manager* _manager) :
	Rectangle(CANNON_LAYER,CANNON_WIDTH,CANNON_HEIGHT,TANK_HEIGHT/4,0,_angle,0,0,1,App::imageBank->get(TXT_CANNON),_owner),
	wind(_wind),
	heat(0),
	strength(0),
	angleMin(_angleMin),
	angleMax(_angleMax),
	rotationStep(_rotationStep),
	stillHeld(false),
	reloadTime(Timer(RELOAD_TIME)),
	blockedCannon(Timer(BLOCKING_TIME)),
	furyReloadTime(Timer(FURY_RELOAD_TIME)),
	manager(_manager),
	guidedMissile(NULL)
{
	GRRLIB_texImg *crossHair_image;
	switch (_playerNumber){
	case 1: crossHair_image = App::imageBank->get(TXT_CROSSHAIR1);break;
	case 2: crossHair_image = App::imageBank->get(TXT_CROSSHAIR2);break;
	default:crossHair_image = App::imageBank->get(TXT_CROSSHAIR1);break;
	}
	vertices.reserve(CHILDREN_STRENGTH + STRENGTH_JAUGE_STATES);
	addChild(new Rectangle(CROSSHAIR_LAYER, CROSSHAIR_WIDTH, CROSSHAIR_HEIGHT, 0, 0, CROSSHAIR_OVERTAKE, angle, 0, 1, crossHair_image, _owner));
	addChild(NULL);		//< Un emplacement pour la munition
	for (int i=0;i<STRENGTH_JAUGE_STATES;i++){
		addChild(
			new Rectangle(
					STRENGTH_JAUGE_LAYER,
					STRENGHT_JAUGE_SPRITE_WIDTH,
					STRENGHT_JAUGE_SPRITE_HEIGHT,
					CANNON_WIDTH/2,
					0,
					i*100/STRENGTH_JAUGE_STATES,
					0,0,0,
					App::imageBank->get(TXT_STRENGTH_SPRITES),
					this,
					i,
					STRENGHT_JAUGE_SPRITE_WIDTH,
					STRENGHT_JAUGE_SPRITE_HEIGHT,
					true));
	}
}

Cannon::~Cannon() {
	// NOTHING TO DO
	// guidedMissile destroyed by Manager
	// ammo and strength jauge destroyed by the Polygon class
}

void Cannon::destroyGuidedMissile(){
	guidedMissile->destroy(); // Le gestionnaire de collision se charge du reste
	guidedMissile = NULL;
}

void Cannon::loseInfluenceOnMissile(){
	guidedMissile = NULL;
}

void Cannon::init() {
	heat = 0;
	strength = 0;
	reloadTime.init();
	blockedCannon.init();
	furyReloadTime.init();
	if (isLoaded()) {
		delete getAmmo();
		setAmmo(NULL);
	}
	if (isGuidingMissile()) guidedMissile = NULL;		//< le Manager s'occupe d�j� de la suppression

}

float Cannon::getStrength() const {
	return strength;
}

float Cannon::getHeat() const {
	return heat;
}

float* Cannon::getPStrength(){
	return &strength;
}

float* Cannon::getPHeat(){
	return &heat;
}

Ammo* Cannon::getAmmo(){
	return static_cast<Ammo*>(children[CHILD_AMMO]);
}

Ammo* Cannon::getAmmo() const{
	return static_cast<Ammo*>(children[CHILD_AMMO]);
}

GuidedMissile* Cannon::getGuidedMissile(){
	return guidedMissile;
}

GuidedMissile* Cannon::getGuidedMissile() const{
	return guidedMissile;
}

Player* Cannon::getOwner(){
	return static_cast<Player*>(getFather());
}

Player* Cannon::getOwner() const{
	return static_cast<Player*>(getFather());
}

void Cannon::setAmmo(Ammo* _ammo){
	children[CHILD_AMMO] = _ammo;
}

void Cannon::computeHeat() {
	if (getOwner()->isInFuryMode()){
		heat -= HEAT_COOL_FAST_STEP;
	}
	else if (heat == 100) {
		if (blockedCannon.timeIsOver()) heat -= HEAT_COOL_SLOW_STEP;
		else blockedCannon.compute();
	}
	else if (heat > 50) heat -= HEAT_COOL_SLOW_STEP;			//< Mode lent quand le canon est chaud
	else if (heat > 0) heat -= HEAT_COOL_FAST_STEP;					//< Mode normal 50 premiers % de la jauge
	if (heat < 0) heat = 0;
}

void Cannon::up(){
	stillHeld = false;
}

void Cannon::rotateLeft() {
	angle -= rotationStep;
	if (angle < angleMin) angle = angleMin;
	if (isLoaded()) getAmmo()->setAngle(angle);
}

void Cannon::rotateRight() {
	angle += rotationStep;
	if (angle > angleMax) angle = angleMax;
	if (isLoaded()) getAmmo()->setAngle(angle);
}

void Cannon::incStrength(){
	if (getOwner()->isInFuryMode()) return;
	if (!isLoaded()) return;	//< Si il n'y a pas de munition dans le canon
	if (heat == 100) return;
	strength+=STRENGTHEN_STEP;
	if (strength >= 100) {
		strength = 100;
		shoot();
		stillHeld = true;
	}
}

void Cannon::incHeat(){
	if (getOwner()->isInFuryMode()){
		heat += HEAT_INC_STEP;
		if (heat > 100) heat = 100;
		return;
	}
	heat += HEAT_INC_STEP;
	if (heat > 100) {				// Le timer �tait bloqu� sur un multiple du temps de blocage
		heat = 100;					// ici, on le d�phase un peu, ainsi computeHeat() va r��quillibrer
		strength = 0;				// le Timer avant de faire baisser la jauge de heat.
		blockedCannon.init();		// Le init, sert � p�naliser le joueur si il essaie de tirer
		blockedCannon.compute();	// alors que l'attente n'est pas termin�e.
	}
}

void Cannon::compute(){
	computeStrengthJauge();
	computeReload();
	computeHeat();
}

void Cannon::computeStrengthJauge(){
	if (getOwner()->isInFuryMode()) return;
	int showLimit = strength*STRENGTH_JAUGE_STATES/100;
	for (int i=0;i<showLimit;i++) children[CHILDREN_STRENGTH+i]->show();
	for (int i=showLimit;i<STRENGTH_JAUGE_STATES;i++) children[CHILDREN_STRENGTH+i]->hide();
}

void Cannon::shoot() {
	if (!isLoaded()) return;	//< Si il n'y a pas de munition dans le canon
	incHeat();
	if (getOwner()->isInFuryMode()) strength = 100;
	else if (heat == 100) return;	//< Si le canon est trop chaud, on ne peux pas tirer
	getAmmo()->init(strength);
	guidedMissile = dynamic_cast<GuidedMissile*>(getAmmo());	//< Cas ou l'on a un missile t�l�-guid�
	setAmmo(NULL);
	strength = 0;

	App::console->addDebug("recul = %d",int(SHOT_RECOIL*sin(angle)));
	getOwner()->addRecoil(SHOT_RECOIL*sin(angle));
}

void Cannon::computeReload() {
	if (isLoaded()) return;
	if (getOwner()->isInFuryMode()){
		furyReloadTime.compute();
		if (furyReloadTime.timeIsOver()) {
			if (rand()%FURY_HOMING_PROBABILITY) loadCannon();
			else loadHoming();
		}
	}
	else{
		reloadTime.compute();
		if (reloadTime.timeIsOver() && !stillHeld) loadCannon();
	}
}

void Cannon::loadCannon(){
	if (isLoaded() || isGuidingMissile()) return;
	Player* owner = getOwner();
	GRRLIB_texImg* ammoImage = NULL;
	switch(owner->getPlayerNumber()){
		case 1: ammoImage = App::imageBank->get(TXT_AMMO1);break;
		case 2: ammoImage = App::imageBank->get(TXT_AMMO2);break;
		default: ammoImage = App::imageBank->get(TXT_AMMO1);break;
	}
	setAmmo(new CannonBall(angle, wind, ammoImage, owner, owner->getTerrain(), manager));
}

void Cannon::loadHoming(){
	// Le homing se met � la place de l'autre munition si il y en a une
	if (isLoaded()) delete children[CHILD_AMMO];
	Player* owner = getOwner();
	GRRLIB_texImg* ammoImage = NULL;
	switch(owner->getPlayerNumber()){
		case 1: ammoImage = App::imageBank->get(TXT_HOMING1);break;
		case 2: ammoImage = App::imageBank->get(TXT_HOMING2);break;
		default: ammoImage = App::imageBank->get(TXT_HOMING1);break;
	}
	setAmmo(new HomingMissile(angle, wind, ammoImage, owner, owner->getTerrain(), manager));
}

void Cannon::loadGuided(){
	if (getOwner()->isInFuryMode()) return;
	// Le guided se met � la place de l'autre munition si il y en a une
	if (isLoaded()) delete children[CHILD_AMMO];
	Player* owner = getOwner();
	GRRLIB_texImg* ammoImage = NULL;
	switch(owner->getPlayerNumber()){
		case 1: ammoImage = App::imageBank->get(TXT_GUIDED1);break;
		case 2: ammoImage = App::imageBank->get(TXT_GUIDED2);break;
		default: ammoImage = App::imageBank->get(TXT_GUIDED1);break;
	}
	setAmmo(new GuidedMissile(angle, wind, ammoImage, owner, owner->getTerrain(), manager));
}

bool Cannon::isLoaded() const{
	return (getAmmo() != NULL);
}

bool Cannon::isGuidingMissile() const{
	return (guidedMissile != NULL);
}


}
