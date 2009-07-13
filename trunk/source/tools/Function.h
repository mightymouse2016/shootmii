#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "../ShootMii.h"

namespace shootmii {

class Function {
protected:
	float a;
	float b;
	float c;
public:
	Function(const float _a = 0, const float _b = 0, const float _c = 0);
	virtual float operator()(const float t) const=0; // la fonction
	virtual float operator[](const float t) const=0; // la dérivée
	void setA(float _a);
	void setB(float _b);
	void setC(float _c);
};

}

#endif /* FUNCTION_H_ */
