#include "../ShootMii.h"

namespace shootmii {

Cannon::Cannon(
		const float _angleMin,
		const float _angleMax,
		const float _angle,
		const float _rotationStep,
		Wind* _wind,
		Player* _owner,
		int _playerNumber) :
	Rectangle(CANNON_WIDTH,CANNON_HEIGHT,TANK_HEIGHT/4,0,_angle,0,0,1,App::imageBank->get(TXT_CANNON),_owner),
	angleMin(_angleMin),
	angleMax(_angleMax),
	rotationStep(_rotationStep),
	wind(_wind),
	strength(0),
	heat(0),
	blockedTime(0),
	heatCool(0),
	reloadTime(0),
	stillHeld(false)
{
	GRRLIB_texImg *crossHair_image, *ammo_Image;
	switch (_playerNumber){
	case 1:
		ammo_Image = App::imageBank->get(TXT_AMMO1);
		crossHair_image = App::imageBank->get(TXT_CROSSHAIR1);
		break;
	case 2:
		ammo_Image = App::imageBank->get(TXT_AMMO2);
		crossHair_image = App::imageBank->get(TXT_CROSSHAIR2);
		break;
	default:
		ammo_Image = App::imageBank->get(TXT_AMMO1);
		crossHair_image = App::imageBank->get(TXT_CROSSHAIR1);
		break;
	}
	vertices.reserve(2);
	addChild(new Rectangle(CROSSHAIR_WIDTH, CROSSHAIR_HEIGHT, 0, 0, CROSSHAIR_OVERTAKE, angle, 0, 1, crossHair_image, _owner));
	addChild(new CannonBall(angle,wind,ammo_Image,_owner,static_cast<Player*>(getFather())->getTerrain()));
	for (int i=0;i<STRENGHT_JAUGE_STATES;i++){
		addChild(
			new Rectangle(
					STRENGHT_JAUGE_SPRITE_WIDTH,
					STRENGHT_JAUGE_SPRITE_HEIGHT,
					CANNON_WIDTH/2,
					0,
					i*100/STRENGHT_JAUGE_STATES,
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
	if (isLoaded()) delete getAmmo();
}

void Cannon::init() {
	strength = 0;
	for (int i=0;i<STRENGHT_JAUGE_STATES;i++){
		children[CHILDREN_STRENGHT+i]->hide();
	}
	heat = 0;
	blockedTime = 0;
	heatCool = 0;
	reloadTime = 0;
	if (isLoaded()) delete getAmmo();
	GRRLIB_texImg* image;
	switch (static_cast<Player*>(getFather())->getPlayerNumber()){
	case 1: image = App::imageBank->get(TXT_AMMO1);break;
	case 2: image = App::imageBank->get(TXT_AMMO2);break;
	//default : image = App::imageBank->get(TXT_AMMO1);break;
	}
	setAmmo(new CannonBall(angle, wind, image, static_cast<Player*>(getFather()),static_cast<Player*>(getFather())->getTerrain()));
	getAmmo()->setAngle(angle);
}

int Cannon::getStrength() const {
	return strength;
}

int Cannon::getHeat() const {
	return heat;
}

int Cannon::getBlockedTime() const {
	return blockedTime;
}

Ammo* Cannon::getAmmo(){
	return static_cast<Ammo*>(children[CHILD_AMMO]);
}

Ammo* Cannon::getAmmo() const{
	return static_cast<Ammo*>(children[CHILD_AMMO]);
}

void Cannon::setAmmo(Ammo* _ammo){
	children[CHILD_AMMO] = _ammo;
}

void Cannon::decHeat() {
	heatCool++;
	if (heatCool > 10)
		heatCool = 0;
	u32 currentTime = ticks_to_millisecs(gettime());

	// Mode bloqué quand on a harcelé le canon
	if (heat == 100) {
		if (currentTime - blockedTime > BLOCKING_TIME) heat -= 1;
	}

	// Mode lent quand le canon est chaud
	else if (heat > 50) {
		if (!(heatCool % HEAT_COOL_SLOW)) heat -= 1;
	}

	// Mode normal 50 premiers % de la jauge
	else if (heat > 0) {
		if (!(heatCool % HEAT_COOL_FAST)) heat -= 1;
	}

	reload();
}

void Cannon::up(){
	stillHeld = false;
}

void Cannon::rotateLeft() {
	if (angle - rotationStep > angleMin) angle -= rotationStep;
	else angle = angleMin;
	if (isLoaded()) getAmmo()->setAngle(angle);
}

void Cannon::rotateRight() {
	if (angle + rotationStep < angleMax) angle += rotationStep;
	else angle = angleMax;
	if (isLoaded()) getAmmo()->setAngle(angle);
}

void Cannon::incStrength(Manager* manager){
	// Si il n'y a pas de munition dans le canon
	if (!isLoaded()) return;
	if (strength >= 100) {
		shoot(manager);
		for (int i=0;i<STRENGHT_JAUGE_STATES;i++){
			children[CHILDREN_STRENGHT+i]->hide();
		}
		stillHeld = true;
	}
	else {
		strength+=STRENGTHEN_STEP;
		children[CHILDREN_STRENGHT+strength*STRENGHT_JAUGE_STATES/100-1]->show();
	}
}

void Cannon::shoot(Manager* manager) {
	float cosinus = cos(getAbsolutePolygonAngle());
	float sinus = sin(getAbsolutePolygonAngle());
	// Si il n'y a pas de munition dans le canon
	if (!isLoaded()) return;
	// Saturation du canon
	if (heat + HEAT_STEP >= 100) {
		heat = 100;
		strength = 0;
		for (int i=0;i<STRENGHT_JAUGE_STATES;i++){
			children[CHILDREN_STRENGHT+i]->hide();
		}
		blockedTime = ticks_to_millisecs(gettime());
	}
	else heat += HEAT_STEP;
	// Si le canon est trop chaud, on ne peux pas tirer
	if (heat == 100) return;
	// A partir de ce point, le lancé est autorisé et a lieu !
	// Mise à jour des coefficients qui définissent l'inclinaison de la courbe (si on a bougé le cannon)
	getAmmo()->getCalcX()->setC(getAmmo()->getAbsoluteOriginX() + CANNON_LENGTH * cosinus); // X
	getAmmo()->getCalcY()->setC(getAmmo()->getAbsoluteOriginY() + CANNON_LENGTH * sinus); // Y
	getAmmo()->getCalcX()->setB(strength * cosinus); // X
	getAmmo()->getCalcY()->setB(strength * sinus); // Y
	// On libère la munition de l'emprise du cannon
	getAmmo()->setFather(NULL);
	// On confie la munition au manager
	getAmmo()->fire();
	getAmmo()->setRadial(0);
	manager->addAmmosToDraw(getAmmo());
	setAmmo(NULL);
	strength = 0;
	for (int i=0;i<STRENGHT_JAUGE_STATES;i++){
		children[CHILDREN_STRENGHT+i]->hide();
	}
}

void Cannon::reload() {
	if (!isLoaded())
		if (reloadTime > RELOAD_TIME) {
			setAmmo(new CannonBall(angle, wind, App::imageBank->get(TXT_AMMO1), static_cast<Player*>(getFather()),static_cast<Player*>(getFather())->getTerrain()));
			reloadTime = 0;
		} else if(!stillHeld){
			reloadTime++;
		}
}

bool Cannon::isLoaded() const{
	if (getAmmo()) return true;
	return false;
}


}
