#include "../tools/ImageBank.h"
#include "../App.h"
#include "Button.h"
#include "Text.h"
#include "Dock.h"

namespace shootmii {

Dock::Dock(bool _position) :
	Rectangle(DOCK_LAYER,DOCK_WIDTH,DOCK_HEIGHT,DOCK_WIDTH/2,0,0,0,_position ? PI : 0,true,true,App::imageBank->get(TXT_DOCK)),
	position(_position)
{
	// NOTHING TO DO
}

void Dock::addButton(Button* button){
	button->setFather(this);
	buttons.push_back(button);
}

void Dock::addText(Text* text){
	text->setFather(this);
	texts.push_back(text);
}

void Dock::toggleHideShow(){
	hiddenOutOfScreen = !hiddenOutOfScreen;
	for (std::list<Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
		(*i)->toggleStuck();
	}
}

void Dock::init(){
	hiddenOutOfScreen = true;
	originY = position ? - DOCK_HEIGHT/2 : SCREEN_HEIGHT + DOCK_HEIGHT/2;
	for (std::list<Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
		(*i)->stuckIt();
	}
}


void Dock::compute(){
	if (position){
		if (hiddenOutOfScreen){
			originY -= HIDE_PACE;
			if (originY < -DOCK_HEIGHT/2) originY = -DOCK_HEIGHT/2;
		}
		else{
			originY += SHOW_PACE;
			if (originY > DOCK_HEIGHT/2) originY = DOCK_HEIGHT/2;
		}
	}
	else{
		if (hiddenOutOfScreen){
			originY += HIDE_PACE;
			if (originY > SCREEN_HEIGHT + DOCK_HEIGHT/2) originY = SCREEN_HEIGHT + DOCK_HEIGHT/2;
		}
		else{
			originY -= SHOW_PACE;
			if (originY < SCREEN_HEIGHT - DOCK_HEIGHT/2) originY = SCREEN_HEIGHT - DOCK_HEIGHT/2;
		}
	}
}

}
