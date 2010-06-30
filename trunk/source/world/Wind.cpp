#include "../game/JaugeManager.h"
#include "../game/Manager.h"
#include "Wind.h"

namespace shootmii {

Wind::Wind() :
	windModificationFlag(false),
	turnover(false),
	windSpeedRight(0),
	windSpeedLeft(0)
{

}

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

void Wind::compute(){
	if (windModificationFlag){
		if (turnover){
			if (windSpeedLeft) windSpeedRight = 0;
		}
		else{
			if (windSpeedRight) windSpeedLeft = 0;
		}
	}
	else{
		if (rand()%WIND_TURNOVER_PROBABILITY){
			turnover = windSpeedRight == 0;
			int windSpeed = rand()%100;
			if (turnover){
				Manager::jaugeManager->addIncrease(&windSpeedRight,windSpeed,&windModificationFlag);
				Manager::jaugeManager->addDecrease(&windSpeedLeft,200,&windModificationFlag);
			}
			else{
				Manager::jaugeManager->addIncrease(&windSpeedLeft,windSpeed,&windModificationFlag);
				Manager::jaugeManager->addDecrease(&windSpeedRight,200,&windModificationFlag);
			}
		}
	}
}

void Wind::init(){
	windModificationFlag = false;
	turnover = false;
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
