#include "../ShootMii.h"

namespace shootmii {

Screen::Screen(
		App* _app,
		Pointer** _pointerPlayer,
		u32** _eventsPlayer):
	app(_app),
	pointerPlayer(_pointerPlayer),
	eventsPlayer(_eventsPlayer)
{

}

Screen::~Screen(){
	buttons.clear();
}

void Screen::addToDrawManager(){
	pointerPlayer[0]->addToDrawManager();
	pointerPlayer[1]->addToDrawManager();
	for (map<ButtonType,Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
		App::drawManager->addToDraw(i->second);
	}
}

void Screen::init(){

}

void Screen::compute(){
	computePointer(pointerPlayer[0]);
	computePointer(pointerPlayer[1]);
	computeButtons();
}

void Screen::computePointer(Pointer* pointer){
	int x = pointer->getOriginX();
	int y = pointer->getOriginY();
	for (map<ButtonType,Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
		if (x < (i->second->getOriginX() - i->second->getWidth()/2)) continue;
		if (x > (i->second->getOriginX() + i->second->getWidth()/2)) continue;
		if (y < (i->second->getOriginY() - i->second->getHeight()/2)) continue;
		if (y > (i->second->getOriginY() + i->second->getHeight()/2)) continue;
		if (pointer->isCliking()) i->second->click();
		i->second->pointOn();
	}
}

void Screen::computeButtons(){
	for (map<ButtonType,Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
		if (i->second->isPointed()){
			i->second->setScale(BUTTON_GROWTH);
			i->second->pointOver();
		}
		else{
			i->second->setScale(1);
		}
	}
}

void Screen::dealEvent(){
	pointerPlayer[0]->dealEvent();
	pointerPlayer[1]->dealEvent();
	// Gestion du mode DEBUG
	if ((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_MINUS) {
		App::console->toggleDebug();
	}
}

void Screen::addButton(const int originX, const int originY, const string text, const ButtonType type){
	buttons[type] = new Button(originX,originY,BUTTON_1_WIDTH,BUTTON_1_HEIGHT,text,App::imageBank->get(TXT_BUTTON_1));
}

}
