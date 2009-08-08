#include "../ShootMii.h"

namespace shootmii {

Sinus::Sinus(const float _a, const float _b, const float _c) :
	Function(_a, _b, _c)
{
	// NOTHING TO DO
}

float Sinus::operator()(const float t) const {
	return a*sin(b*t)+c;
}

float Sinus::operator[](const float t) const {
	return -a*b*cos(b*t);
}

}
