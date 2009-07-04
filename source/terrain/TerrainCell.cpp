#include "../ShootMii.h"

namespace shootmii {

TerrainCell::TerrainCell(
  GRRLIB_texImg* _tileSet) :
    Cell(TERRAIN_CELL_WIDTH,
        TERRAIN_CELL_HEIGHT),
        type(EMPTY),
        tileSet(_tileSet)
{

}

CellType TerrainCell::getType() const {
	return type;
}

void TerrainCell::setType(CellType _type) {
	type = _type;
}

void TerrainCell::setCell(const CellType _type, const float _y1, const float _y2) {
  type = _type;
  y1 = _y1;
  y2 = _y2;
}

int TerrainCell::getHeight(const int x) const {
  return height*((y2 - y1)*x/width + y1);
}

void TerrainCell::draw() const {
	  GRRLIB_DrawTile(screenX, screenY, *tileSet, 0, 1, 1, WHITE, type);
}

}
