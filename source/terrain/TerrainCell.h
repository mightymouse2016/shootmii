#ifndef TERRAINCELL_H_
#define TERRAINCELL_H_

#include "../ShootMii.h"

const int N_CELLTYPE(2); // Nombre de type de cellules, pour l'instant terre ou ciel

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
