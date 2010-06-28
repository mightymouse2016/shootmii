#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "GRRLIB.h"
#include <vector>
#include "TerrainCell.h"

namespace shootmii {

const int TERRAIN_UP_LIMIT(50); // Les variations du terrain ne dépasseront pas 50% de la zone de jeu
const int TERRAIN_DOWN_LIMIT(95); // Les variations du terrain ne dépasseront pas 90% de la zone de jeu
const int VARIATION_TERRAIN(2); // une pente entre -VARIATION_TERRAIN et +VARIATION_TERRAIN

class Terrain {
private:
	int rows;
	int cols;
	int cellWidth;
	int cellHeight;
	GRRLIB_texImg* tileSet;
	std::vector<std::vector<TerrainCell> > grille; // Vecteur de lignes
public:
	Terrain(const int _rows, const int _cols, const int _cellWidth, const int _cellHeight);
	int getRows() const;
	int getCols() const;
	int getCellWidth() const;
	int getCellHeight() const;
	const std::vector<std::vector<TerrainCell> > & getGrille() const;
	CellType getType(const int colIndex, const int rowIndex) const;
	void addToDrawManager();
	void generate();
	bool contains(float screenX, float screenY) const;
	float getHeight(const int screenX) const;
	float getAngle(const float screenX) const;
	const TerrainCell& getGround(const int colIndex) const;
};

}

#endif /*TERRAIN_H_*/
