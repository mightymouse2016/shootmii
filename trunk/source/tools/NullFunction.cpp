#include "../ShootMii.h"

namespace shootmii {

float NullFunction::operator()(const float t) const{
	return 0;
}

float NullFunction::operator[](const float t) const{
	return 0;
}

}
