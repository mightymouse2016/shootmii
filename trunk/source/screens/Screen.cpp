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
	buttons.clear();
	texts.clear();
	docks.clear();
}

void Screen::addToDrawManager(){
	pointerPlayer[0]->addToDrawManager();
	pointerPlayer[1]->addToDrawManager();
	for (std::list<Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
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
	if (buttons.size() != 0 && selectionMode){
		(*selectedButton)->highLight();
	}
}

void Screen::init(){
	for (std::list<Dock*>::iterator i=docks.begin();i!=docks.end();i++){
		(*i)->init();
	}
	
	for (std::list<Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
		(*i)->init();
	}
	
	if (buttons.size() != 0){
		selectedButton = buttons.begin();
	}
	
	selectionMode = false;
}

void Screen::compute(){
	computePointer(pointerPlayer[0]);
	computePointer(pointerPlayer[1]);
	computeButtons();
	computeDocks();
	computeSelectors();
}

void Screen::computePointer(Pointer* pointer){
	int x = pointer->getAbsoluteOriginX();
	int y = pointer->getAbsoluteOriginY();
	int bx, by, bw, bh;

	for (std::list<Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
		if ((*i)->isStuck()) continue;
		bx = (*i)->getAbsoluteOriginX();
		by = (*i)->getAbsoluteOriginY();
		bw = (*i)->getWidth();
		bh = (*i)->getHeight();
		if (x < (bx - bw/2)) continue;
		if (x > (bx + bw/2)) continue;
		if (y < (by - bh/2)) continue;
		if (y > (by + bh/2)) continue;
		if (pointer->isCliking()) (*i)->click();
		(*i)->pointOn();
		selectionMode = false;
	}
}

void Screen::computeButtons(){
	for (std::list<Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
		if ((*i)->isPointed()){
			(*i)->grow();			// Grossissement du bouton
			(*i)->pointOver();
		}
		else{
			(*i)->shrink();		// Rétrécissement du bouton
		}
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
	if (buttons.size() > 0 && !(*selectedButton)->isStuck()){
		// haut et gauche
		if (((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_UP) || 
				((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_LEFT)) {
			// Si aucun bouton n'est séléctionné on se met sur le premier
			if (selectionMode == false){
				selectedButton = buttons.begin();
				selectionMode = true;
			}
			// Sinon on séléctionne le prochain
			else{
				if (selectedButton == buttons.begin()) selectedButton = buttons.end();
				selectedButton--;
			}
		}
		// bas et droite
		if (((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_DOWN) || 
				((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_RIGHT)) {
			// Si aucun bouton n'est séléctionné on se met sur le premier
			if (selectionMode == false){
				selectedButton = buttons.begin();
				selectionMode = true;
			}
			// Sinon on séléctionne le précédent
			else{
				selectedButton++;
				if (selectedButton == buttons.end()) selectedButton = buttons.begin();
			}
		}
	}
	
	// si on appuie sur A alors qu'un bouton séléctionné
	if (selectionMode == true && ((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_A) && !(*selectedButton)->isStuck()) {
		(*selectedButton)->click();
		selectionMode = false;
	}
	
}

void Screen::addButton(Button* button){
	buttons.push_back(button);
	if (buttons.size() == 1) selectedButton = buttons.begin();
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
