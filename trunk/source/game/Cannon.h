#ifndef CANNON_H_
#define CANNON_H_

#include "../ShootMii.h"

namespace shootmii {
  
  const float PI(3.14159265);
  
  const float CANNON_LENGTH(20.);
  const float INIT_ANGLE(45.);
  const float ROTATION_STEP(5.);
  const float ROTATION_RANGE(90.);
  const float ANGLE_OFFSET(90.);
  
  class Cannon{
    private:
      float angleOffSet;
      float angleRange;
      float angle;
      float rotationStep;
    public:
      Cannon(const float _angleOffSet, const float _angleRange, const float _angle, const float _rotationStep);
      void draw(const int screenX, const int screenY, const int cellSize) const;
      void rotateLeft();
      void rotateRight();
  };
  
}

#endif /*CANNON_H_*/
