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
	Rectangle(CANNON_WIDTH,CANNON_HEIGHT,0,0,TANK_HEIGHT/4,0,_angle,1,App::imageBank->get(TXT_CANNON),_owner),
	angleMin(_angleMin),
	angleMax(_angleMax),
	rotationStep(_rotationStep),
	wind(_wind),
	strength(0),
	heat(0),
	blockedTime(0),
	heatCool(0),
	reloadTime(0),
	loadedAmmo(new CannonBall(angle,wind,ammoLook,_owner)),
	stillHeld(false)
{
	switch (_playerNumber){
	case 1:
		ammoLook = App::imageBank->get(TXT_AMMO1);
		//crossHair = App::imageBank->get(TXT_CROSSHAIR1);
		break;
	case 2:
		ammoLook = App::imageBank->get(TXT_AMMO2);
		//crossHair = App::imageBank->get(TXT_CROSSHAIR2);
		break;
	}
}

Cannon::~Cannon() {
	if (loadedAmmo) delete loadedAmmo;
}

void Cannon::init() {
	strength = 0;
	heat = 0;
	blockedTime = 0;
	heatCool = 0;
	reloadTime = 0;
	if (loadedAmmo) delete loadedAmmo;
	loadedAmmo = new CannonBall(angle, wind, ammoLook, static_cast<Player*>(getFather()));
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

/*
void Cannon::draw(const int screenX, const int screenY) const {
	int centerX = screenX + TANK_ROTATION_AXIS_X;
	int centerY = screenY + TANK_ROTATION_AXIS_Y;
	int beginStrenght = CANNON_WIDTH/2+AMMO_OVERTAKE;
	int strenghtRange = 100-CROSS_WIDTH/2-AMMO_OVERTAKE;
	int offset;
	float cosinus = cos(angle);
	float sinus = sin(angle);

	// On dessine la munition
	if (loadedAmmo) {
		loadedAmmo->setScreenX(screenX+AMMO_OVERTAKE*cosinus);
		loadedAmmo->setScreenY(screenY+AMMO_OVERTAKE*sinus);
		loadedAmmo->compute();
		loadedAmmo->draw();
	}
	// On dessine le canon
	GRRLIB_DrawImg(screenX, screenY, *cannonLook, angle*180/PI, 1, 1, WHITE);

	// On dessine le réticule de visée
		GRRLIB_DrawImg(
				centerX+(100-CROSS_WIDTH/2)*cosinus-CROSS_WIDTH/2,
				centerY+(100-CROSS_WIDTH/2)*sinus-CROSS_WIDTH/2,
				*crossHair,angle*180/PI, 1, 1, WHITE);

	// On dessine la jauge de puissance
		for (int i=0;i<strength*STRENGHT_JAUGE_STATES/100;i++){
			offset = beginStrenght+i*strenghtRange/STRENGHT_JAUGE_STATES;
			GRRLIB_DrawTile(
					centerX+offset*cosinus-STRENGHT_JAUGE_SPRITE_WIDTH/2,
					centerY+offset*sinus-STRENGHT_JAUGE_SPRITE_HEIGHT/2,
					*App::imageBank->get(TXT_STRENGTH_SPRITES), 0, 1, 1, WHITE, i);
		}
}
*/

void Cannon::rotateLeft() {
	if (polygonAngle - rotationStep > angleMin) polygonAngle -= rotationStep;
	else polygonAngle = angleMin;
	if (loadedAmmo) loadedAmmo->setAngle(polygonAngle);
}

void Cannon::rotateRight() {
	if (polygonAngle + rotationStep < angleMax) polygonAngle += rotationStep;
	else polygonAngle = angleMax;
	if (loadedAmmo) loadedAmmo->setAngle(polygonAngle);
}

void Cannon::incStrength(Manager* manager){
	// Si il n'y a pas de munition dans le canon
	if (!loadedAmmo) return;
	if (strength >= 100) {
		shoot(manager);
		stillHeld = true;
	}
	else strength+=STRENGTHEN_STEP;
}

void Cannon::shoot(Manager* manager) {
	float cosinus = cos(angle);
	float sinus = sin(angle);
	// Si il n'y a pas de munition dans le canon
	if (!loadedAmmo) return;
	// Saturation du canon
	if (heat + HEAT_STEP >= 100) {
		heat = 100;
		blockedTime = ticks_to_millisecs(gettime());
	}
	else heat += HEAT_STEP;
	// Si le canon est trop chaud, on ne peux pas tirer
	if (heat == 100) return;
	// Mise à jour des coefficients qui définissent l'inclinaison de la courbe (si on a bougé le cannon)
	loadedAmmo->getCalcX()->setC(loadedAmmo->getScreenX() + CANNON_LENGTH * cosinus); // X
	loadedAmmo->getCalcY()->setC(loadedAmmo->getScreenY() + CANNON_LENGTH * sinus); // Y
	loadedAmmo->getCalcX()->setB(strength * cosinus); // X
	loadedAmmo->getCalcY()->setB(strength * sinus); // Y
	// On confie la munition au manager
	loadedAmmo->fire();
	manager->addAmmosToDraw(loadedAmmo);
	loadedAmmo = NULL;
	strength = 0;
}

void Cannon::reload() {
	if (!loadedAmmo)
		if (reloadTime > RELOAD_TIME) {
			loadedAmmo = new CannonBall(angle, wind, ammoLook, static_cast<Player*>(getFather()));
			reloadTime = 0;
		} else if(!stillHeld){
			reloadTime++;
		}
}

bool Cannon::isLoaded() const{
	if (loadedAmmo) return true;
	return false;
}


}
