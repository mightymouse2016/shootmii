#ifndef AMMO_H_
#define AMMO_H_

#include "../ShootMii.h"

namespace shootmii {
  
  const float G(-9.81);
  
  class Ammo{
    protected:
      Function* calcX;
      Function* calcY;
      float t;
    public:
      Ammo(Function*,Function*);
      virtual ~Ammo();
      void incT();
      void decT();
      virtual void draw() const=0;
      Function* getCalcX();
      Function* getCalcY();
      float getT() const;
  };
  
  class CannonBall : public Ammo{
    public:
      CannonBall(const float _vInitX = DEFAULT_POWER,const float _vInitY = DEFAULT_POWER,const float _xInit = 0,const float _yInit = 0);
      void draw() const;
  };
  
}

#endif /*AMMO_H_*/
