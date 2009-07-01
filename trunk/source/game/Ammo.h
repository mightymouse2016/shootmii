#ifndef AMMO_H_
#define AMMO_H_

#include "../ShootMii.h"

namespace shootmii {

  const float G(-9.81);
  const float TIME_STEP(.1);
  const int AMMO_WEIGHT(1);
  const int AMMO_WIDTH(16);
  const int AMMO_HEIGHT(16);
  const int AMMO_OVERTAKE(5); // dépassement de la munition du canon

  class Ammo : public Cell {
    protected:
      Function* calcX;
      Function* calcY;
      float t;
      float angle;
      bool destroyed;
      bool outOfCannon; // pour que le gestionnaire de collision ignore le contact
      GRRLIB_texImg* ammoLook;
      Player* owner;
    public:
      Ammo(const float _angle, GRRLIB_texImg* _ammoLook, Function*, Function*, Player* _owner);
      virtual ~Ammo();
      void incT();
      void decT();
      virtual void draw() const=0;
      Function* getCalcX();
      Function* getCalcY();
      int getCol() const;
      int getRow() const;
      void compute();
      void setAngle(const float _angle);
      bool isBeingDestroyed() const;
      bool isOutOfCannon() const;
      void out();
      void destruction();
  };

  class CannonBall : public Ammo {
    public:
      CannonBall(const float _angle, Wind* wind, GRRLIB_texImg* _ammoLook, Player* _owner, const float _vInitX = DEFAULT_POWER,
        const float _vInitY = DEFAULT_POWER, const float _xInit = 0,
        const float _yInit = 0);
      void draw() const;
  };

}

#endif /*AMMO_H_*/
