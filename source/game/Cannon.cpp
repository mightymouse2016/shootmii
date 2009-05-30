#include "../ShootMii.h"

namespace shootmii {
  
  Cannon::Cannon(const float _angle, const float _rotationStep) : angle(_angle), rotationStep(_rotationStep) {}
  
  void Cannon::draw() const{
    // TODO
  }
  
  void Cannon::rotateleft(){
    angle += rotationStep;
  }
  
  void Cannon::rotateright(){
    angle -= rotationStep;
  }
}
