#ifndef SINUS_H_
#define SINUS_H_

#include <cmath>
#include "Function.h"

namespace shootmii{

class Sinus: public Function {
protected:
	float a;
	float b;
	float c;
public: // a*sin(b*t)+c
	Sinus(const float _a = 1, const float _b = 1, const float _c = 0);
	float operator()(const float t) const; // La fonction
	float operator[](const float t) const; // La dérivée
	void setA(float _a);
	void setB(float _b);
	void setC(float _c);
};


}

#endif /* SINUS_H_ */
