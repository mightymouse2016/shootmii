#ifndef TERRAINCELL_H_
#define TERRAINCELL_H_

#include "../ShootMii.h"

const int N_CELLTYPE(2); // Nombre de type de cellules, pour l'instant terre ou ciel

namespace shootmii {

enum CellType {
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
	GROUND_BOTTOM_RIGHT,
  EMPTY
};

class TerrainCell: public Cell {
private:
	CellType type;
	GRRLIB_texImg* tileSet;
	float y1;
	float y2;

public:
	TerrainCell(GRRLIB_texImg* _tileSet);
	CellType getType() const;
	int getY1() const;
	int getY2() const;
	void setType(const CellType);
	void setCell(const CellType, const float, const float);
	int getRelativeHeight(const int x) const;
	void draw() const;
};

}

#endif
