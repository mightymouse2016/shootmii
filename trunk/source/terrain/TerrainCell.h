#ifndef TERRAINCELL_H_
#define TERRAINCELL_H_

#include "../ShootMii.h"

const int N_CELLTYPE(2); // Nombre de type de cellules, pour l'instant terre ou ciel

namespace shootmii {

enum CellType {
	EMPTY = -1,

	GRASS_LEFT,
	GRASS_MID,
	GRASS_RIGHT,
	SLOPE_UP_05_1,
	SLOPE_UP_05_2,
	SLOPE_UP_1,
	SLOPE_DOWN_1,
	SLOPE_DOWN_05_1,
	SLOPE_DOWN_05_2,

	GROUND_LEFT,
	GROUND_MID,
	GROUND_RIGHT,
	GROUND_SLOPE_UP_05_1,
	GROUND_SLOPE_UP_05_2,
	GROUND_SLOPE_UP_1,
	GROUND_SLOPE_DOWN_1,
	GROUND_SLOPE_DOWN_05_1,
	GROUND_SLOPE_DOWN_05_2,

	GROUND_BOTTOM_LEFT,
	GROUND_BOTTOM_MID,
	GROUND_BOTTOM_RIGHT

};

class TerrainCell: public Polygon {
public:
	TerrainCell(
		GRRLIB_texImg* tileSet,
		const int width,
		const int height);
	CellType getType() const;
	float getY1() const;
	float getAbsoluteY1() const;
	float getY2() const;
	float getAbsoluteY2() const;
	float getAngle() const;
	void setType(const CellType);
	float getAbsoluteHeight(const float x) const;
	void setYs(const int _y1, const int _y2);
	void setIndexCoords(const int colIndex, const int rowIndex);
	//void draw() const;
};

}

#endif
