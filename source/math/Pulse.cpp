#include "../ShootMii.h"

namespace shootmii {

Pulse::Pulse(
		const float _r1,
		const float _r2,
		const float _period,
		const float _offset,
		const float _amplitude) :
	r1(_r1),
	r2(_r2),
	period(_period),
	offset(_offset),
	amplitude(_amplitude)
{

}

float Pulse::getR1() const{
	return r1;
}

float Pulse::getR2() const{
	return r2;
}

float Pulse::getPeriod() const{
	return r2;
}

float Pulse::getOffset() const{
	return offset;
}

float Pulse::getAmplitude() const{
	return amplitude;
}

void Pulse::setR1(const float _r1){
	r1 = _r1;
}

void Pulse::setR2(const float _r2){
	r2 = _r2;
}

void Pulse::setPeriod(const float _period){
	period = _period;
}

void Pulse::setOffset(const float _offset){
	offset = _offset;
}

void Pulse::setAmplitude(const float _amplitude){
	amplitude = _amplitude;
}

float Pulse::operator()(const float t) const{
	const float tModPeriod = fmod(t,period);
	float yRatio;
	if (tModPeriod < r1*r2*period) yRatio=tModPeriod/(r1*r2*period);
	else if (tModPeriod < r2*period) yRatio=1-(tModPeriod-r1*r2*period)/((1-r1)*r2*period);
	else yRatio=0;
	return yRatio*amplitude+offset;
}

float Pulse::operator[](const float t) const{
	const float tModPeriod = fmod(t,period);
	float yRatio;
	if (tModPeriod < r1*r2*period) yRatio=1/(r1*r2*period);
	else if (tModPeriod < r2*period) yRatio=-1/((1-r1)*r2*period);
	else yRatio=0;
	return yRatio*amplitude;
}

}
