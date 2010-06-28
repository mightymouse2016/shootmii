#include "Coordinates.h"

namespace shootmii {

Coordinates::Coordinates(const float _x, const float _y) :
	x(_x),
	y(_y)
{

}

float Coordinates::getX() const{
	return x;
}

float Coordinates::getY() const{
	return y;
}

float Coordinates::getAngle() const{
	return atan2(y,x);
}

float Coordinates::getRadial() const{
	return sqrt(x*x+y*y);
}

void Coordinates::setX(const float _x){
	x = _x;
}

void Coordinates::setY(const float _y){
	y = _y;
}

void Coordinates::setCoordinates(const float _x,const float _y){
	x = _x;
	y = _y;
}

void Coordinates::grow(const float k){
	growX(k);
	growY(k);
}
void Coordinates::growX(const float k){
	x*=k;
}

void Coordinates::growY(const float k){
	y*=k;
}

}
