#ifndef CLOUD_H_
#define CLOUD_H_

#include "../ShootMii.h"

const int MAX_WIND_SPEED(100);
const int WIND_INFLUENCE_ON_CLOUDS(50); // 0->100
	//0 means that clouds will remain static
	//100 means that clouds will move from 1px every CLOUD_SPEED_COEF frame

const int FRONT_CLOUD_SPEED_COEF(4);
const int FRONT_CLOUD_HEIGHT(64);
const int FRONT_CLOUD_WIDTH(64);

const int BACK_CLOUD_SPEED_COEF(1);
const int BACK_CLOUD_HEIGHT(48);
const int BACK_CLOUD_WIDTH(64);

namespace shootmii {

  class Cloud {
    private:
      bool windDirection;
      GRRLIB_texImg* cloudImg;
      int cloudWidth;
      int cloudHeight;
      int t;
      int slow;
      int screenX;
      int screenY;
    public:
      Cloud(bool _windDirection, GRRLIB_texImg* _cloudImg, const int _cloudWidth, const int _cloudHeight, const int _slow);
      void updateT();
      void updateX();
      void randomX();
      void randomY();
      void init(int _windDirection, int _slow);
      void draw() const;
  };

}

#endif /*CLOUD_H_*/
