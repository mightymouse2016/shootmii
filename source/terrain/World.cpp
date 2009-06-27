#include "../ShootMii.h"

namespace shootmii {

  World::World() :
    terrain(new Terrain(CELL_SIZE,N_ROWS,N_COLS)),
    windSpeed(rand()%MAX_WIND_SPEED),
    backgroundCloud(GRRLIB_LoadTexture(background_cloud)),
    foregroundCloud(GRRLIB_LoadTexture(foreground_cloud)),
    cloudsBackToDraw(new list<Cloud*>),
    cloudsFrontToDraw(new list<Cloud*>) {
    for(int i=0;i<N_BACKGROUND_CLOUDS;i++)
      cloudsBackToDraw->push_back(new Cloud(&backgroundCloud, BACK_CLOUD_WIDTH, BACK_CLOUD_HEIGHT, (MAX_WIND_SPEED-windSpeed)*BACK_CLOUD_SPEED_COEF/WIND_COEF));
    for(int i=0;i<N_FOREGROUND_CLOUDS;i++)
      cloudsFrontToDraw->push_back(new Cloud(&foregroundCloud, FRONT_CLOUD_WIDTH, FRONT_CLOUD_HEIGHT, (MAX_WIND_SPEED-windSpeed)*FRONT_CLOUD_SPEED_COEF/WIND_COEF));
  }

  World::~World() {
    delete terrain;
    cloudsBackToDraw->clear();
    cloudsFrontToDraw->clear();
    delete cloudsBackToDraw;
    delete cloudsFrontToDraw;
  }
  
  Terrain* World::getTerrain(){
    return terrain;
  }
  
  void World::compute(){
    computeClouds();
  }
  
  void World::computeClouds() {
    for (list<Cloud*>::iterator i=cloudsBackToDraw->begin(); i!=cloudsBackToDraw->end(); i++) {
      (*i)->updateT();
      (*i)->updateX();
    }
    for (list<Cloud*>::iterator i=cloudsFrontToDraw->begin(); i!=cloudsFrontToDraw->end(); i++) {
      (*i)->updateT();
      (*i)->updateX();
    }
  }
  
  void World::drawBackground() const{
    // Ciel
    u32 colors[] = {BLUE_SKY_1,BLUE_SKY_1,BLUE_SKY_2,BLUE_SKY_2};
    drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, colors);
    // Nuages lointains
    for (list<Cloud*>::iterator i=cloudsBackToDraw->begin(); i!=cloudsBackToDraw->end(); i++) (*i)->draw();
    terrain->draw();
  }

  void World::drawForeground() const{
    // Nuages proches
    for (list<Cloud*>::iterator i=cloudsFrontToDraw->begin(); i!=cloudsFrontToDraw->end(); i++) (*i)->draw();
  }

}
