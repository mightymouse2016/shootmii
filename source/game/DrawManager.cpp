#include "../ShootMii.h"

namespace shootmii {

DrawManager::DrawManager() :
	polygonsToDraw(new multiset<Polygon*, ComparePolygons>)
{
	// NOTHING TO DO
}

DrawManager::~DrawManager(){
	delete polygonsToDraw;
}

void DrawManager::addToDraw(Polygon* polygon){
	polygonsToDraw->insert(polygon);
}

void DrawManager::addToDraw(list<Ammo*>* ammosList){
	for (list<Ammo*>::iterator i=ammosList->begin();i!=ammosList->end();i++)
		(*i)->addToDrawManager();
}

void DrawManager::addToDraw(list<Bonus*>* bonusesList){
	for (list<Bonus*>::iterator i=bonusesList->begin();i!=bonusesList->end();i++)
		(*i)->addToDrawManager();
}

void DrawManager::addToDraw(list<Animation*>* animationsList){
	for (list<Animation*>::iterator i=animationsList->begin();i!=animationsList->end();i++)
		(*i)->addToDrawManager();
}

void DrawManager::draw(){
	// On affiche tout
	for (multiset<Polygon*>::iterator i=polygonsToDraw->begin();i!=polygonsToDraw->end();i++){
		(*i)->draw();
	}
	// On affiche le mode debug par dessus ! (Si il est actif)
	if (App::console->isDebug()){
		for (multiset<Polygon*>::iterator i=polygonsToDraw->begin();i!=polygonsToDraw->end();i++){
			(*i)->drawDebug();
		}
	}
	// On vide la liste pour la prochaine frame
	delete polygonsToDraw;
	polygonsToDraw = new multiset<Polygon*, ComparePolygons>;
}

}
