#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "../ShootMii.h"

namespace shootmii {

const int AMPLITUDE_TERRAIN(20); // les variations du terrains peuvent recouvrir 50% de l'écran
const int CENTER_TERRAIN(70); // centré à 70% de l'écran en partant du haut
const int VARIATION_TERRAIN(2); // une pente entre -VARIATION_TERRAIN et +VARIATION_TERRAIN

class Terrain {
private:
	int rows;
	int cols;
	vector<vector<TerrainCell> > grille; // Vecteur de lignes
	GRRLIB_texImg tileSet;
public:
	Terrain(const int _rows, const int _cols);
	int getRows() const;
	int getCols() const;
	const vector<vector<TerrainCell> > & getGrille() const;
	CellType getType(const int colIndex, const int rowIndex) const;
	void draw() const;
	void generate();
	bool contains(float screenX, float screenY) const;
	int getHeight(const int screenX, const int rowIndex) const;
};

}

#endif /*TERRAIN_H_*/
