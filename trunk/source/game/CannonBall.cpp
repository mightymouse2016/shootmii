#include "../world/Wind.h"
#include "../world/Terrain.h"
#include "../tools/Animation.h"
#include "../tools/SoundBank.h"
#include "../tools/ImageBank.h"
#include "../math/PolyDeg2.h"
#include "../App.h"
#include "CannonBall.h"
#include "Player.h"

namespace shootmii {

CannonBall::CannonBall(
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
    		_manager)
{
    vertices.reserve(5);
    vertices.push_back(Coordinates( 8, 0));
    vertices.push_back(Coordinates( 2,-7));
    vertices.push_back(Coordinates(-8,-7));
    vertices.push_back(Coordinates(-8, 7));
    vertices.push_back(Coordinates( 2, 7));
}

void CannonBall::computePosition(){
	float _t = getT();
	originX = (*calcX)(_t);
	originY = (*calcY)(_t);
	angle = atan2((*calcY)[_t],(*calcX)[_t]);
}

Animation* CannonBall::destruction(explosionType _type, Player* _playerHit) {
	App::soundBank->play(AMMO_BOOM);
    switch (_type){
    case HIT_A_SHIELD:
    case HIT_ANOTHER_AMMO:
        return new Animation(
        	EXPLOSION_LAYER,
			App::imageBank->get(TXT_CANNONBALL_AIR_EXPLOSION),
			originX,
			originY,
			0,
			0,
			0,
			NULL,
			CANNONBALL_AIR_EXPLOSION_WIDTH,
			CANNONBALL_AIR_EXPLOSION_HEIGHT,
			CANNONBALL_AIR_EXPLOSION_DURATION);
    case HIT_A_PLAYER:
        return new Animation(
            EXPLOSION_LAYER,
			App::imageBank->get(TXT_CANNONBALL_HIT_EXPLOSION),
			0,
			0,
			0,
			0,
			0,
			_playerHit,
			CANNONBALL_HIT_EXPLOSION_WIDTH,
			CANNONBALL_HIT_EXPLOSION_HEIGHT,
			CANNONBALL_HIT_EXPLOSION_DURATION);
    case HIT_THE_GROUND:
        return new Animation(
            EXPLOSION_LAYER,
			App::imageBank->get(TXT_CANNONBALL_GROUND_EXPLOSION),
			originX,
			terrain->getHeight(originX),
			CANNONBALL_GROUND_EXPLOSION_HEIGHT/2 - CANNONBALL_GROUND_EXPLOSION_DEPTH,
			terrain->getAngle(originX) - PI/2,
			PI/2,
			NULL,
			CANNONBALL_GROUND_EXPLOSION_WIDTH,
			CANNONBALL_GROUND_EXPLOSION_HEIGHT,
			CANNONBALL_GROUND_EXPLOSION_DURATION);
    }
    return NULL;
}

}
