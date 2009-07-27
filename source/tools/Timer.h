#ifndef TIMER_H_
#define TIMER_H_

#include "../ShootMii.h"

namespace shootmii{

const float DEFAULT_TIME_STEP(.1);

class Timer{
private:
	int t;
	int slow;
	float step; // Le vrai temps est en fait égal à t*step
public:
	Timer(int slow = 0, float step = DEFAULT_TIME_STEP);
	void compute();
	float getT() const;
	bool timeIsOver() const;
};

}

#endif /* TIMER_H_ */
