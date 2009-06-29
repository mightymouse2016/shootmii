#include "../ShootMii.h"

namespace shootmii {

Terrain::Terrain(const int _size, const int _rows, const int _cols) :
	size(_size), rows(_rows), cols(_cols), grille(
			vector<vector<TerrainCell> > (_rows, vector<TerrainCell> (_cols,
					TerrainCell((CellType) 0, 0, 0)))) {
	// Initialisation des coordonnées contenues dans les Cell
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			grille[i][j].setCoords(i, j);
}

int Terrain::getSize() const {
	return size;
}

int Terrain::getRows() const {
	return rows;
}

int Terrain::getCols() const {
	return cols;
}

CellType Terrain::getCellType(const int rowIndex, const int colIndex) const {
	return getGrille()[rowIndex][colIndex].getType();
}

const vector<vector<TerrainCell> > & Terrain::getGrille() const {
	return grille;
}

void Terrain::draw() const {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			grille[i][j].draw();
}

void Terrain::generate() {
	srand(time(NULL)); // Pour ne pas avoir toujours la même génération

	int highLimit = rows*(CENTER_TERRAIN-AMPLITUDE_TERRAIN/2)/100;
	int lowLimit = rows*(CENTER_TERRAIN+AMPLITUDE_TERRAIN/2)/100;

	// Calcul de la hauteur initiale (à la colonne -1)
	int height = rand()%(lowLimit-highLimit)+(lowLimit+highLimit)/2;

	// Pour chaque colonne ...
	for (int i=0;i<cols;i++){

		// Déplacement compris entre -AMPLITUDE et +AMPLITUDE par rapport a la colonne précédente
		height += rand() % (2* VARIATION_TERRAIN + 1) - VARIATION_TERRAIN;

		if (height < highLimit) height = highLimit; // Si on dépasse en haut
		if (height > lowLimit) height = lowLimit; // Si on dépasse en bas

		// On met de la terre

		for (int j = 0; j < height; j++) grille[j][i].setType(SKY);
		grille[height][i].setType(GRASS);
		for (int j = height + 1; j < rows; j++) grille[j][i].setType(GROUND);

	}
}

bool Terrain::contains(float screenX, float screenY) const {
	if (screenX < -CELL_SIZE || screenX > CELL_SIZE * cols || screenY
			< -CELL_SIZE || screenY > CELL_SIZE * rows)
		return false;
	return true;
}
}
