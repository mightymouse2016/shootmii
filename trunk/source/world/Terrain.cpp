#include "../tools/ImageBank.h"
#include "../App.h"
#include "Terrain.h"

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
		grille(std::vector<std::vector<TerrainCell> > (rows,std::vector<TerrainCell> (cols,TerrainCell(tileSet,cellWidth,cellHeight))))
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

float Terrain::getHeight(const int screenX) const {
	int row;
	int col = screenX/cellWidth;
	if (screenX < 0 || col >= cols) return cellHeight*rows;
	for(row=0;getType(col,row)==EMPTY;row++);
	return grille[row][col].getAbsoluteHeight(screenX);
}

float Terrain::getAngle(const float screenX) const{
	int x1, x = screenX, col = x/cellWidth;
	float alpha1, alpha2;
	if (x%cellWidth > cellWidth/2){
		if (col < 0 || col+1 >= cols) return 0;
		alpha1 = getGround(col).getAngle();
		alpha2 = getGround(col+1).getAngle();
		x1 = col*cellWidth+cellWidth/2;
	} else {
		if (col-1 < 0 || col >= cols) return 0;
		alpha1 = getGround(col-1).getAngle();
		alpha2 = getGround(col).getAngle();
		x1 = col*cellWidth-cellWidth/2;
	}
	return (alpha2-alpha1)*(screenX-x1)/cellWidth + alpha1;
}

const TerrainCell& Terrain::getGround(const int colIndex) const {
  int rowIndex;
  for(rowIndex = 0; getType(colIndex, rowIndex) == EMPTY; rowIndex++);
  return grille[rowIndex][colIndex];
}

CellType Terrain::getType(const int colIndex, const int rowIndex) const {
	return grille[rowIndex][colIndex].getType();
}

const std::vector<std::vector<TerrainCell> > & Terrain::getGrille() const {
	return grille;
}

void Terrain::addToDrawManager(){
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			grille[i][j].addToDrawManager();
}

void Terrain::generate() {
	// Remise à zero(EMPTY) du terrain
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			grille[i][j].setType(EMPTY);

	// Initialisation
	int highLimit = rows*TERRAIN_UP_LIMIT/100;
	int lowLimit = rows*TERRAIN_DOWN_LIMIT/100;
	int height = rand()%(lowLimit-highLimit)+highLimit;

	// Première Colonne
	grille[height][0].setType(GRASS_LEFT);
	for(int i=height+1;i<rows-1;i++) grille[i][0].setType(GROUND_LEFT);
	grille[rows-1][0].setType(GROUND_BOTTOM_LEFT);

	// Tout en bas
	for (int i=1;i<cols-1;i++) grille[rows-1][i].setType(GROUND_BOTTOM_MID);

	for (int i=1,variation;i<cols-1;i++){

		if (i == cols-2){
			if (height == highLimit) {
				if (rand()%100 > 50) variation = -VARIATION_TERRAIN;
				else variation = 0;
			}
			else if (height == lowLimit) {
				if (rand()%100 > 50) variation = VARIATION_TERRAIN;
				else variation = 0;
			}
			else variation = VARIATION_TERRAIN*(rand() % (VARIATION_TERRAIN + 1) - 1);
		}
		else {
			if (height == highLimit) variation = -rand()%(VARIATION_TERRAIN + 1);
			else if (height == lowLimit) variation = rand()%(VARIATION_TERRAIN + 1);
			else variation = rand() % (2* VARIATION_TERRAIN + 1) - VARIATION_TERRAIN;
		}

		switch (variation) {
		case 2:
			height--;
			grille[height][i].setType(SLOPE_UP_1);
			grille[height+1][i].setType(GROUND_SLOPE_UP_1);
			for (int j=height+2;j<rows-1;j++) grille[j][i].setType(GROUND_MID);
			break;
		case 1:
			height--;
			grille[height][i].setType(SLOPE_UP_05_1);
			grille[height+1][i].setType(GROUND_SLOPE_UP_05_1);
			i++;
			grille[height][i].setType(SLOPE_UP_05_2);
			grille[height+1][i].setType(GROUND_SLOPE_UP_05_2);
			for (int j=height+2;j<rows-1;j++) grille[j][i-1].setType(GROUND_MID);
			for (int j=height+2;j<rows-1;j++) grille[j][i].setType(GROUND_MID);
			break;
		case 0:
			grille[height][i].setType(GRASS_MID);
			for (int j=height+1;j<rows-1;j++) grille[j][i].setType(GROUND_MID);
			break;
		case -1:
			grille[height][i].setType(SLOPE_DOWN_05_1);
			grille[height+1][i].setType(GROUND_SLOPE_DOWN_05_1);
			i++;
			grille[height][i].setType(SLOPE_DOWN_05_2);
			grille[height+1][i].setType(GROUND_SLOPE_DOWN_05_2);
			height++;
			for (int j=height+1;j<rows-1;j++) grille[j][i-1].setType(GROUND_MID);
			for (int j=height+1;j<rows-1;j++) grille[j][i].setType(GROUND_MID);
			break;
		case -2:
			grille[height][i].setType(SLOPE_DOWN_1);
			grille[height+1][i].setType(GROUND_SLOPE_DOWN_1);
			height++;
			for (int j=height+1;j<rows-1;j++) grille[j][i].setType(GROUND_MID);
			break;
		}
	}

	// Dernière Colonne
	grille[height][cols-1].setType(GRASS_RIGHT);
	for(int i=height+1;i<rows-1;i++) grille[i][cols-1].setType(GROUND_RIGHT);
	grille[rows-1][cols-1].setType(GROUND_BOTTOM_RIGHT);

}

bool Terrain::contains(float screenX, float screenY) const {
	if (screenX < 0) return false;
	else if (screenX >= cellWidth*cols) return false;
	else if (screenY < 0) return false;
	else if (screenY >= cellHeight*rows) return false;
	return true;
}

}
