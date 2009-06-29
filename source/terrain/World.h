#ifndef WORLD_H_
#define WORLD_H_

#include "../ShootMii.h"

const int MAX_WIND_SPEED(100);

const int N_ROWS(26);
const int N_COLS(40);

const int N_BACKGROUND_CLOUDS(6);
const int N_FOREGROUND_CLOUDS(10);

namespace shootmii {

class World {
private:
	Wind* wind;
	Terrain* terrain;
	GRRLIB_texImg backgroundCloud;
	GRRLIB_texImg foregroundCloud;
	list<Cloud*>* cloudsBackToDraw;
	list<Cloud*>* cloudsFrontToDraw;
public:
	World();
	virtual ~World();
	Terrain* getTerrain();
	Wind* getWind();
	void init();
	void compute();
	void computeClouds();
	void drawBackground() const;
	void drawForeground() const;
};

}

#endif /*WORLD_H_*/
