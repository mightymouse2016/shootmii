#include "JaugeManager.h"

namespace shootmii {

JaugeManager::JaugeModification::JaugeModification(
		float* _percentage,
		float _amount,
		bool* _modifyFlag) :
	percentage(_percentage),
	amount(_amount),
	modifyFlag(_modifyFlag)
{

}

JaugeManager::JaugeModification::~JaugeModification(){
	if (modifyFlag != NULL) *modifyFlag = false;
}

JaugeManager::JaugeManager() :
	increases(new std::list<JaugeModification* >),
	decreases(new std::list<JaugeModification* >)
{
	// NOTHING TO DO
}

JaugeManager::~JaugeManager(){
	clear();

	for (std::list<JaugeModification* >::const_iterator i=increases->begin();i!=increases->end();i++){
		delete *i;
	}
	delete increases;


	for (std::list<JaugeModification* >::const_iterator i=decreases->begin();i!=decreases->end();i++){
		delete *i;
	}
	delete decreases;
}

void JaugeManager::addIncrease(float* percentage,float amount,bool* modifyFlag){
	increases->push_back(new JaugeModification(percentage,amount,modifyFlag));
}

void JaugeManager::addDecrease(float* percentage,float amount,bool* modifyFlag){
	decreases->push_back(new JaugeModification(percentage,amount,modifyFlag));
}

void JaugeManager::incPercentage(JaugeModification* increase){
	*(increase->percentage) += INC_STEP;
	if (*(increase->percentage) > 100) *(increase->percentage) = 100;
	if (increase->modifyFlag != NULL) *(increase->modifyFlag) = true;
}

void JaugeManager::decPercentage(JaugeModification* decrease){
	*(decrease->percentage) -= DEC_STEP;
	if (*(decrease->percentage) < 0) *(decrease->percentage) = 0;
	if (decrease->modifyFlag != NULL) *(decrease->modifyFlag) = true;
}

void JaugeManager::compute(){
	std::list<JaugeModification*>* newIncreases = new std::list<JaugeModification* >;
	for(std::list<JaugeModification*>::iterator i=increases->begin();i!=increases->end();i++){
		incPercentage(*i); 									// On incrémente le %
		(*i)->amount -= INC_STEP; 							// On diminue la "réserve" d'autant
		if ((*i)->amount > 0) newIncreases->push_back(*i);
		else delete *i; 									// Si la réserve est vide on la supprime
	}
	delete increases;
	increases = newIncreases;

	std::list<JaugeModification* >* newDecreases = new std::list<JaugeModification* >;
	for(std::list<JaugeModification*>::iterator i=decreases->begin();i!=decreases->end();i++){
		decPercentage(*i);
		(*i)->amount -= DEC_STEP;
		if ((*i)->amount > 0) newDecreases->push_back(*i);
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
