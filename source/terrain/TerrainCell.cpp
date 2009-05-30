#include "../ShootMii.h"

namespace shootmii {

  TerrainCell::TerrainCell(const CellType _type, const int _rowIndex,
    const int _colIndex) :
    Cell(_rowIndex, _colIndex), type(_type) {
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
        GRRLIB_Rectangle(screenX, screenY, CELL_SIZE, CELL_SIZE, BLUE_SKY, true);
        break;
      case GROUND:
        GRRLIB_Rectangle(screenX, screenY, CELL_SIZE, CELL_SIZE, BROWN, true);
        break;
      case GRASS:
        GRRLIB_Rectangle(screenX, screenY, CELL_SIZE, CELL_SIZE, GREEN_GRASS,
            true);
        break;
      default:
        GRRLIB_Rectangle(screenX, screenY, CELL_SIZE, CELL_SIZE, GREEN, true);
    }
  }
}
