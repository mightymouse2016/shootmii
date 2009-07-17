#ifndef CELL_H_
#define CELL_H_

#include "../ShootMii.h"

namespace shootmii {

class Cell {
protected:
	int width;
	int height;
	float screenX;
	float screenY;
	float angle;

public:
	Cell(
		const int _width,
		const int _height,
		const float _screenX = 0,
		const float _screenY = 0,
		const float _angle = 0);
	int getWidth() const;
	int getHeight() const;
	float getScreenX() const;
	float getScreenY() const;
	virtual int getCol() const;
	virtual int getRow() const;
	void setScreenX(const float _screenX);
	void setScreenY(const float _screenY);
	void setCol(const int _col);
	void setRow(const int _row);
	void setScreenCoords(const float _screenX, const float _screenY);
	virtual void setIndexCoords(const int _colIndex, const int _rowIndex);
	bool cellIntersect(const Cell* c) const;
};

}

#endif /*CELL_H_*/
