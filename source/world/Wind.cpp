#include "Wind.h"

namespace shootmii {

float* Wind::getPWindSpeedLeft(){
	return &windSpeedLeft;
}

float* Wind::getPWindSpeedRight(){
	return &windSpeedRight;
}

float Wind::getWindSpeed() const{
	if (windSpeedLeft) return -windSpeedLeft;
	return windSpeedRight;
}

void Wind::init(){
	int windSpeed = rand()%100;
	if (rand()%100 < 50) {
		windSpeedLeft = windSpeed;
		windSpeedRight = 0;
	}
	else {
		windSpeedLeft = 0;
		windSpeedRight = windSpeed;
	}
}

}
