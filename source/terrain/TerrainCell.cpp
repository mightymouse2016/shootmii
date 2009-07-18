#include "../ShootMii.h"

namespace shootmii {

TerrainCell::TerrainCell(
	GRRLIB_texImg* _tileSet,
	const int _width,
	const int _height) :
		Cell(_width,_height),
		type(EMPTY),
		tileSet(_tileSet),
		y1(1),
		y2(1)
{

}

CellType TerrainCell::getType() const {
	return type;
}

float TerrainCell::getY1() const{
	return y1;
}

float TerrainCell::getY2() const{
	return y2;
}

float TerrainCell::getAngle() const{
	return atan2(y1-y2,1);
}

void TerrainCell::setType(CellType _type) {
	type = _type;
}

void TerrainCell::setCell(const CellType _type, const float _y1, const float _y2) {
  type = _type;
  y1 = _y1;
  y2 = _y2;
}

int TerrainCell::getRelativeHeight(const int x) const {
  return height*((y2 - y1)*x/width + y1);
}

void TerrainCell::draw() const {
	GRRLIB_DrawTile(screenX, screenY, *tileSet, 0, 1, 1, WHITE, type);
	if (!App::console->isDebug()) return;
	if (type == EMPTY) return;
	GRRLIB_Line(screenX,screenY+(1-y1)*height,screenX,screenY+height,RED);
	GRRLIB_Line(screenX,screenY+(1-y1)*height,screenX+width,screenY+(1-y2)*height,RED);

}

}
