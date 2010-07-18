#include "../fonts/army_font.h"
#include "../fonts/gui_font.h"
#include "Text.h"

namespace shootmii {

Text::Text(
		std::string _text,
		fontName _name,
		fontSize _size,
		const Color& _color,
		const float _originX,
		const float _originY,
		const u16 _flags) :
	Rectangle(TEXT_LAYER,0,0,_originX,_originY),
	name(_name),
	size(_size),
	color(_color),
	gxFont(new FreeTypeGX),
	flags(_flags)
{
	initFont();
	setText(_text);
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

void Text::setUnderline(const bool underline){
	if (underline) flags |= FTGX_STYLE_UNDERLINE;
	else flags &= ~FTGX_STYLE_UNDERLINE;
}

void Text::update(){
	float x1,x2,y1,y2;
	const float _height = gxFont->getHeight(text);
	const float _width = gxFont->getWidth(text);

	// Gauche, droite, centre
	if (flags & FTGX_JUSTIFY_LEFT){
		x1 = 0;
		x2 = _width;
	}
	else if (flags & FTGX_JUSTIFY_RIGHT){
		x1 = -_width;
		x2 = 0;
	}
	else { // Par défaut FTGX_JUSTIFY_CENTER
		x1 = -_width/2;
		x2 = _width/2;
	}

	// Haut, bas, milieu

	if (flags & FTGX_ALIGN_TOP){
		y1 = 0;
		y2 = _height;
	}
	else if (flags & FTGX_ALIGN_MIDDLE){
		y1 = -_height/2;
		y2 = _height/2;
	}
	else { // Par défaut FTGX_ALIGN_BOTTOM
		y1 = -_height;
		y2 = 0;
	}

	vertices[0] = Coordinates(x1,y1);
	vertices[1] = Coordinates(x2,y1);
	vertices[2] = Coordinates(x2,y2);
	vertices[3] = Coordinates(x1,y2);
}

void Text::setColor(const Color& _color){
	color = _color;
}

void Text::draw(){
	Polygon::draw();
	gxFont->drawText(getAbsoluteOriginX(), getAbsoluteOriginY(), text,color, flags);
}

}
