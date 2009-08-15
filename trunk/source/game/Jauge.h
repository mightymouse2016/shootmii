#ifndef JAUGE_H_
#define JAUGE_H_

#include "../ShootMii.h"

namespace shootmii{

const int STRENGTH_JAUGE_WIDTH(68);
const int STRENGTH_JAUGE_HEIGHT(8);
const int STRENGTH_JAUGE_X(218);
const int STRENGTH_JAUGE_Y(-19);

const int HEAT_JAUGE_WIDTH(68);
const int HEAT_JAUGE_HEIGHT(8);
const int HEAT_JAUGE_X(218);
const int HEAT_JAUGE_Y(-6);

const int LIFE_JAUGE_WIDTH(68);
const int LIFE_JAUGE_HEIGHT(8);
const int LIFE_JAUGE_X(218);
const int LIFE_JAUGE_Y(7);

const int FURY_JAUGE_WIDTH(200);
const int FURY_JAUGE_HEIGHT(24);
const int FURY_JAUGE_X(213);
const int FURY_JAUGE_Y(15);

const int WIND_JAUGE_WIDTH(80);
const int WIND_JAUGE_HEIGHT(8);
const int WIND_JAUGE_X(42);
const int WIND_JAUGE_Y(-23);

class Jauge : public Rectangle{
private:
	float* percentage; // Un pointeur vers la valeur (sur 100)
public:
	Jauge(
		const LayerPriority layer,
		float* percentage,
		const float width,
		const float height,
		const float originX,
		const float originY,
		GRRLIB_texImg* image,
		const float angle = 0,
		Polygon* father = NULL);
	// Surcharge pour g�rer l'affichage variable de la jauge
	void compute();
};

}

#endif /* JAUGE_H_ */