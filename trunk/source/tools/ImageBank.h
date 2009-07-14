#ifndef IMAGEBANK_H_
#define IMAGEBANK_H_

#include "../ShootMii.h"

namespace shootmii {

  enum ImageTexture {
    TXT_TITLE_SCREEN,
    TXT_CANNON,
    TXT_AMMO1,
    TXT_AMMO2,
    TXT_CROSSHAIR1,
    TXT_CROSSHAIR2,
    TXT_TANK,
    TXT_SCORE_PANEL,
    TXT_LIFE_JAUGE,
    TXT_STRENGTH_JAUGE,
    TXT_STRENGTH_SPRITES,
    TXT_HEAT_JAUGE,
    TXT_TERRAIN,
    TXT_BG_CLOUD,
    TXT_FG_CLOUD,
    TXT_CANNONBALL_AIR_EXPLOSION,
    TXT_CANNONBALL_HIT_EXPLOSION,
    TXT_CANNONBALL_GROUND_EXPLOSION,

    NUMBER_OF_TEXTURES // Utilisé uniquement pour les boucle
  };

  class ImageBank {
    public:
      ImageBank();
      virtual ~ImageBank();
      GRRLIB_texImg* get(ImageTexture textureName);
      void init();
    private:
      vector<GRRLIB_texImg> allTextures;
  };

}

#endif /*IMAGEBANK_H_*/
