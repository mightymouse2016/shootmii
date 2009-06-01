#include "../ShootMii.h"

namespace shootmii {

  Terrain::Terrain(const int _size, const int _rows, const int _cols) :
    size(_size), rows(_rows), cols(_cols), grille(vector<vector<TerrainCell> >(
        _rows, vector<TerrainCell>(_cols, TerrainCell((CellType)0, 0, 0)))) {
    // Initialisation des coordonnées contenues dans les Cell
    for (int i=0; i<rows; i++)
      for (int j=0; j<cols; j++)
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
    for (int i=0; i<rows; i++)
      for (int j=0; j<cols; j++)
        grille[i][j].draw();
  }

  void Terrain::generate() {
    srand(time(NULL)); // Pour ne pas avoir toujours la même génération

    int highLimit = (rows-1)/2 + (rows-1)/AMPLITUDE_DEPART;
    int lowLimit = (rows-1)/2 - (rows-1)/AMPLITUDE_DEPART;

    // Calcul de la hauteur initiale (à la colonne -1)
    int height = rand()*(rows-1)*2/(AMPLITUDE_DEPART*RAND_MAX)+(rows-1)/2; // Entre 1/4rows et 3/4rows

    // Pour chaque colonne ...
    for (int i=0; i<cols; i++) {

      // Déplacement compris entre -AMPLITUDE et +AMPLITUDE par rapport a la colonne précédente
      height += rand()%(2*AMPLITUDE+1) - AMPLITUDE;

      if (height > highLimit)
        height = highLimit; // Si on dépasse en haut
      if (height < lowLimit)
        height = lowLimit; // Si on dépasse en bas

      // On met de la terre

      for (int j=0; j<height; j++)
        grille[j][i].setType(SKY);
      grille[height][i].setType(GRASS);
      for (int j=height+1; j<rows; j++)
        grille[j][i].setType(GROUND);

    }
  }

  bool Terrain::contains(float screenX, float screenY) const {
    int colIndex = int(screenX)/CELL_SIZE;
    int rowIndex = int(screenY)/CELL_SIZE;
    if (colIndex < 0 || colIndex > cols || rowIndex < 0 || rowIndex > rows) return false;
    return true;
  }
}
