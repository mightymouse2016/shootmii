#ifndef CANNONBALL_H_
#define CANNONBALL_H_

#include "../ShootMii.h"

namespace shootmii {

  const int CANNONBALL_GROUND_EXPLOSION_WIDTH(64);
  const int CANNONBALL_GROUND_EXPLOSION_HEIGHT(64);
  const int CANNONBALL_GROUND_EXPLOSION_DEPTH(10);
  const int CANNONBALL_GROUND_EXPLOSION_DURATION(28);

  const int CANNONBALL_AIR_EXPLOSION_WIDTH(48);
  const int CANNONBALL_AIR_EXPLOSION_HEIGHT(48);
  const int CANNONBALL_AIR_EXPLOSION_DEPTH(0);
  const int CANNONBALL_AIR_EXPLOSION_DURATION(12);
  
  const int CANNONBALL_HIT_EXPLOSION_WIDTH(64);
  const int CANNONBALL_HIT_EXPLOSION_HEIGHT(64);
  const int CANNONBALL_HIT_EXPLOSION_DEPTH(0);
  const int CANNONBALL_HIT_EXPLOSION_DURATION(16); 
  
  class CannonBall : public Ammo {

    public:
      CannonBall(
        const float _angle,
        Wind* wind,
        GRRLIB_texImg* _ammoLook,
        Player* _owner,
        const float _vInitX = DEFAULT_POWER,
        const float _vInitY = DEFAULT_POWER,
        const float _xInit = 0,
        const float _yInit = 0);
      void draw() const;
      Explosion* destruction(explosionType _type);
  };

}

#endif /* CANNONBALL_H_ */
