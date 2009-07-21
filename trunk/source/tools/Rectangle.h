#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "../ShootMii.h"

namespace shootmii{

class Rectangle : public Polygon{
public:
	Rectangle(
		const float width,
		const float height,
		const float originX,
		const float originY,
		const float radial = 0,
		const float angle = 0,
		const float polygonAngle = 0,
		const float spin = 1,
		GRRLIB_texImg* image = NULL,
		Polygon* father = NULL,
		const int spriteIndex = 0,
		const int spriteWidth = 0,
		const int spriteHeight = 0,
		const bool hidden = false);
	float getWidth() const;
	float getHeight() const;
};

}

#endif /* RECTANGLE_H_ */
