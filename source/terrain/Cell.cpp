#include "../ShootMii.h"

namespace shootmii {

  Cell::Cell(const int _rowIndex, const int _colIndex) :
    rowIndex(_rowIndex), colIndex(_colIndex), screenX(_colIndex*CELL_SIZE),
        screenY(_rowIndex*CELL_SIZE) {
  }

  void Cell::setCoords(const int _rowIndex, const int _colIndex) {
    rowIndex = _rowIndex;
    colIndex = _colIndex;
    screenX = _colIndex*CELL_SIZE;
    screenY = _rowIndex*CELL_SIZE;
  }

  int Cell::getRowIndex() const {
    return rowIndex;
  }

  int Cell::getColIndex() const {
    return colIndex;
  }

  int Cell::getscreenX() const {
    return screenX;
  }

  int Cell::getscreenY() const {
    return screenY;
  }

}
