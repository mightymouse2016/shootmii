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
      cloudsBackToDraw->push_back(new Cloud(windDirection, &backgroundCloud, BACK_CLOUD_WIDTH, BACK_CLOUD_HEIGHT,
    				  (MAX_WIND_SPEED-windSpeed)*BACK_CLOUD_SPEED_COEF/WIND_INFLUENCE_ON_CLOUDS));
    for(int i=0;i<N_FOREGROUND_CLOUDS;i++)
      cloudsFrontToDraw->push_back(new Cloud(windDirection, &foregroundCloud, FRONT_CLOUD_WIDTH, FRONT_CLOUD_HEIGHT,
    				  (MAX_WIND_SPEED-windSpeed)*FRONT_CLOUD_SPEED_COEF/WIND_INFLUENCE_ON_CLOUDS));
    // rand()%2 ne fonctionnerais pas, on tomberais toujours sur des nombres impairs ...
    if (rand()%1000 < 500) windDirection = false;
    else windDirection = true;
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

  void World::init(){
	  terrain->generate();
	  windSpeed = rand()%MAX_WIND_SPEED;
	  if (rand()%1000 < 500) windDirection = false;
	  else windDirection = true;
	  for(list<Cloud*>::iterator i=cloudsBackToDraw->begin();i!=cloudsBackToDraw->end();i++)
		  (*i)->init(windDirection,(MAX_WIND_SPEED-windSpeed)*BACK_CLOUD_SPEED_COEF/WIND_INFLUENCE_ON_CLOUDS);
	  for(list<Cloud*>::iterator i=cloudsFrontToDraw->begin();i!=cloudsFrontToDraw->end();i++)
	  		  (*i)->init(windDirection,(MAX_WIND_SPEED-windSpeed)*FRONT_CLOUD_SPEED_COEF/WIND_INFLUENCE_ON_CLOUDS);
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
