#include "../ShootMii.h"

namespace shootmii {

  Ammo::Ammo(Function* _calcX, Function* _calcY) : calcX(_calcX), calcY(_calcY), t(0) {}
  
  Ammo::~Ammo(){}

  void Ammo::incT() {
    t+=.1;
  }
  
  void Ammo::decT(){
    t-=.1;
  }

  CannonBall::CannonBall(const float _vInitX, const float _vInitY,
    const float _xInit, const float _yInit) :
    Ammo(new Affine(_vInitX,_xInit),new PolyDeg2(-G/2,-_vInitY,_yInit)) {
    }

    void CannonBall::draw() const {
      GRRLIB_Rectangle((*calcX)(t), (*calcY)(t), CELL_SIZE, CELL_SIZE, BLACK, true);
    }
    
    Function* Ammo::getCalcX(){
      return calcX;
    }
    
    Function* Ammo::getCalcY(){
      return calcY;
    }
    
    float Ammo::getT() const{
      return t;
    }
    
  }
