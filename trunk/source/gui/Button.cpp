#include "../ShootMii.h"

namespace shootmii {

Button::Button(const int originX,
	const int originY,
	const int width,
	const int height,
	const string _text,
	GRRLIB_texImg* image) :
		Rectangle(BUTTON_LAYER,width,height,originX,originY,0,0,0,1,image),
		text(_text),
		pointed(false),
		clicked(false)
{
	// NOTHING TO DO
}

void Button::click(){
	clicked = true;
}

void Button::unClick(){
	clicked = false;
}

bool Button::isClicked() const{
	return clicked;
}

void Button::pointOn(){
	pointed = true;
}

void Button::pointOver(){
	pointed = false;
}

bool Button::isPointed() const{
	return pointed;
}


}
