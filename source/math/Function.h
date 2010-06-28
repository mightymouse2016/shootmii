#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "../ShootMii.h"

namespace shootmii {

class Function {
public:
	Function();
	virtual float operator()(const float t) const=0; // la fonction
	virtual float operator[](const float t) const=0; // la d�riv�e
};

}

#endif /* FUNCTION_H_ */
