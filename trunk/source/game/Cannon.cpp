#include "../ShootMii.h"

namespace shootmii {

Cannon::Cannon(
		const float _angleOffSet,
		const float _angleRange,
		const float _angle,
		const float _rotationStep,
		Wind* _wind,
		Player* _owner) :
	angleOffSet(_angleOffSet),
	angleRange(_angleRange),
	angle(_angle),
	rotationStep(_rotationStep),
	wind(_wind),
	strength(0),
	heat(0),
	blockedTime(0),
	heatCool(0),
	reloadTime(0),
	ammoLook(GRRLIB_LoadTexture(ammo_2)),
	cannonLook(GRRLIB_LoadTexture(cannon)),
	loadedAmmo(new CannonBall(angle * PI / 180,wind,&ammoLook,_owner)),
	owner(_owner)
{

}

Cannon::~Cannon() {
	if (loadedAmmo)
		delete loadedAmmo;
}

void Cannon::init() {
	strength = 0;
	heat = 0;
	blockedTime = 0;
	heatCool = 0;
	reloadTime = 0;
	if (loadedAmmo)
		delete loadedAmmo;
	loadedAmmo = new CannonBall(-angle * PI / 180, wind, &ammoLook, owner);
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
		if (currentTime - blockedTime > BLOCKING_TIME)
			heat -= 1;
	}

	// Mode lent quand le canon est chaud
	else if (heat > 50) {
		if (!(heatCool % HEAT_COOL_SLOW))
			heat -= 1;
	}

	// Mode normal 50 premiers % de la jauge
	else if (heat > 0) {
		if (!(heatCool % HEAT_COOL_FAST))
			heat -= 1;
	}

	reload();
}

void Cannon::draw(const int screenX, const int screenY) const {
	// On dessine la munition
	if (loadedAmmo) {
		loadedAmmo->setScreenX(screenX);
		loadedAmmo->setScreenY(screenY);
		loadedAmmo->draw();
	}
	// On dessine le canon
	GRRLIB_DrawImg(screenX, screenY, cannonLook, -angle, 1, 1, WHITE);
}

void Cannon::rotateLeft() {
	if (angle + rotationStep <= angleOffSet + angleRange)
		angle += rotationStep;
	else
		angle = angleOffSet + angleRange;
	if (loadedAmmo)
		loadedAmmo->setAngle(-angle * PI / 180);
}

void Cannon::rotateRight() {
	if (angle - rotationStep >= angleOffSet)
		angle -= rotationStep;
	else
		angle = angleOffSet;
	if (loadedAmmo)
		loadedAmmo->setAngle(-angle * PI / 180);
}

void Cannon::shoot(Manager* manager) {
	// Si le canon est trop chaud, on ne peux pas tirer
	if (heat == 100) return;
	if (loadedAmmo) {
		// Saturation du canon
		if (heat + HEAT_STEP >= 100) {
			heat = 100;
			blockedTime = ticks_to_millisecs(gettime());
		}
		// Ou incrémentation normale
		else heat += HEAT_STEP;

		float topCos = cos(angle * PI / 180);
		float topSin = sin(angle * PI / 180);
		// Mise à jour des coefficients qui définissent l'inclinaison de la courbe (si on a bougé le cannon)
		loadedAmmo->getCalcX()->setC(loadedAmmo->getScreenX() + CANNON_LENGTH * topCos); // X
		loadedAmmo->getCalcY()->setC(loadedAmmo->getScreenY() - CANNON_LENGTH * topSin); // Y
		loadedAmmo->getCalcX()->setB(DEFAULT_POWER * topCos); // X
		loadedAmmo->getCalcY()->setB(-DEFAULT_POWER * topSin); // Y
		// On confie la munition au manager
		manager->addAmmosToDraw(loadedAmmo);
		loadedAmmo = NULL;
	}

}

void Cannon::reload() {
	if (!loadedAmmo)
		if (reloadTime > RELOAD_TIME) {
			loadedAmmo = new CannonBall(-angle * PI / 180, wind, &ammoLook, owner);
			reloadTime = 0;
		} else reloadTime++;
}

}
