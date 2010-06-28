#include "../ShootMii.h"

namespace shootmii {

PolyDeg2::PolyDeg2(const float _a, const float _b, const float _c) :
	a(_a),
	b(_b),
	c(_c)
{

}

float PolyDeg2::operator()(const float t) const {
	return a*t*t+b*t+c;
}

float PolyDeg2::operator[](const float t) const {
	return 2*a*t+b;
}

void PolyDeg2::setA(float _a) {
	a = _a;
}

void PolyDeg2::setB(float _b) {
	b = _b;
}

void PolyDeg2::setC(float _c) {
	c = _c;
}

}
