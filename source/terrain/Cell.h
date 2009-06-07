#ifndef CELL_H_
#define CELL_H_

#include "../ShootMii.h"

namespace shootmii {

  const int CELL_SIZE(8);

  class Cell {
    protected:
      int rowIndex;
      int colIndex;
      int screenX;
      int screenY;
    public:
      //Constructeur
      Cell(const int _rowIndex = 0, const int _colIndex = 0);
      // Accesseurs
      void setCoords(const int _rowIndex, const int _colIndex);
      int getRowIndex() const;
      int getColIndex() const;
      int getScreenX() const;
      int getScreenY() const;
      void setScreenX(int);
      void setScreenY(int);
      virtual bool cellIntersect(const Cell*) const;
  };
}

#endif /*CELL_H_*/
