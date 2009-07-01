#ifndef WORLD_H_
#define WORLD_H_

#include "../ShootMii.h"

namespace shootmii {

const int MAX_WIND_SPEED(100);

const int SCORE_PANEL_HEIGHT(64);

const int TERRAIN_CELL_HEIGHT(4);
const int TERRAIN_CELL_WIDTH(8);

const int N_ROWS((SCREEN_HEIGHT-SCORE_PANEL_HEIGHT)/TERRAIN_CELL_HEIGHT);
const int N_COLS(SCREEN_WIDTH/TERRAIN_CELL_WIDTH);

const int N_BACKGROUND_CLOUDS(6);
const int N_FOREGROUND_CLOUDS(10);

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
