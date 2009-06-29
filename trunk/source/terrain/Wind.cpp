#include "../ShootMii.h"

namespace shootmii {

int Wind::getWindSpeed() const{
	return windSpeed;
}

bool Wind::getWindDirection() const{
	return windDirection;
}

void Wind::init(){
	windSpeed = rand()%100+1;
	if (rand()%1000 < 500) windDirection = false;
	else windDirection = true;
}

}
