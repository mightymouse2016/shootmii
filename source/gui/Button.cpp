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
	App::fontManager->loadFont(gui_font, gui_font_size, 16);
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

void Button::draw() const{
	Polygon::draw();
	char textCopy[255];
	strcpy(textCopy,text.c_str());
	GXColor color = {0x00, 0x00, 0x00, 0xff};
	App::fontManager->drawText(originX, originY+16/2, FreeTypeGX::charToWideChar(textCopy),color,
            FTGX_JUSTIFY_CENTER | FTGX_ALIGN_BOTTOM);
}

}
