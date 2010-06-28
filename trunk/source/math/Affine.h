#ifndef AFFINE_H_
#define AFFINE_H_

#include "Function.h"

namespace shootmii {

class Affine: public Function {
protected:
	float a;
	float b;
public:
	Affine(const float _a = 0, const float _b = 0);
	float operator()(const float t) const;
	float operator[](const float t) const;
	void setA(float a);
	void setB(float b);
};

}

#endif /* AFFINE_H_ */
