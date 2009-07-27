#include "../ShootMii.h"

namespace shootmii{

Timer::Timer(int _slow, float _step) : t(0), slow(_slow), step(_step) {}

void Timer::compute(){
	t++;
}

bool Timer::timeIsOver() const{
	return (!(t%slow));
}

float Timer::getT() const{
	return t*step;
}

}
