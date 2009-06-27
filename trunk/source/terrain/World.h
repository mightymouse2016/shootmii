#ifndef WORLD_H_
#define WORLD_H_

#include "../ShootMii.h"

const int N_BACKGROUND_CLOUDS(6);
const int N_FOREGROUND_CLOUDS(10);

namespace shootmii {

  class World {
    private:
      Terrain* terrain;
      int windSpeed;
      GRRLIB_texImg backgroundCloud;
      GRRLIB_texImg foregroundCloud;
      list<Cloud*>* cloudsBackToDraw;
      list<Cloud*>* cloudsFrontToDraw;
    public:
      World();
      virtual ~World();
      Terrain* getTerrain();
      void compute();
      void computeClouds();
      void drawBackground() const;
      void drawForeground() const;
  };

}

#endif /*WORLD_H_*/
