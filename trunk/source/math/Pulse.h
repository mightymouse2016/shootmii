#ifndef AFFINESEGMENTS_H_
#define AFFINESEGMENTS_H_

#include "Function.h"
#include <cmath>

namespace shootmii {

const float DEFAULT_R1(.5);
const float DEFAULT_R2(.5);
const float DEFAULT_PERIOD(1);
const float DEFAULT_OFFSET(0);
const float DEFAULT_AMPLITUDE(1);

//     /\                       |
//  __/__\_____________         | amplitude
//   /    \             |offset |
//  /      \___________ |       |
//  _r1_|___
//  ___r2___|___________
//	______period________

class Pulse: public Function {
protected:
	float r1;	// 0->1 ( 0 : __, 1 : /\ )
	float r2;	// 0->1 ratio ( 0 : |\__, 1 ; /|__)
	float period;
	float offset;
	float amplitude;
public:
	Pulse(
		const float r1 = DEFAULT_R1,
		const float r2 = DEFAULT_R2,
		const float period = DEFAULT_PERIOD,
		const float offset = DEFAULT_OFFSET,
		const float amplitude = DEFAULT_AMPLITUDE);
	float getR1() const;
	float getR2() const;
	float getPeriod() const;
	float getOffset() const;
	float getAmplitude() const;
	void setR1(const float r1);
	void setR2(const float r1);
	void setPeriod(const float r1);
	void setOffset(const float r1);
	void setAmplitude(const float r1);
	float operator()(const float t) const; // La fonction
	float operator[](const float t) const; // La dérivée
};

}

#endif /* AFFINESEGMENTS_H_ */
