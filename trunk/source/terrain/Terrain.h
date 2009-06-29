#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "../ShootMii.h"

namespace shootmii {

const int AMPLITUDE_TERRAIN(20); // les variations du terrains peuvent recouvrir 50% de l'�cran
const int CENTER_TERRAIN(70); // centr� � 70% de l'�cran en partant du haut
const int VARIATION_TERRAIN(2); // une pente entre -VARIATION_TERRAIN et +VARIATION_TERRAIN

class Terrain {
private:
	int size;
	int rows;
	int cols;
	vector<vector<TerrainCell> > grille; // Vecteur de lignes
public:
	// Constructeur
	Terrain(const int _size = 10, const int _rows = 10, const int _cols = 10);
	// Accesseurs
	int getSize() const;
	int getRows() const;
	int getCols() const;
	const vector<vector<TerrainCell> > & getGrille() const;
	CellType getCellType(const int rowIndex, const int colIndex) const;
	bool contains(float screenX, float screenY) const;
	// M�thodes
	void draw() const;
	void generate();
};

}

#endif /*TERRAIN_H_*/
