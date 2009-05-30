#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "../ShootMii.h"

namespace shootmii{

    class Terrain{
    private:
        int size;
        int rows;
        int cols;
        vector<vector<TerrainCell> > grille; // Vecteur de lignes
    public:
      // Constructeur
      Terrain(const int _size=10,const int _rows=10, const int _cols=10);
      // Accesseurs
      int getSize() const;
      int getRows() const;
      int getCols() const;
      const vector<vector<TerrainCell> > & getGrille() const;
      CellType getCellType(const int rowIndex, const int colIndex) const;
      // Méthodes
      void draw() const;
      void generate();
    };

}

#endif /*TERRAIN_H_*/
