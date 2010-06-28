#ifndef POLYDEG2_H_
#define POLYDEG2_H_

#include "Function.h"

namespace shootmii {

class PolyDeg2: public Function {
protected:
	float a;
	float b;
	float c;
public:
	PolyDeg2(const float _a = 0, const float _b = 0, const float _c = 0);
	float operator()(const float t) const; // La fonction
	float operator[](const float t) const; // La dérivée
	void setA(float _a);
	void setB(float _b);
	void setC(float _c);
};

}

#endif /* POLYDEG2_H_ */
