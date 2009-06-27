#ifndef CLOUD_H_
#define CLOUD_H_

#include "../ShootMii.h"

const int MAX_WIND_SPEED(100);
const int WIND_COEF(10);

const int FRONT_CLOUD_SPEED_COEF(4);
const int FRONT_CLOUD_HEIGHT(64);
const int FRONT_CLOUD_WIDTH(64);

const int BACK_CLOUD_SPEED_COEF(1);
const int BACK_CLOUD_HEIGHT(48);
const int BACK_CLOUD_WIDTH(64);

namespace shootmii {

  class Cloud {
    private:
      GRRLIB_texImg* cloudImg;
      int cloudWidth;
      int cloudHeight;
      int t;
      int slow;
      int screenX;
      int screenY;
    public:
      Cloud(GRRLIB_texImg* _cloudImg, const int _cloudWidth, const int _cloudHeight, const int _slow);
      void updateT();
      void updateX();
      void randomX();
      void randomY();
      void draw() const;
  };
  
}

#endif /*CLOUD_H_*/
