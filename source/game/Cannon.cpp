#include "../ShootMii.h"

namespace shootmii {
  
  Cannon::Cannon(const float _angleOffSet, const float _angleRange, const float _angle, const float _rotationStep)
    : angleOffSet(_angleOffSet), angleRange(_angleRange), angle(_angle), rotationStep(_rotationStep) {}
  
  void Cannon::draw(const int screenX, const int screenY, const int cellSize) const{
    GRRLIB_Line(
        screenX+cellSize/2,
        screenY+cellSize/2,
        screenX+cellSize/2+CANNON_LENGTH*cos(angle*PI/180),
        screenY+cellSize/2-CANNON_LENGTH*sin(angle*PI/180),
        BLACK);
  }
  
  void Cannon::rotateLeft(){
    if (angle + rotationStep < angleOffSet + angleRange) angle += rotationStep;
  }
  
  void Cannon::rotateRight(){
    if (angle - rotationStep > angleOffSet) angle -= rotationStep;
  }
}
