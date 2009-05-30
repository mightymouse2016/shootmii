#ifndef CANNON_H_
#define CANNON_H_

#include "../ShootMii.h"

namespace shootmii {
  
  class Cannon{
    private:
      float angle;
      float rotationStep;
    public:
      Cannon(const float _angle = 45., const float _rotationStep = 45./60); // 45 degrés par secondes
      void draw() const;
      void rotateleft();
      void rotateright();
  };
  
}

#endif /*CANNON_H_*/
