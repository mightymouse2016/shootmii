#include "../tools/Colors.h"
#include "../gui/Text.h"
#include "SelectorOption.h"

namespace shootmii {

SelectorOption::SelectorOption(
		const int _originX,
		const int _originY,
		const std::string _text) :
		Clickable(
				_originX,
				_originY,
				0,
				0,
				_text,
				WHITE,
				FONT_SIZE_10,
				FTGX_ALIGN_MIDDLE | FTGX_JUSTIFY_LEFT),
		highLighted(false)
{
	vertices[0] = getText()->getVertices()[0];
	vertices[1] = getText()->getVertices()[1];
	vertices[2] = getText()->getVertices()[2];
	vertices[3] = getText()->getVertices()[3];
}

void SelectorOption::grow(){
	Clickable::grow();
	getText()->setUnderline(true);
}

void SelectorOption::shrink(){
	Clickable::shrink();
	getText()->setUnderline(false);
}

void SelectorOption::draw(){
	Clickable::draw();
	if (!highLighted) return;
	int ox = getAbsoluteOriginX();
	int oy = getAbsoluteOriginY();
	int x1 = ox + vertices[0].getX();
	int x2 = ox + vertices[1].getX();
	int y1 = oy + vertices[1].getY();
	int y2 = oy + vertices[2].getY();
	for (int i=-1;i<2;i++) {
		GRRLIB_Line(x1+i,y1+i,x2-i,y1+i, GREEN);
		GRRLIB_Line(x1+i,y2-i,x2-i,y2-i, GREEN);
		GRRLIB_Line(x1+i,y1+i,x1+i,y2-i, GREEN);
		GRRLIB_Line(x2-i,y1+i,x2-i,y2-i, GREEN);
	}
}

void SelectorOption::highLight(){
	highLighted = true;
}

void SelectorOption::unHighLight(){
	highLighted = false;
}

}
