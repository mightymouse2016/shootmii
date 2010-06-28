#include "../ShootMii.h"

namespace shootmii {

Affine::Affine(const float _a, const float _b) :
	a(_a),
	b(_b)
{

}

float Affine::operator()(const float t) const {
	return a*t+b;
}

float Affine::operator[](const float t) const {
	return a;
}

void Affine::setA(float _a) {
	a = _a;
}

void Affine::setB(float _b) {
	b = _b;
}

}
