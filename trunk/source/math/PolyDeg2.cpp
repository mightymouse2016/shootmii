#include "../ShootMii.h"

namespace shootmii {

PolyDeg2::PolyDeg2(const float _a, const float _b, const float _c) :
	Function(_a, _b, _c)
{

}

float PolyDeg2::operator()(const float t) const {
	return a*t*t+b*t+c;
}

float PolyDeg2::operator[](const float t) const {
	return 2*a*t+b;
}

}
