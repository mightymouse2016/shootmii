#include "../ShootMii.h"

namespace shootmii {

Button::Button(const int originX,
	const int originY,
	const int width,
	const int height,
	const string _text,
	GRRLIB_texImg* image) :
		Rectangle(BUTTON_LAYER,width,height,originX,originY,0,0,0,true,true,image,NULL,0,width,height),
		stuck(false),
		pointed(false),
		clicked(false)
{
	addChild(new Text(_text,GUI_FONT,FONT_SIZE_6,BLACK));
}

void Button::init(){
	scale = 1;
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

void Button::stuckIt(){
	stuck = true;
}

void Button::unStuckIt(){
	stuck = false;
}

void Button::toggleStuck(){
	stuck = !stuck;
}

bool Button::isStuck() const{
	return stuck;
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

Text* Button::getText(){
	return static_cast<Text*>(children[1]);
}

Text* Button::getText() const{
	return static_cast<Text*>(children[1]);
}

void Button::highLight(){
	setSprite(1);
}

void Button::unHighLight(){
	setSprite(0);
}

void Button::grow(){
	scale += GROW_PACE;
	if (scale > BUTTON_GROWTH) scale = BUTTON_GROWTH;
}

void Button::shrink(){
	scale -= SHRINK_PACE;
	if (scale < 1) scale = 1;
}

void Button::draw(){
	Rectangle::draw();
}

}
