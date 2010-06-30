#include "../fonts/army_font.h"
#include "../fonts/gui_font.h"
#include "Text.h"

namespace shootmii {

Text::Text(
		std::string _text,
		fontName _name,
		fontSize _size,
		u32 _color,
		const float _originX,
		const float _originY,
		const u16 _flags) :
	Rectangle(TEXT_LAYER,0,0,_originX,_originY),
	name(_name),
	size(_size),
	gxFont(new FreeTypeGX),
	flags(_flags)
{
	initFont();
	setText(_text);
	setColor(_color);
	update();
}

Text::~Text(){
	delete gxFont;
}

void Text::initFont(){
	switch (name){
	case GUI_FONT:
		gxFont->loadFont(gui_font, gui_font_size, size);
		break;
	case ARMY_FONT:
		gxFont->loadFont(army_font, army_font_size, size);
		break;
	default:
		gxFont->loadFont(gui_font, gui_font_size, size);
		break;
	}
}

void Text::setText(std::string _text){
	char textCopy[255];
	strcpy(textCopy,_text.c_str());
	text = FreeTypeGX::charToWideChar(textCopy);
}

void Text::setFontName(fontName _name){
	name = _name;
}

void Text::setFontSize(fontSize _size){
	size = _size;
}

void Text::update(){
	const float _height = gxFont->getHeight(text);
	const float _width = gxFont->getWidth(text);
	if (flags & FTGX_JUSTIFY_LEFT){
		vertices[0] = Coordinates(0,-_height/2);
		vertices[1] = Coordinates(_width,-_height/2);
		vertices[2] = Coordinates(_width,_height/2);
		vertices[3] = Coordinates(0,_height/2);
	}
	else if (flags & FTGX_JUSTIFY_RIGHT){
		vertices[0] = Coordinates(-_width,-_height/2);
		vertices[1] = Coordinates(0,-_height/2);
		vertices[2] = Coordinates(0,_height/2);
		vertices[3] = Coordinates(-_width,_height/2);
	}
	else {
		vertices[0] = Coordinates(-_width/2,-_height/2);
		vertices[1] = Coordinates(_width/2,-_height/2);
		vertices[2] = Coordinates(_width/2,_height/2);
		vertices[3] = Coordinates(-_width/2,_height/2);
	}
}

void Text::setColor(u32 _color){
	u8 r = (_color >> 24) & 0x000000FF;
	u8 g = (_color >> 16) & 0x000000FF;
	u8 b = (_color >> 8 ) & 0x000000FF;
	u8 a =  _color & 0x000000FF;
	color = (GXColor) {r,g,b,a};
}

void Text::draw(){
	Polygon::draw();
	gxFont->drawText(getAbsoluteOriginX(), getAbsoluteOriginY(), text,color, flags);
}

}
