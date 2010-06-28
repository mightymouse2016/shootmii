#include "Sinus.h"

namespace shootmii {

Sinus::Sinus(const float _a, const float _b, const float _c) :
	a(_a),
	b(_b),
	c(_c)
{
	// NOTHING TO DO
}

float Sinus::operator()(const float t) const {
	return a*sin(b*t)+c;
}

float Sinus::operator[](const float t) const {
	return -a*b*cos(b*t);
}

void Sinus::setA(float _a) {
	a = _a;
}

void Sinus::setB(float _b) {
	b = _b;
}

void Sinus::setC(float _c) {
	c = _c;
}


}
