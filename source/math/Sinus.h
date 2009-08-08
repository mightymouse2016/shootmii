#ifndef SINUS_H_
#define SINUS_H_

#include "../ShootMii.h"

namespace shootmii{

class Sinus: public Function {
public: // a*sin(b*t)+c
	Sinus(const float _a = 1, const float _b = 1, const float _c = 0);
	float operator()(const float t) const; // La fonction
	float operator[](const float t) const; // La dérivée
};


}

#endif /* SINUS_H_ */
