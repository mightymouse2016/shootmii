#include "../ShootMii.h"

namespace shootmii {

  Cannon::Cannon(const float _angleOffSet, const float _angleRange, const float _angle, const float _rotationStep)
  : angleOffSet(_angleOffSet), angleRange(_angleRange), angle(_angle), rotationStep(_rotationStep),
    loadedAmmo(new CannonBall) {}
  
  Cannon::~Cannon(){
    delete loadedAmmo;
  }

  void Cannon::draw(const int screenX, const int screenY, const int cellSize) const {
    float topCos = cos(angle*PI/180);
    float topSin = sin(angle*PI/180);
    float topX = CANNON_LENGTH*topCos;
    float topY = CANNON_LENGTH*topSin;
    
    GRRLIB_Line(
    screenX+cellSize/2,
    screenY+cellSize/2,
    screenX+cellSize/2+topX,
    screenY+cellSize/2-topY,
    BLACK);
    loadedAmmo->getCalcX()->setB(screenX+topX); // X
    loadedAmmo->getCalcY()->setC(screenY-topY); // Y
    loadedAmmo->getCalcX()->setA(DEFAULT_POWER*topCos); // X
    loadedAmmo->getCalcY()->setB(-DEFAULT_POWER*topSin); // Y
    loadedAmmo->draw();
  }

  void Cannon::rotateLeft() {
    if (angle + rotationStep < angleOffSet + angleRange) angle += rotationStep;
  }

  void Cannon::rotateRight() {
    if (angle - rotationStep> angleOffSet) angle -= rotationStep;
  }
  
  void Cannon::shoot(Manager* manager) {
    manager->addAmmoToMove(loadedAmmo);
    loadedAmmo = new CannonBall;
  }
}
