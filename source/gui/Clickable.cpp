#include "Clickable.h"

namespace shootmii {

Clickable::Clickable(
		const int _originX,
		const int _originY,
		const int _width,
		const int _height,
		const std::string _text,
		const Color& _textColor,
		const fontSize _textSize,
		const u16 _textFlags,
		GRRLIB_texImg* _image) :
		Rectangle(BUTTON_LAYER,_width,_height,_originX,_originY,0,0,0,true,true,_image,NULL,0,_width,_height),
		stuck(false),
		pointed(false),
		clicked(false)
{
	addChild(new Text(_text,GUI_FONT,_textSize,_textColor,0,0,_textFlags));
}

void Clickable::init(){
	scale = 1;
}

void Clickable::click(){
	clicked = true;
}

void Clickable::unClick(){
	clicked = false;
}

bool Clickable::isClicked() const{
	return clicked;
}

void Clickable::stuckIt(){
	stuck = true;
}

void Clickable::unStuckIt(){
	stuck = false;
}

void Clickable::toggleStuck(){
	stuck = !stuck;
}

bool Clickable::isStuck() const{
	return stuck;
}

void Clickable::pointOn(){
	pointed = true;
}

void Clickable::pointOver(){
	pointed = false;
}

bool Clickable::isPointed() const{
	return pointed;
}

Text* Clickable::getText(){
	return static_cast<Text*>(children[0]);
}

Text* Clickable::getText() const{
	return static_cast<Text*>(children[0]);
}

void Clickable::highLight(){
	// TODO highlight avec rectangle
}

void Clickable::unHighLight(){
	// TODO un-highlight
}

void Clickable::grow(){
	scale += GROW_PACE;
	if (scale > BUTTON_GROWTH) scale = BUTTON_GROWTH;
}

void Clickable::shrink(){
	scale -= SHRINK_PACE;
	if (scale < 1) scale = 1;
}

void Clickable::compute(){
	if (isPointed()){
		grow();		// Grossissement
		pointOver();
	}
	else{
		shrink();		// Rétrécissement
	}
}

}
