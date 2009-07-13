#include "../ShootMii.h"

namespace shootmii {

Coordinates::Coordinates(const float _x, const float _y) :
	x(_x),
	y(_y)
{

}

int Coordinates::getX() const{
	return x;
}

int Coordinates::getY() const{
	return y;
}

void Coordinates::setX(const int _x){
	x = _x;
}

void Coordinates::setY(const int _y){
	y = _y;
}

}
