#ifndef TIMER_H_
#define TIMER_H_

namespace shootmii{

const float DEFAULT_TIME_STEP(.1);

class Timer{
protected:
	int t; //  Utiliser l'accesseur !
	int slow;
	float step; // Le vrai temps est en fait égal à t*step
public:
	Timer(int slow = 0, float step = DEFAULT_TIME_STEP);
	void compute();
	void setSlow(const int slow);
	float getT() const;
	void setT(const float t);
	bool timeIsOver() const;
	void init();
};

}

#endif /* TIMER_H_ */
