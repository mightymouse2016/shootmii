#ifndef TIMER_H_
#define TIMER_H_

#include "../ShootMii.h"

namespace shootmii{

const float DEFAULT_TIME_STEP(.1);

class Timer{
protected:
	int t; //  Utiliser l'accesseur !
	int slow;
	float step; // Le vrai temps est en fait �gal � t*step
public:
	Timer(int slow = 0, float step = DEFAULT_TIME_STEP);
	void compute();
	void setSlow(const int slow);
	float getT() const;
	bool timeIsOver() const;
	void init();
};

}

#endif /* TIMER_H_ */
