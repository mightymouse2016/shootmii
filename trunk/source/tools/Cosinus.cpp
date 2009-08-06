#include "../ShootMii.h"

namespace shootmii {

Cosinus::Cosinus(const float _a, const float _b, const float _c) :
	Function(_a, _b, _c)
{
	// NOTHING TO DO
}

float Cosinus::operator()(const float t) const {
	return a*cos(b*t)+c;
}

float Cosinus::operator[](const float t) const {
	return a*b*sin(b*t);
}

}
