#include "../ShootMii.h"

namespace shootmii {

TerrainCell::TerrainCell(
	GRRLIB_texImg* _tileSet,
	const int _width,
	const int _height) :
		Polygon(0,0,sqrt((_width/2)*(_width/2)+(_height/2)*(_height/2)),PI/4,0,0,NULL,Coordinates(-_width/2,-_height/2),_tileSet,EMPTY,_width,_height)
{
	vertices.reserve(4);
	vertices.push_back(Coordinates(-_width/2,-_height/2));
	vertices.push_back(Coordinates(_width/2,-_height/2));
	vertices.push_back(Coordinates(_width/2,_height/2));
	vertices.push_back(Coordinates(-_width/2,_height/2));
}

CellType TerrainCell::getType() const {
	return static_cast<CellType>(spriteIndex);
}

float TerrainCell::getY1() const{
	return vertices[UP_LEFT].getY();
}

float TerrainCell::getAbsoluteY1() const{
	return getAbsoluteY() + getY1();
}

float TerrainCell::getY2() const{
	return vertices[UP_RIGHT].getY();
}

float TerrainCell::getAbsoluteY2() const{
	return getAbsoluteY() + getY2();
}

float TerrainCell::getAngle() const{
	return atan2(getY2()-getY1(),spriteWidth);
}

void TerrainCell::setType(CellType _type) {
	spriteIndex = static_cast<int>(_type);
	switch (_type) {
	case SLOPE_UP_1 : setYs(spriteHeight/2,-spriteHeight/2);break;
	case SLOPE_DOWN_1 : setYs(-spriteHeight/2,spriteHeight/2);break;
	case SLOPE_UP_05_1 : setYs(spriteHeight/2,0);break;
	case SLOPE_UP_05_2 : setYs(0,-spriteHeight/2);break;
	case SLOPE_DOWN_05_1 : setYs(-spriteHeight/2,0);break;
	case SLOPE_DOWN_05_2 : setYs(0,spriteHeight/2);break;
	default : setYs(-spriteHeight/2,-spriteHeight/2);break;
	}
}

float TerrainCell::getAbsoluteHeight(const float x) const {
  return (getY2() - getY1())*(x-originX)/spriteWidth + getAbsoluteY1();
}

void TerrainCell::setYs(const int _y1, const int _y2){
	vertices[UP_LEFT].setY(_y1);
	vertices[UP_RIGHT].setY(_y2);
}

void TerrainCell::setIndexCoords(const int _colIndex, const int _rowIndex){
	originX = _colIndex*spriteWidth;
	originY = _rowIndex*spriteHeight;
}

/*
void TerrainCell::draw() const {
	if (type == EMPTY) return;
	if (App::console->isDebug()){
		GRRLIB_Line(screenX,screenY+(1-y1)*height,screenX,screenY+height,RED);
		GRRLIB_Line(screenX,screenY+(1-y1)*height,screenX+width,screenY+(1-y2)*height,RED);
	} else {
		GRRLIB_DrawTile(screenX, screenY, *tileSet, 0, 1, 1, WHITE, type);
	}

}
*/

}
