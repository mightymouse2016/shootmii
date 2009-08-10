#include "../ShootMii.h"

namespace shootmii {

World::World() :
	wind(new Wind),
	terrain(new Terrain(N_ROWS, N_COLS, TERRAIN_CELL_WIDTH, TERRAIN_CELL_HEIGHT)),
	sun(new Sun),
	cloudsBackToDraw(new list<Cloud*>),
	cloudsFrontToDraw(new list<Cloud*>)
{
	backgroundCloud = App::imageBank->get(TXT_BG_CLOUD);
	foregroundCloud = App::imageBank->get(TXT_FG_CLOUD);
	for (int i = 0; i < N_BACKGROUND_CLOUDS; i++)
		cloudsBackToDraw->push_back(new Cloud(BACK_CLOUD_LAYER, wind, backgroundCloud,BACK_CLOUD_WIDTH, BACK_CLOUD_HEIGHT));
	for (int i = 0; i < N_FOREGROUND_CLOUDS; i++)
		cloudsFrontToDraw->push_back(new Cloud(FRONT_CLOUDS_LAYER, wind, foregroundCloud,FRONT_CLOUD_WIDTH, FRONT_CLOUD_HEIGHT));
}

World::~World() {
	delete terrain;
	cloudsBackToDraw->clear();
	cloudsFrontToDraw->clear();
	delete cloudsBackToDraw;
	delete cloudsFrontToDraw;
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
	for (list<Cloud*>::iterator i=cloudsBackToDraw->begin();i!=cloudsBackToDraw->end();i++) (*i)->init();
	for (list<Cloud*>::iterator i=cloudsFrontToDraw->begin();i!=cloudsFrontToDraw->end();i++) (*i)->init();
}

void World::compute() {
	computeClouds();
	sun->compute();
}

void World::computeClouds() {
	for (list<Cloud*>::iterator i=cloudsBackToDraw->begin();i!=cloudsBackToDraw->end();i++) {
		(*i)->updateT();
		(*i)->updateX();
	}
	for (list<Cloud*>::iterator i=cloudsFrontToDraw->begin();i!=cloudsFrontToDraw->end();i++) {
		(*i)->updateT();
		(*i)->updateX();
	}
}

void World::drawBackground() const {
	// Ciel
	float ratio = (1-SUN_LIGHT_INFLUENCE) - sin(sun->getAngle())*SUN_LIGHT_INFLUENCE;
	u8 r = (BLUE_SKY_1 & 0xFF000000) >> 24;
	u8 g = (BLUE_SKY_1 & 0x00FF0000) >> 16;
	u8 b = (BLUE_SKY_1 & 0x0000FF00) >> 8;
	u32 colorSky1 = (static_cast<u32>(r*ratio)<<24) | (static_cast<u32>(g*ratio)<<16) | (static_cast<u32>(b*ratio)<<8) | 0xFF;

	r = (BLUE_SKY_2 & 0xFF000000) >> 24;
	g = (BLUE_SKY_2 & 0x00FF0000) >> 16;
	b = (BLUE_SKY_2 & 0x0000FF00) >> 8;
	u32 colorSky2 = (static_cast<u32>(r*ratio)<<24) | (static_cast<u32>(g*ratio)<<16) | (static_cast<u32>(b*ratio)<<8) | 0xFF;

	if (App::console->isDebug()) {
		colorSky1 = colorSky2 = WHITE;
	}

	u32 colors[] = { colorSky1, colorSky1, colorSky2, colorSky2 };
	drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, colors);
	// Soleil
	sun->draw();
	// Nuages lointains
	for (list<Cloud*>::iterator i=cloudsBackToDraw->begin();i!=cloudsBackToDraw->end();i++) (*i)->draw();
}

void World::drawMiddleground() const{
	// Terrain
	terrain->draw();
}

void World::drawForeground() const {
	// Nuages proches
	for (list<Cloud*>::iterator i=cloudsFrontToDraw->begin();i!=cloudsFrontToDraw->end();i++)
		(*i)->draw();
}

}
