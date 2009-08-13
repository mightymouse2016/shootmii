#ifndef JAUGEMANAGER_H_
#define JAUGEMANAGER_H_

#include "../ShootMii.h"

namespace shootmii{

const float INC_STEP(.2);
const float DEC_STEP(.4);

class JaugeManager{
private:
	list<pair<float*,float>*>* increases; // Le float représente le montant à prélever dans la jauge
	list<pair<float*,float>*>* decreases;
public:
	JaugeManager();
	~JaugeManager();
	void addIncrease(float* percentage,float amount); // 100 > percentage > 0 ; amount > 0
	void addDecrease(float* percentage,float amount); // 100 > percentage > 0 ; amount > 0
	void incPercentage(pair<float*,float>* increase);
	void decPercentage(pair<float*,float>* decrease);
	void compute();
	void clear();
};

}

#endif /* JAUGEMANAGER_H_ */
