#include "../ShootMii.h"

namespace shootmii {

Terrain::Terrain(
	const int _rows,
	const int _cols,
	const int _cellWidth,
	const int _cellHeight) :
		rows(_rows),
		cols(_cols),
		cellWidth(_cellWidth),
		cellHeight(_cellHeight),
	  tileSet(App::imageBank->get(TXT_TERRAIN)),
		grille(vector<vector<TerrainCell> > (rows,vector<TerrainCell> (cols,TerrainCell(tileSet,cellWidth,cellHeight))))
{
	// Initialisation des coordonnées contenues dans les Cell
	GRRLIB_InitTileSet(tileSet, cellWidth, cellHeight, 0);
	for (int i=0;i<rows;i++)
		for (int j=0;j<cols;j++)
			grille[i][j].setIndexCoords(j,i);
}

int Terrain::getRows() const {
	return rows;
}

int Terrain::getCols() const {
	return cols;
}

int Terrain::getCellWidth() const{
	return cellWidth;
}

int Terrain::getCellHeight() const{
  return cellHeight;
}

int Terrain::getHeight(const int screenX) const {
	int row;
	int col = screenX/cellWidth;
	int relativeX = screenX%cellWidth;
	for(row=0;getType(col,row)==EMPTY;row++);
	return (row+1)*cellHeight - grille[row][screenX/cellWidth].getRelativeHeight(relativeX);
}

TerrainCell Terrain::getGround(const int colIndex) const {
  int rowIndex;
  for(rowIndex = 0; getType(colIndex, rowIndex) == EMPTY; rowIndex++);
  return grille[rowIndex][colIndex];
}

CellType Terrain::getType(const int colIndex, const int rowIndex) const {
	return grille[rowIndex][colIndex].getType();
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

  // Remise à zero(EMPTY) du terrain
  for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
        grille[i][j].setType(EMPTY);

	// Initialisation
  int highLimit = rows*(CENTER_TERRAIN-AMPLITUDE_TERRAIN/2)/100;
  int lowLimit = rows*(CENTER_TERRAIN+AMPLITUDE_TERRAIN/2)/100;
	int height = rand()%(lowLimit-highLimit)+(lowLimit+highLimit)/2;

	// Première Colonne
	grille[height][0].setCell(GRASS_LEFT,1,1);
	for(int i=height+1;i<rows-1;i++) grille[i][0].setType(GROUND_LEFT);
	grille[rows-1][0].setType(GROUND_BOTTOM_LEFT);

	for (int i=1,variation;i<cols-1;i++){

		if (height == highLimit) variation = -rand()%(VARIATION_TERRAIN + 1);
		else if (height == lowLimit) variation = rand()%(VARIATION_TERRAIN + 1);
		else variation = rand() % (2* VARIATION_TERRAIN + 1) - VARIATION_TERRAIN;

		switch (variation) {
		  case 2:
			height--;
			grille[height][i].setCell(SLOPE_UP_1, 0, 1);
			grille[height+1][i].setType(GROUND_SLOPE_UP_1);
			for (int j=height+2;j<rows-1;j++) grille[j][i].setType(GROUND_MID);
			break;
		  case 1:
			height--;
			grille[height][i].setCell(SLOPE_UP_05_1, 0, 0.5);
			grille[height+1][i].setType(GROUND_SLOPE_UP_05_1);
			i++;
			grille[height][i].setCell(SLOPE_UP_05_2, 0.5, 1);
			grille[height+1][i].setType(GROUND_SLOPE_UP_05_2);
			for (int j=height+2;j<rows-1;j++) grille[j][i-1].setType(GROUND_MID);
			for (int j=height+2;j<rows-1;j++) grille[j][i].setType(GROUND_MID);
			break;
		  case 0:
			grille[height][i].setCell(GRASS_MID, 1, 1);
			for (int j=height+1;j<rows-1;j++) grille[j][i].setType(GROUND_MID);
			break;
		  case -1:
			grille[height][i].setCell(SLOPE_DOWN_05_1, 1, 0.5);
			grille[height+1][i].setType(GROUND_SLOPE_DOWN_05_1);
			i++;
			grille[height][i].setCell(SLOPE_DOWN_05_2, 0.5, 0);
			grille[height+1][i].setType(GROUND_SLOPE_DOWN_05_2);
			height++;
			for (int j=height+1;j<rows-1;j++) grille[j][i-1].setType(GROUND_MID);
			for (int j=height+1;j<rows-1;j++) grille[j][i].setType(GROUND_MID);
			break;
		  case -2:
			grille[height][i].setCell(SLOPE_DOWN_1, 1, 0);
			grille[height+1][i].setType(GROUND_SLOPE_DOWN_1);
			height++;
			for (int j=height+1;j<rows-1;j++) grille[j][i].setType(GROUND_MID);
			break;
		}
	}

	// Tout en bas
	for (int i=1;i<cols;i++) grille[rows-1][i].setType(GROUND_BOTTOM_MID);

	// Dernière Colonne
	grille[height][cols-1].setCell(GRASS_RIGHT, 1, 1);
	for(int i=height+1;i<rows-1;i++) grille[i][cols-1].setType(GROUND_RIGHT);
	grille[rows-1][cols-1].setType(GROUND_BOTTOM_RIGHT);

}

bool Terrain::contains(float screenX, float screenY) const {
	if (screenX < 0) return false;
	else if (screenX > cellWidth*cols-1) return false;
	else if (screenY < 0) return false;
	else if (screenY > cellHeight*rows-1) return false;
	return true;
}

}
