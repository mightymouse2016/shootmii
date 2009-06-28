#ifndef AMMO_H_
#define AMMO_H_

#include "../ShootMii.h"

namespace shootmii {

  const float G(-9.81);
  const float TIME_STEP(.1);
  const int AMMO_WEIGHT(1);

  class Ammo : public Cell {
    protected:
      Function* calcX;
      Function* calcY;
      float t;
      bool destroyed;
    public:
      Ammo(Function*, Function*);
      virtual ~Ammo();
      void incT();
      void decT();
      virtual void draw() const=0;
      Function* getCalcX();
      Function* getCalcY();
      void updateXYT();
      bool isBeingDestroyed() const;
      void destruction();
  };

  class CannonBall : public Ammo {
    public:
      CannonBall(Wind* wind = NULL, const float _vInitX = DEFAULT_POWER,
        const float _vInitY = DEFAULT_POWER, const float _xInit = 0,
        const float _yInit = 0);
      void draw() const;
  };

}

#endif /*AMMO_H_*/
