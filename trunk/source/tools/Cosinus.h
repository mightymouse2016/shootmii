#ifndef COSINUS_H_
#define COSINUS_H_

#include "../ShootMii.h"

namespace shootmii{

class Cosinus: public Function {
public: // a*cos(b*t)+c
	Cosinus(const float _a = 1, const float _b = 1, const float _c = 0);
	float operator()(const float t) const; // La fonction
	float operator[](const float t) const; // La dérivée
};

}

#endif /* COSINUS_H_ */
