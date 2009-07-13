#include "../ShootMii.h"

namespace shootmii {

Affine::Affine(const float _a, const float _b) :
	Function(_a,_b,0) {
}

float Affine::operator()(const float t) const {
	return a*t+b;
}

float Affine::operator[](const float t) const {
	return a;
}

}
