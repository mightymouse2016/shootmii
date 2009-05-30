#ifndef TERRAINCELL_H_
#define TERRAINCELL_H_

#include "../ShootMii.h"

#define N_CELLTYPE 2 // Nombre de type de cellules, pour l'instant terre ou ciel
#define AMPLITUDE_DEPART 4 // case initiale entre 1/2-1/4 et 1/2+1/4
#define AMPLITUDE 2 // une pente entre -AMPLITUDE et +AMPLITUDE

namespace shootmii{

    enum CellType {SKY, GROUND, GRASS};

    class TerrainCell : public Cell{
        private:
          CellType type;
        public:
            //Constructeur
          TerrainCell(const CellType, const int, const int);
          // Accesseurs
          CellType getType() const;
          void setType(const CellType);
          // Méthodes
          void draw() const;
    };

}

#endif
