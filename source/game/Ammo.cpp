#include "../ShootMii.h"

namespace shootmii {

  Ammo::Ammo(Function* _calcX, Function* _calcY) :
    calcX(_calcX), calcY(_calcY), t(0), destroyed(false) {
  }

  Ammo::~Ammo() {
  }

  void Ammo::incT() {
    t += TIME_STEP;
  }

  void Ammo::decT() {
    t -= TIME_STEP;
  }

  CannonBall::CannonBall(Wind* wind, const float _vInitX, const float _vInitY,
    const float _xInit, const float _yInit) :
    Ammo(new PolyDeg2(wind->getWindSpeed()*(wind->getWindDirection()*2 - 1)*WIND_INFLUENCE_ON_AMMO/(2*100*AMMO_WEIGHT),_vInitX,_xInit),
    		new PolyDeg2(-G/(2*AMMO_WEIGHT),-_vInitY,_yInit)) {
  }

  void CannonBall::draw() const {
    GRRLIB_Rectangle(screenX, screenY, CELL_SIZE, CELL_SIZE, BLACK, true);
  }

  Function* Ammo::getCalcX() {
    return calcX;
  }

  Function* Ammo::getCalcY() {
    return calcY;
  }

  void Ammo::updateXYT() {
    screenX = (*calcX)(t);
    screenY = (*calcY)(t);
    incT();
  }
  bool Ammo::isBeingDestroyed() const{
    return destroyed;
  }

  void Ammo::destruction(){
    destroyed = true;
  }
}
