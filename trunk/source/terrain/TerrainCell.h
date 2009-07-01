#ifndef TERRAINCELL_H_
#define TERRAINCELL_H_

#include "../ShootMii.h"

const int N_CELLTYPE(2); // Nombre de type de cellules, pour l'instant terre ou ciel

namespace shootmii {

enum CellType {
	SKY, GROUND, GRASS
};

class TerrainCell: public Cell {
private:
	CellType type;
public:
	TerrainCell(const CellType _type, const int _colIndex, const int _rowIndex);
	CellType getType() const;
	void setType(const CellType);
	void draw() const;
};

}

#endif
