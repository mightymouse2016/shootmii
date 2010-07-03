#include "../tools/Console.h"
#include "../tools/Tools.h"
#include "../gui/Button.h"
#include "../gui/Text.h"
#include "../gui/Dock.h"
#include "../gui/Pointer.h"
#include "../gui/Selector.h"
#include "../App.h"
#include "Screen.h"

namespace shootmii {

Screen::Screen(
		App* _app,
		Pointer** _pointerPlayer,
		u32** _eventsPlayer):
	app(_app),
	pointerPlayer(_pointerPlayer),
	eventsPlayer(_eventsPlayer),
	selectionMode(false)
{

}

Screen::~Screen(){
	/*
	 * Clickables, Texts, Docks et Selectors sont ajoutés en tant que fils,
	 * et sont donc détruits automatiquement.
	 */
	clickables.clear();
	texts.clear();
	docks.clear();
}

std::list<Clickable*>& Screen::getClickables(){
	return clickables;
}

const std::list<Clickable*>& Screen::getClickables() const{
	return clickables;
}

void Screen::addToDrawManager(){
	pointerPlayer[0]->addToDrawManager();
	pointerPlayer[1]->addToDrawManager();
	for (std::list<Clickable*>::iterator i=clickables.begin();i!=clickables.end();i++){
		(*i)->addToDrawManager();
		(*i)->unHighLight();
	}
	for (std::list<Text*>::iterator i=texts.begin();i!=texts.end();i++){
		(*i)->addToDrawManager();
	}	
	for (std::list<Dock*>::iterator i=docks.begin();i!=docks.end();i++){
		(*i)->addToDrawManager();
	}
	for (std::list<Selector*>::iterator i=selectors.begin();i!=selectors.end();i++){
		(*i)->addToDrawManager();
	}
	
	// Si il y a des boutons et qu'on est en mode séléction
	if (clickables.size() != 0 && selectionMode){
		(*selectedClickable)->highLight();
	}
}

void Screen::init(){
	for (std::list<Dock*>::iterator i=docks.begin();i!=docks.end();i++){
		(*i)->init();
	}
	
	for (std::list<Clickable*>::iterator i=clickables.begin();i!=clickables.end();i++){
		(*i)->init();
	}
	
	if (clickables.size() != 0){
		selectedClickable = clickables.begin();
	}
	
	selectionMode = false;
}

void Screen::compute(){
	computePointer(pointerPlayer[0]);
	computePointer(pointerPlayer[1]);
	computeClickables();
	computeDocks();
	computeSelectors();
}

void Screen::computePointer(Pointer* pointer){
	int x = pointer->getAbsoluteOriginX();
	int y = pointer->getAbsoluteOriginY();
	int x1,x2,y1,y2,ox,oy;

	for (std::list<Clickable*>::iterator i=clickables.begin();i!=clickables.end();i++){
		if ((*i)->isStuck()) continue;
		ox = (*i)->getAbsoluteOriginX();
		oy = (*i)->getAbsoluteOriginY();
		x1 = ox + (*i)->getVertices()[0].getX();
		x2 = ox + (*i)->getVertices()[1].getX();
		y1 = oy + (*i)->getVertices()[1].getY();
		y2 = oy + (*i)->getVertices()[2].getY();
		if (x < x1 || x > x2 || y < y1 || y > y2) continue;
		if (pointer->isCliking()) (*i)->click();
		(*i)->pointOn();
		selectionMode = false;
	}
}

void Screen::computeClickables(){
	for (std::list<Clickable*>::iterator i=clickables.begin();i!=clickables.end();i++){
		(*i)->compute();
	}
}

void Screen::computeDocks(){
	for (std::list<Dock*>::iterator i=docks.begin();i!=docks.end();i++){
		(*i)->compute();
	}
}

void Screen::computeSelectors(){

}

void Screen::dealEvent(){
	pointerPlayer[0]->dealEvent();
	pointerPlayer[1]->dealEvent();
	// Gestion du mode DEBUG
	if ((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_MINUS) {
		App::console->toggleDebug();
	}
	// Si il y a des boutons sur l'écran
	if (clickables.size() > 0 && !(*selectedClickable)->isStuck()){
		// haut et gauche
		if (((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_UP) || 
				((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_LEFT)) {
			// Si aucun bouton n'est séléctionné on se met sur le premier
			if (selectionMode == false){
				selectedClickable = clickables.begin();
				selectionMode = true;
			}
			// Sinon on séléctionne le prochain
			else{
				if (selectedClickable == clickables.begin()) selectedClickable = clickables.end();
				selectedClickable--;
			}
		}
		// bas et droite
		if (((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_DOWN) || 
				((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_RIGHT)) {
			// Si aucun bouton n'est séléctionné on se met sur le premier
			if (selectionMode == false){
				selectedClickable = clickables.begin();
				selectionMode = true;
			}
			// Sinon on séléctionne le précédent
			else{
				selectedClickable++;
				if (selectedClickable == clickables.end()) selectedClickable = clickables.begin();
			}
		}
	}
	
	// si on appuie sur A alors qu'un bouton séléctionné
	if (selectionMode == true && ((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_A) && !(*selectedClickable)->isStuck()) {
		(*selectedClickable)->click();
		selectionMode = false;
	}
	
}

void Screen::addButton(Button* button){
	clickables.push_back(button);
	if (clickables.size() == 1) selectedClickable = clickables.begin();
}

void Screen::addText(Text* text){
	texts.push_back(text);
}

void Screen::addDock(Dock* dock){
	docks.push_back(dock);
}

void Screen::addSelector(Selector* selector){
	selectors.push_back(selector);
}

}
