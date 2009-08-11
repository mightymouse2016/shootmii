#ifndef JAUGE_H_
#define JAUGE_H_

#include "../ShootMii.h"

namespace shootmii{

/* TODO
const int FURY_JAUGE_WIDTH(68);
const int FURY_JAUGE_HEIGHT(8);
const int WIND_JAUGE_WIDTH(68);
const int WIND_JAUGE_HEIGHT(8);
*/

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
	// Surcharge pour gérer l'affichage variable de la jauge
	void compute();
};

}

#endif /* JAUGE_H_ */
