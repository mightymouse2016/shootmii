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
      int cellWidth;
      int cellHeight;
      GRRLIB_texImg* tileSet;
      vector<vector<TerrainCell> > grille; // Vecteur de lignes
    public:
      Terrain(const int _rows, const int _cols, const int _cellWidth, const int _cellHeight);
      int getRows() const;
      int getCols() const;
      int getCellWidth() const;
      int getCellHeight() const;
      const vector<vector<TerrainCell> > & getGrille() const;
      CellType getType(const int colIndex, const int rowIndex) const;
      void draw() const;
      void generate();
      bool contains(float screenX, float screenY) const;
      int getHeight(const int screenX) const;
      TerrainCell getGround(const int colIndex) const;
  };

}

#endif /*TERRAIN_H_*/
