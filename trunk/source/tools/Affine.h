#ifndef AFFINE_H_
#define AFFINE_H_

#include "../ShootMii.h"

namespace shootmii {

class Affine: public Function {
public:
	Affine(const float _a = 0, const float _b = 0);
	float operator()(const float t) const;
	float operator[](const float t) const;
};

}

#endif /* AFFINE_H_ */
