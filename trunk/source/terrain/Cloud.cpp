#include "../ShootMii.h"

namespace shootmii {

  Cloud::Cloud(GRRLIB_texImg* _cloudImg,
      const int _cloudWidth,
      const int _cloudHeight,
      const int _slow) :
  cloudImg(_cloudImg),
  cloudWidth(_cloudWidth),
  cloudHeight(_cloudHeight),
  t(0),
  slow(_slow) {
      randomX();
      randomY();
  }

  void Cloud::updateT(){
    if (t>slow) t=0;
    else t++;
  }
  
  void Cloud::updateX(){
    if (!t)
     if (screenX>SCREEN_WIDTH){
       screenX=-cloudWidth;
       randomY();
     }
     else screenX++;
   }
  
  void Cloud::randomX(){
    screenX = rand()%(cloudWidth + static_cast<int>(SCREEN_WIDTH)) - cloudWidth;
  }
  
  void Cloud::randomY(){
    screenY = rand()%(static_cast<int>(SCREEN_HEIGHT)/4 - cloudHeight);
  }
  
  void Cloud::draw() const{
    GRRLIB_DrawImg(screenX, screenY, *cloudImg, 0, 1, 1, WHITE);
  }
  

}
