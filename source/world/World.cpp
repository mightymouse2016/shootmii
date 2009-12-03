#include "../ShootMii.h"

namespace shootmii {

World::World() :
	Polygon(SKY_LAYER),
	wind(new Wind),
	terrain(new Terrain(N_ROWS, N_COLS, TERRAIN_CELL_WIDTH, TERRAIN_CELL_HEIGHT)),
	sun(new Sun),
	clouds(new list<Cloud*>)
{
	vertices.reserve(4);
	vertices.push_back(Coordinates(1,1));
	vertices.push_back(Coordinates(TERRAIN_CELL_WIDTH*N_COLS-1,1));
	vertices.push_back(Coordinates(TERRAIN_CELL_WIDTH*N_COLS-1,TERRAIN_CELL_HEIGHT*N_ROWS-1));
	vertices.push_back(Coordinates(1,TERRAIN_CELL_HEIGHT*N_ROWS-1));

	for (int i = 0; i < N_BACKGROUND_CLOUDS; i++) {
		clouds->push_back(
			new Cloud(
				BACK_CLOUD_LAYER,
				wind,
				App::imageBank->get(TXT_BG_CLOUD),
				BACK_CLOUD_WIDTH,
				BACK_CLOUD_HEIGHT));
	}
	for (int i = 0; i < N_FOREGROUND_CLOUDS; i++) {
		clouds->push_back(
			new Cloud(
				FRONT_CLOUD_LAYER,
				wind,
				App::imageBank->get(TXT_FG_CLOUD),
				FRONT_CLOUD_WIDTH,
				FRONT_CLOUD_HEIGHT));
	}
}

World::~World() {
	clouds->clear();
	delete clouds;
	delete terrain;
}

Wind* World::getWind() {
	return wind;
}

Terrain* World::getTerrain() {
	return terrain;
}

void World::init() {
	terrain->generate();
	wind->init();
	sun->init();
	for (list<Cloud*>::iterator i=clouds->begin();i!=clouds->end();i++) (*i)->init();
}

void World::compute() {
	computeClouds();
	sun->compute();
}

void World::computeClouds() {
	for (list<Cloud*>::iterator i=clouds->begin();i!=clouds->end();i++) {
		(*i)->compute();
	}
}

void World::addToDrawManager(){
	Polygon::addToDrawManager();
	sun->addToDrawManager();
	terrain->addToDrawManager();
	for (list<Cloud*>::iterator i=clouds->begin();i!=clouds->end();i++) (*i)->addToDrawManager();
}

void World::draw(){
	// Ciel
	float ratio = (1-SUN_LIGHT_INFLUENCE) - sin(sun->getAbsoluteAngle())*SUN_LIGHT_INFLUENCE;
	u32 colorSky1 = applyRatioToRGBA(BLUE_SKY_1,ratio,0,0,0,1);
	u32 colorSky2 = applyRatioToRGBA(BLUE_SKY_2,ratio,0,0,0,1);
	u32 colors[] = {colorSky1, colorSky1, colorSky2, colorSky2};
	drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, colors);
	Polygon::draw();
}

}
