#include "../ShootMii.h"

namespace shootmii {

Text::Text(string _text, fontName _name, fontSize _size, u32 _color, const float _originX, const float _originY) :
	Rectangle(TEXT_LAYER,0,0,_originX,_originY),
	name(_name),
	size(_size),
	gxFont(new FreeTypeGX)
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

void Text::setText(string _text){
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
	setWidthHeight(gxFont->getWidth(text),gxFont->getHeight(text));
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
	float x = getAbsoluteOriginX();
	float y = getAbsoluteOriginY()+size/2;
	gxFont->drawText(x, y, text,color, FTGX_JUSTIFY_CENTER | FTGX_ALIGN_BOTTOM);
}

}
