#include "Timer.h"

namespace shootmii{

Timer::Timer(int _slow, float _step) : t(0), slow(_slow), step(_step) {}

void Timer::compute(){
	t++;
}

bool Timer::timeIsOver() const{
	return (!(t%slow));
}

void Timer::setSlow(const int _slow){
	slow = _slow;
}

float Timer::getT() const{
	return t*step;
}

void Timer::setT(const float _t){
	t = _t;
}

void Timer::init(){
	t=0;
}

}
