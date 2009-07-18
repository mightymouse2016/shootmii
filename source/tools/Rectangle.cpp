#include "../ShootMii.h"

namespace shootmii {

Rectangle::Rectangle(
	const float _width,
	const float _height,
	const float _originX,
	const float _originY,
	const float _radial,
	const float _angle,
	const float _polygonAngle,
	const float _spin,
	GRRLIB_texImg* _image,
	Polygon* _father) :
		Polygon(_originX,_originY,_radial,_angle,_polygonAngle,_spin,_father,Coordinates(-_width/2,-_height/2),_image)
{
	vertices.reserve(4);
	vertices.push_back(Coordinates(-_width/2,-_height/2));
	vertices.push_back(Coordinates(_width/2,-_height/2));
	vertices.push_back(Coordinates(_width/2,_height/2));
	vertices.push_back(Coordinates(-_width/2,_height/2));
}

float Rectangle::getWidth() const{
	return vertices[UP_RIGHT].getX() - vertices[UP_LEFT].getX();
}

float Rectangle::getHeight() const{
	return vertices[DOWN_LEFT].getY() - vertices[UP_LEFT].getY();
}

}
