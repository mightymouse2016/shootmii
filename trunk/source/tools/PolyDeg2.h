#ifndef POLYDEG2_H_
#define POLYDEG2_H_

#include "../ShootMii.h"

namespace shootmii {

class PolyDeg2: public Function {
public:
	PolyDeg2(const float _a = 0, const float _b = 0, const float _c = 0);
	float operator()(const float t) const; // La fonction
	float operator[](const float t) const; // La dérivée
};

}

#endif /* POLYDEG2_H_ */
