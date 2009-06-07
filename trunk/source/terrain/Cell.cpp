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

  int Cell::getScreenX() const {
    return screenX;
  }

  int Cell::getScreenY() const {
    return screenY;
  }
  
  void Cell::setScreenX(int _screenX){
    screenX = _screenX;
  }
  
  void Cell::setScreenY(int _screenY){
    screenY = _screenY;
  }

  bool Cell::cellIntersect(const Cell* c) const {
    if (screenX - CELL_SIZE > c->getScreenX()) {
      return false;
    } else if (screenX + CELL_SIZE < c->getScreenX()) {
      return false;
    } else if (screenY - CELL_SIZE > c->getScreenY()) {
      return false;
    } else if (screenY + CELL_SIZE < c->getScreenY()) {
      return false;
    }
    return true;
  }

}
