#include "../ShootMii.h"

namespace shootmii {

HomingMissile::HomingMissile(
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
    		new PolyDeg2(-G/(2*AMMO_WEIGHT),-vY,y),
    		_owner,
    		_terrain,
    		_manager)
{
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

Animation* HomingMissile::destruction(explosionType _type, Player* _playerHit) {
    switch (_type){
    case HIT_ANOTHER_AMMO:
        return new Animation(
			App::imageBank->get(TXT_CANNONBALL_AIR_EXPLOSION), // TODO
			originX,
			originY,
			0,
			0,
			0,
			NULL,
			HOMING_AIR_EXPLOSION_WIDTH,
			HOMING_AIR_EXPLOSION_HEIGHT,
			HOMING_AIR_EXPLOSION_DURATION);
    case HIT_A_PLAYER:
        return new Animation(
			App::imageBank->get(TXT_CANNONBALL_HIT_EXPLOSION), // TODO
			0,
			0,
			0,
			0,
			0,
			_playerHit,
			HOMING_HIT_EXPLOSION_WIDTH,
			HOMING_HIT_EXPLOSION_HEIGHT,
			HOMING_HIT_EXPLOSION_DURATION);
    case HIT_THE_GROUND:
        return new Animation(
			App::imageBank->get(TXT_CANNONBALL_GROUND_EXPLOSION),
			originX,
			terrain->getHeight(originX),
			HOMING_GROUND_EXPLOSION_HEIGHT/2 - HOMING_GROUND_EXPLOSION_DEPTH,
			terrain->getAngle(originX) - PI/2,
			PI/2,
			NULL,
			HOMING_GROUND_EXPLOSION_WIDTH,
			HOMING_GROUND_EXPLOSION_HEIGHT,
			HOMING_GROUND_EXPLOSION_DURATION);
    }
    return NULL;
}

void HomingMissile::compute(){
	if (fired) {
		float _t = getT();
		Timer::compute();
		originX = (*calcX)(_t);
		originY = (*calcY)(_t);
		angle = atan2((*calcY)[_t],(*calcX)[_t]);
		manager->addSmokletsToDraw(
			new Animation(
				App::imageBank->get(TXT_HOMING_SMOKE),
				originX+HOMING_SMOKE_OVERTAKE*cos(angle),
				originY+HOMING_SMOKE_OVERTAKE*sin(angle),
				0,
				0,
				0,
				NULL,
				HOMING_SMOKE_WIDTH,
				HOMING_SMOKE_HEIGHT,
				HOMING_SMOKE_DURATION,
				HOMING_SMOKE_SLOW,
				1,
				new PolyDeg2(manager->getWind()->getWindSpeed()*WIND_INFLUENCE_ON_SMOKE/(2*100* SMOKE_WEIGHT),0,originX+HOMING_SMOKE_OVERTAKE*cos(angle)),
				new PolyDeg2(-G*SMOKE_AIR_RESISTANCE/2,0,originY+HOMING_SMOKE_OVERTAKE*sin(angle))));
	}
	if (!isOutOfCannon()) if (!intersect(owner)) out();
}

}
