#include "../ShootMii.h"

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
	for (map<ButtonType,Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
		i->second->addToDrawManager();
		i->second->unHighLight();
	}
	for (list<Text*>::iterator i=texts.begin();i!=texts.end();i++){
		(*i)->addToDrawManager();
	}	
	for (list<Dock*>::iterator i=docks.begin();i!=docks.end();i++){
		(*i)->addToDrawManager();
	}
	
	// Si il y a des boutons et qu'on est en mode séléction
	if (buttons.size() != 0 && selectionMode){
		selectedButton->second->highLight();
	}
}

void Screen::init(){
	for (list<Dock*>::iterator i=docks.begin();i!=docks.end();i++){
		(*i)->init();
	}
	
	for (map<ButtonType,Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
		i->second->init();
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
}

void Screen::computePointer(Pointer* pointer){
	int x = pointer->getAbsoluteOriginX();
	int y = pointer->getAbsoluteOriginY();
	int bx, by, bw, bh;
	Button* b;

	for (map<ButtonType,Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
		b = i->second;
		if (b->isStuck()) continue;
		bx = b->getAbsoluteOriginX();
		by = b->getAbsoluteOriginY();
		bw = b->getWidth();
		bh = b->getHeight();
		if (x < (bx - bw/2)) continue;
		if (x > (bx + bw/2)) continue;
		if (y < (by - bh/2)) continue;
		if (y > (by + bh/2)) continue;
		if (pointer->isCliking()) b->click();
		b->pointOn();
		selectionMode = false;
	}
}

void Screen::computeButtons(){
	Button* b;
	for (map<ButtonType,Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
		b = i->second;
		if (b->isPointed()){
			b->grow();			// Grossissement du bouton
			b->pointOver();
		}
		else{
			b->shrink();		// Rétrécissement du bouton
		}
	}
}

void Screen::computeDocks(){
	for (list<Dock*>::iterator i=docks.begin();i!=docks.end();i++){
		(*i)->compute();
	}
}


void Screen::dealEvent(){
	pointerPlayer[0]->dealEvent();
	pointerPlayer[1]->dealEvent();
	// Gestion du mode DEBUG
	if ((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_MINUS) {
		App::console->toggleDebug();
	}
	// Si il y a des boutons sur l'écran
	if (buttons.size() > 0 && !selectedButton->second->isStuck()){
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
	if (selectionMode == true && ((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_A) && !selectedButton->second->isStuck()) {
		selectedButton->second->click();
		selectionMode = false;
	}
	
}

void Screen::addButton(const int originX, const int originY, const string text, const ButtonType type){
	buttons[type] = new Button(originX,originY,BUTTON_1_WIDTH,BUTTON_1_HEIGHT,text,App::imageBank->get(TXT_BUTTON_1));
	if (buttons.size() == 1) selectedButton = buttons.begin();
}

void Screen::addText(Text* text){
	texts.push_back(text);
}

void Screen::addDock(Dock* dock){
	docks.push_back(dock);
}

}
