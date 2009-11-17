#include "../ShootMii.h"

namespace shootmii {

Rectangle::Rectangle(
		const LayerPriority _layer,
		const float _width,
		const float _height,
		const float _originX,
		const float _originY,
		const float _radial,
		const float _angle,
		const float _polygonAngle,
		const bool _spinFather,
		const bool _spinPolygon,
		GRRLIB_texImg* _image,
		Polygon* _father,
		const int _spriteIndex,
		const int _spriteWidth,
		const int _spriteHeight,
		const bool _hidden,
		const bool _debugHidden) :
	Polygon(_layer,_originX,_originY,_radial,_angle,_polygonAngle,_spinFather,_spinPolygon,_father,Coordinates(-_width/2,-_height/2),_image,_spriteIndex,_spriteWidth,_spriteHeight,_hidden,_debugHidden)
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

void Rectangle::setWidthHeight(const float _width, const float _height){
	vertices[0] = Coordinates(-_width/2,-_height/2);
	vertices[1] = Coordinates(_width/2,-_height/2);
	vertices[2] = Coordinates(_width/2,_height/2);
	vertices[3] = Coordinates(-_width/2,_height/2);
}

}
