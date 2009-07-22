#include "../ShootMii.h"

namespace shootmii{

Sun::Sun() :
  Rectangle(
      SUN_WIDTH,
      SUN_HEIGHT,
      SCREEN_WIDTH/2,
      (CENTER_TERRAIN+AMPLITUDE_TERRAIN+SUN_HEIGHT/2)*N_ROWS*TERRAIN_CELL_WIDTH/100,
      (SCREEN_WIDTH - SUN_WIDTH)/2,
      -PI/2,
      0,
      0,
      App::imageBank->get(TXT_SUN))
{

}

void Sun::compute(){
  if (angle >= 0) angle = -PI;
  else angle += SUN_SLOW;
}

void Sun::init(){
	angle = - static_cast<float>(rand()%180)*PI/180;
}

}
