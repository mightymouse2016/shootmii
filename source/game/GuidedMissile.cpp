#include "../ShootMii.h"

namespace shootmii {

GuidedMissile::GuidedMissile(
	const float _angle,
	Wind* wind,
    GRRLIB_texImg* _ammoLook,
    Player* _owner,
    Terrain* _terrain,
    Manager* _manager,
    const float vX,
    const float vY,
    const float x,
    const float y) :
    	Ammo(
    		_angle,
    		_ammoLook,
    		new PolyDeg2(wind->getWindSpeed()*WIND_INFLUENCE_ON_AMMO/(2*100*AMMO_WEIGHT),vX,x),
    		new PolyDeg2(-GRAVITY/(2*AMMO_WEIGHT),-vY,y),
    		_owner,
    		_terrain,
    		_manager),
    	active(false)
{
	// La silhouette du homing (pour des intersections plus fines)
    vertices.reserve(8);
    vertices.push_back(Coordinates( 8,-2));
    vertices.push_back(Coordinates( 0,-2));
    vertices.push_back(Coordinates(-4,-5));
    vertices.push_back(Coordinates(-8,-5));
    vertices.push_back(Coordinates(-8, 5));
    vertices.push_back(Coordinates(-4, 5));
    vertices.push_back(Coordinates( 0, 2));
    vertices.push_back(Coordinates( 8, 2));
}

Animation* GuidedMissile::destruction(explosionType _type, Player* _playerHit) {
	App::soundBank->play(AMMO_BOOM);
    switch (_type){
    case HIT_ANOTHER_AMMO:
        return new Animation(
            EXPLOSION_LAYER,
			App::imageBank->get(TXT_CANNONBALL_AIR_EXPLOSION), // TODO trouver mieux
			originX,
			originY,
			0,
			0,
			0,
			NULL,
			GUIDED_AIR_EXPLOSION_WIDTH,
			GUIDED_AIR_EXPLOSION_HEIGHT,
			GUIDED_AIR_EXPLOSION_DURATION);
    case HIT_A_PLAYER:
        return new Animation(
            EXPLOSION_LAYER,
			App::imageBank->get(TXT_CANNONBALL_HIT_EXPLOSION), // TODO trouver mieux
			0,
			0,
			0,
			0,
			0,
			_playerHit,
			GUIDED_HIT_EXPLOSION_WIDTH,
			GUIDED_HIT_EXPLOSION_HEIGHT,
			GUIDED_HIT_EXPLOSION_DURATION);
    case HIT_THE_GROUND:
        return new Animation(
            EXPLOSION_LAYER,
			App::imageBank->get(TXT_CANNONBALL_GROUND_EXPLOSION), // TODO trouver mieux
			originX,
			terrain->getHeight(originX),
			HOMING_GROUND_EXPLOSION_HEIGHT/2 - HOMING_GROUND_EXPLOSION_DEPTH,
			terrain->getAngle(originX) - PI/2,
			PI/2,
			NULL,
			GUIDED_GROUND_EXPLOSION_WIDTH,
			GUIDED_GROUND_EXPLOSION_HEIGHT,
			GUIDED_GROUND_EXPLOSION_DURATION);
    }
    return NULL;
}

void GuidedMissile::deleteMe(){
	Ammo::deleteMe();
	owner->getCannon()->loseInfluenceOnMissile();
}

void GuidedMissile::rotateRight(){
	angle += GUIDED_ROTATION_STEP;
}

void GuidedMissile::rotateLeft(){
	angle -= GUIDED_ROTATION_STEP;
}

void GuidedMissile::computeSmoklets() {
	if (!active) return;
	manager->addAnimation(
		new Animation(
			SMOKLET_LAYER,
			App::imageBank->get(TXT_HOMING_SMOKE),
			originX+HOMING_SMOKE_OVERTAKE*cos(angle),
			originY+HOMING_SMOKE_OVERTAKE*sin(angle),
			0,0,0,NULL,
			HOMING_SMOKE_WIDTH,
			HOMING_SMOKE_HEIGHT,
			HOMING_SMOKE_DURATION,
			HOMING_SMOKE_SLOW,
			1,
			new PolyDeg2(manager->getWind()->getWindSpeed()*WIND_INFLUENCE_ON_SMOKE/(2*100* SMOKE_WEIGHT),0,originX+HOMING_SMOKE_OVERTAKE*cos(angle)),
			new PolyDeg2(-GRAVITY*SMOKE_AIR_RESISTANCE/2,0,originY+HOMING_SMOKE_OVERTAKE*sin(angle))));
}

void GuidedMissile::computePosition() {
	float _t = getT();
	// Avant d'être activée la munition tourne sur elle même et a une trajectoire parabolique
	if (_t < GUIDED_ACTIVATION_DELAY){
		originX = (*calcX)(_t);
		originY = (*calcY)(_t);
		angle += GUIDED_SPIN_ANGLE;
	}
	else {
		// A l'activation, elle se positionne sur la trajectoire du lancé
		if (!active){
			angle = atan2((*calcY)[_t],(*calcX)[_t]);
			active = true;
		}
		// Après activation son angle est asservi, de manière a ce que l'angle entre la munition et l'adversaire soit nul
		originX += GUIDED_SPEED*cos(angle);
		originY += GUIDED_SPEED*sin(angle);
	}
}

}
