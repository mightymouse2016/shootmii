#ifndef WIND_H_
#define WIND_H_

#include "../ShootMii.h"

namespace shootmii {

const int WIND_INFLUENCE_ON_AMMO(5); // 0->100
const int WIND_INFLUENCE_ON_CLOUDS(10); // 0->100

class Wind {
private:
	int windSpeed;
	bool windDirection;
public:
	int getWindSpeed() const;
	bool getWindDirection() const;
	void init();
};

}

#endif /* WIND_H_ */
