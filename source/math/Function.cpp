#include "../ShootMii.h"

namespace shootmii {

Function::Function(const float _a, const float _b, const float _c) :
	a(_a),
	b(_b),
	c(_c)
{

}

void Function::setA(float _a) {
	a = _a;
}

void Function::setB(float _b) {
	b = _b;
}

void Function::setC(float _c) {
	c = _c;
}

}
