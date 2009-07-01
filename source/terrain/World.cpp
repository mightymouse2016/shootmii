#include "../ShootMii.h"

namespace shootmii {

  World::World() :
	wind(new Wind),
    terrain(new Terrain(N_ROWS,N_COLS)),
    backgroundCloud(GRRLIB_LoadTexture(background_cloud)),
    foregroundCloud(GRRLIB_LoadTexture(foreground_cloud)),
    cloudsBackToDraw(new list<Cloud*>),
    cloudsFrontToDraw(new list<Cloud*>) {
    for(int i=0;i<N_BACKGROUND_CLOUDS;i++)
      cloudsBackToDraw->push_back(new Cloud(wind, &backgroundCloud, BACK_CLOUD_WIDTH, BACK_CLOUD_HEIGHT));
      ////;
    for(int i=0;i<N_FOREGROUND_CLOUDS;i++)
      cloudsFrontToDraw->push_back(new Cloud(wind, &foregroundCloud, FRONT_CLOUD_WIDTH, FRONT_CLOUD_HEIGHT));
      //// (MAX_WIND_SPEED-windSpeed)*FRONT_CLOUD_SPEED_COEF*WIND_INFLUENCE_ON_CLOUDS));
  }

  World::~World() {
    delete terrain;
    cloudsBackToDraw->clear();
    cloudsFrontToDraw->clear();
    delete cloudsBackToDraw;
    delete cloudsFrontToDraw;
  }

  Wind* World::getWind(){
	  return wind;
  }

  Terrain* World::getTerrain(){
    return terrain;
  }

  void World::init(){
	  terrain->generate();
	  wind->init();
	  for(list<Cloud*>::iterator i=cloudsBackToDraw->begin();i!=cloudsBackToDraw->end();i++) (*i)->init();
	  for(list<Cloud*>::iterator i=cloudsFrontToDraw->begin();i!=cloudsFrontToDraw->end();i++) (*i)->init();
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
    // Terrain
    terrain->draw();
  }

  void World::drawForeground() const{
    // Nuages proches
    for (list<Cloud*>::iterator i=cloudsFrontToDraw->begin(); i!=cloudsFrontToDraw->end(); i++) (*i)->draw();
  }

}
