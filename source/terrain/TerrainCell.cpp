#include "../ShootMii.h"

namespace shootmii {

TerrainCell::TerrainCell(const CellType _type, const int _colIndex, const int _rowIndex) :
	Cell(TERRAIN_CELL_WIDTH, TERRAIN_CELL_HEIGHT, _colIndex * TERRAIN_CELL_WIDTH, _rowIndex * TERRAIN_CELL_HEIGHT),
	type(_type)
{

}

CellType TerrainCell::getType() const {
	return type;
}

void TerrainCell::setType(CellType _type) {
	type = _type;
}

void TerrainCell::draw() const {
	switch (type) {
	case SKY:
		break;
	case GROUND:
		GRRLIB_Rectangle(screenX, screenY, width, height, BROWN, true);
		break;
	case GRASS:
		GRRLIB_Rectangle(screenX, screenY, width, height, GREEN_GRASS, true);
		break;
	default:
		GRRLIB_Rectangle(screenX, screenY, width, height, GREEN, true);
	}
}

}
