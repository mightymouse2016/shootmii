#ifndef WORLD_H_
#define WORLD_H_

#include "../ShootMii.h"

namespace shootmii {

const int MAX_WIND_SPEED(100);
const int SCORE_PANEL_HEIGHT(64);
const int TERRAIN_CELL_HEIGHT(16);
const int TERRAIN_CELL_WIDTH(16);
const int N_ROWS((SCREEN_HEIGHT-SCORE_PANEL_HEIGHT)/TERRAIN_CELL_HEIGHT);
const int N_COLS(SCREEN_WIDTH/TERRAIN_CELL_WIDTH);
const int N_BACKGROUND_CLOUDS(6);
const int N_FOREGROUND_CLOUDS(10);

class World : public Polygon{
private:
	Wind* wind;
	Terrain* terrain;
	Sun* sun;
	list<Cloud*>* clouds;
public:
	World();
	virtual ~World();
	Terrain* getTerrain();
	Wind* getWind();
	void init();
	void compute();
	void computeClouds();
	void addToDrawManager();
	void draw();
};

}

#endif /*WORLD_H_*/
