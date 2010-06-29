#ifndef WIND_H_
#define WIND_H_

#include <cstdlib>

namespace shootmii {

const int WIND_TURNOVER_PROBABILITY(60*60); // 1fois toutes les minutes

const float WIND_INFLUENCE_ON_AMMO(10); // 0->100
const float WIND_INFLUENCE_ON_FRONT_CLOUDS(1); // 0->100
const float WIND_INFLUENCE_ON_BACK_CLOUDS(.5); // 0->100

class Wind {
private:
	bool windModificationFlag;
	bool turnover; // false : gauche, true : droite
	float windSpeedRight;
	float windSpeedLeft; // Deux variables car plus simple pour les jauges ...
public:
	Wind();
	float* getPWindSpeedLeft();
	float* getPWindSpeedRight();
	float getWindSpeed() const;
	void compute();
	void init();
};

}

#endif /* WIND_H_ */
