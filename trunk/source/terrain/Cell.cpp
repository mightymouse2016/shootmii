#include "../ShootMii.h"

namespace shootmii {

Cell::Cell(
		const int _width,
		const int _height,
		const float _screenX,
		const float _screenY,
		const float _angle) :
	width(_width),
	height(_height),
	screenX(_screenX),
	screenY(_screenY),
	angle(_angle)
{

}

int Cell::getWidth() const {
	return width;
}

int Cell::getHeight() const {
	return height;
}

float Cell::getScreenX() const {
	return screenX;
}

float Cell::getScreenY() const {
	return screenY;
}

int Cell::getCol() const{
	return int(screenX/width);
}

int Cell::getRow() const{
	return int(screenY/height);
}

void Cell::setScreenX(const float _screenX) {
	screenX = _screenX;
}

void Cell::setScreenY(const float _screenY) {
	screenY = _screenY;
}

void Cell::setCol(const int _col){
	screenX = _col*width;
}

void Cell::setRow(const int _row){
	screenY = _row*height;
}

void Cell::setScreenCoords(const float _screenX, const float _screenY){
	screenX = _screenX;
	screenY = _screenY;
}

void Cell::setIndexCoords(const int _colIndex, const int _rowIndex){
	screenX = _colIndex*width;
	screenY = _rowIndex*height;
}

bool Cell::cellIntersect(const Cell* c) const {
	if (screenX > c->getScreenX() + c->getWidth()) return false;
	else if (screenX + width < c->getScreenX()) return false;
	else if (screenY > c->getScreenY() + c->getHeight()) return false;
	else if (screenY + height < c->getScreenY()) return false;
	return true;
}

}
