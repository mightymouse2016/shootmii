#ifndef JAUGEMANAGER_H_
#define JAUGEMANAGER_H_

#include "../ShootMii.h"

namespace shootmii{

const float INC_STEP(.2);
const float DEC_STEP(.4);

class JaugeManager{
private:
	struct JaugeModification{
	public:
		float* percentage;
		float amount;
		bool* modifyFlag;
		JaugeModification(float* percentage, float amount, bool* modifyFlag=NULL);
		~JaugeModification();
	};
	list<JaugeModification*>* increases; // Le float représente le montant à prélever dans la jauge
	list<JaugeModification*>* decreases;
public:
	JaugeManager();
	~JaugeManager();
	void addIncrease(float* percentage,float amount,bool* modifyFlag=NULL); // 100 > percentage > 0 ; amount > 0
	void addDecrease(float* percentage,float amount,bool* modifyFlag=NULL); // 100 > percentage > 0 ; amount > 0
	void incPercentage(JaugeModification* increase);
	void decPercentage(JaugeModification* decrease);
	void compute();
	void clear();
};

}

#endif /* JAUGEMANAGER_H_ */
