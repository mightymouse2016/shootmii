#include "../ShootMii.h"

namespace shootmii {

JaugeManager::JaugeManager() :
	increases(new list<pair<float*,float>* >),
	decreases(new list<pair<float*,float>* >)
{
	// NOTHING TO DO
}

JaugeManager::~JaugeManager(){
	clear();
	delete increases;
	delete decreases;
}

void JaugeManager::addIncrease(float* percentage,float amount){
	increases->push_back(new pair<float*,float>(percentage,amount));
}

void JaugeManager::addDecrease(float* percentage,float amount){
	decreases->push_back(new pair<float*,float>(percentage,amount));
}

void JaugeManager::incPercentage(pair<float*,float>* increase){
	*(increase->first) += INC_STEP;
	if (*(increase->first) > 100) *(increase->first) = 100;
}

void JaugeManager::decPercentage(pair<float*,float>* decrease){
	*(decrease->first) -= DEC_STEP;
	if (*(decrease->first) < 0) *(decrease->first) = 0;
}

void JaugeManager::compute(){
	list<pair<float*,float>* >* newIncreases = new list<pair<float*,float>* >;
	for(list<pair<float*,float>*>::iterator i=increases->begin();i!=increases->end();i++){
		incPercentage(*i); 									// On incrémente le %
		(*i)->second -= INC_STEP; 							// On diminue la "réserve" d'autant
		if ((*i)->second > 0) newIncreases->push_back(*i);
		else delete *i; 									// Si la réserve est vide on la supprime
	}
	delete increases;
	increases = newIncreases;

	list<pair<float*,float>* >* newDecreases = new list<pair<float*,float>* >;
	for(list<pair<float*,float>*>::iterator i=decreases->begin();i!=decreases->end();i++){
		decPercentage(*i);
		(*i)->second -= DEC_STEP;
		if ((*i)->second > 0) newDecreases->push_back(*i);
		else delete *i;
	}
	delete decreases;
	decreases = newDecreases;
}

void JaugeManager::clear(){
	decreases->clear();
	increases->clear();
}

}
