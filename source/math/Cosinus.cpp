#include "Cosinus.h"

namespace shootmii {

Cosinus::Cosinus(const float _a, const float _b, const float _c) :
	a(_a),
	b(_b),
	c(_c)
{
	// NOTHING TO DO
}

float Cosinus::operator()(const float t) const {
	return a*cos(b*t)+c;
}

float Cosinus::operator[](const float t) const {
	return a*b*sin(b*t);
}

void Cosinus::setA(float _a) {
	a = _a;
}

void Cosinus::setB(float _b) {
	b = _b;
}

void Cosinus::setC(float _c) {
	c = _c;
}

}
