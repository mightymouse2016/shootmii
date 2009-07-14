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

int TerrainCell::getY1() const{
	return y1;
}

int TerrainCell::getY2() const{
	return y2;
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

	int x_gauche = screenX;
	int x_droite = screenX + width;
	int y_bas = screenY + height;
	int y_haut_gauche = screenY + (1-y1)*height;
	int y_haut_droite = screenY + (1-y2)*height;

	GRRLIB_Line(x_gauche,y_haut_gauche,x_droite,y_haut_droite,RED);
	GRRLIB_Line(x_droite,y_haut_droite,x_droite,y_bas,RED);
	GRRLIB_Line(x_droite,y_bas,x_gauche,y_bas,RED);
	GRRLIB_Line(x_gauche,y_bas,x_gauche,y_haut_gauche,RED);

}

}
