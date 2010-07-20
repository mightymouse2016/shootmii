#include "../tools/Console.h"
#include "../tools/Animation.h"
#include "../math/Polygon.h"
#include "../App.h"
#include "Ammo.h"
#include "Bonus.h"
#include "Player.h"
#include "DrawManager.h"

namespace shootmii {

bool ComparePolygons::operator()(Polygon* p1,Polygon* p2){
	return (p1->getLayer() < p2->getLayer());
}

DrawManager::DrawManager() :
	polygonsToDraw(new std::multiset<Polygon*, ComparePolygons>)
{
	// NOTHING TO DO
}

DrawManager::~DrawManager(){
	delete polygonsToDraw;
}

void DrawManager::addToDraw(Polygon* polygon){
	polygonsToDraw->insert(polygon);
}

void DrawManager::addToDraw(std::list<Ammo*>* ammosList){
	for (std::list<Ammo*>::iterator i=ammosList->begin();i!=ammosList->end();i++)
		(*i)->addToDrawManager();
}

void DrawManager::addToDraw(std::list<Bonus*>* bonusesList){
	for (std::list<Bonus*>::iterator i=bonusesList->begin();i!=bonusesList->end();i++)
		(*i)->addToDrawManager();
}

void DrawManager::addToDraw(std::list<Animation*>* animationsList){
	for (std::list<Animation*>::iterator i=animationsList->begin();i!=animationsList->end();i++)
		(*i)->addToDrawManager();
}

void DrawManager::compute(){
	// On vide la liste pour la prochaine frame
	delete polygonsToDraw;
	polygonsToDraw = new std::multiset<Polygon*, ComparePolygons>;
}

void DrawManager::draw() const{
	// On affiche tout
	for (std::multiset<Polygon*>::iterator i=polygonsToDraw->begin();i!=polygonsToDraw->end();i++){
		(*i)->draw();
	}
	// On affiche le mode debug par dessus ! (Si il est actif)
	if (App::console->isDebug()){
		for (std::multiset<Polygon*>::iterator i=polygonsToDraw->begin();i!=polygonsToDraw->end();i++){
			(*i)->drawDebug();
		}
	}
}

}
