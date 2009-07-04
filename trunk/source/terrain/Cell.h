#ifndef CELL_H_
#define CELL_H_

#include "../ShootMii.h"

namespace shootmii {

class Cell {
protected:
	int width;
	int height;
	int screenX;
	int screenY;
	float angle;
	
public:
	Cell(const int _width, const int _height, const int _screenX = 0, const int _screenY = 0);
	int getWidth() const;
	int getHeight() const;
	int getScreenX() const;
	int getScreenY() const;
	virtual int getCol() const;
	virtual int getRow() const;
	void setScreenX(const int _screenX);
	void setScreenY(const int _screenY);
	void setCol(const int _col);
	void setRow(const int _row);
	void setScreenCoords(const int _screenX, const int _screenY);
	virtual void setIndexCoords(const int _colIndex, const int _rowIndex);
	bool cellIntersect(const Cell* c) const;
};
}

#endif /*CELL_H_*/
