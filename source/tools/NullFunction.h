#ifndef NULLFUNCTION_H_
#define NULLFUNCTION_H_

#include "../ShootMii.h"

namespace shootmii{

class NullFunction : public Function {
public:
	float operator()(const float t) const;
	float operator[](const float t) const;
};

}

#endif /* NULLFUNCTION_H_ */
