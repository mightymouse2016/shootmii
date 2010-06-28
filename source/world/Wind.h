#ifndef WIND_H_
#define WIND_H_

#include <cstdlib>

namespace shootmii {

const float WIND_INFLUENCE_ON_AMMO(10); // 0->100
const float WIND_INFLUENCE_ON_FRONT_CLOUDS(1); // 0->100
const float WIND_INFLUENCE_ON_BACK_CLOUDS(.5); // 0->100

class Wind {
private:
	float windSpeedLeft; // Deux variables car plus simple pour les jauges ...
	float windSpeedRight;
public:
	float* getPWindSpeedLeft();
	float* getPWindSpeedRight();
	float getWindSpeed() const;
	void init();
};

}

#endif /* WIND_H_ */
