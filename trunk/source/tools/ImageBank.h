#ifndef IMAGEBANK_H_
#define IMAGEBANK_H_

#include <vector>
#include "GRRLIB.h"

namespace shootmii {

enum ImageTexture {
	TXT_SUN,
	TXT_DOCK,
	TXT_TANK,
	TXT_AMMO1,
	TXT_AMMO2,
	TXT_SMOKE,
	TXT_SHIELD,
	TXT_CANNON,
	TXT_GHOST1,
	TXT_GHOST2,
	TXT_TERRAIN,
	TXT_HOMING1,
	TXT_HOMING2,
	TXT_GUIDED1,
	TXT_GUIDED2,
	TXT_BG_CLOUD,
	TXT_FG_CLOUD,
	TXT_BUTTON_1,
	TXT_POINTER_1,
	TXT_POINTER_2,
	TXT_POINTER_3,
	TXT_POINTER_4,
	TXT_BONUS_LIFE,
	TXT_LIFE_JAUGE,
	TXT_HEAT_JAUGE,
	TXT_WIND_JAUGE,
	TXT_CROSSHAIR1,
	TXT_CROSSHAIR2,
	TXT_FURY_JAUGE1,
	TXT_FURY_JAUGE2,
	TXT_LASER_JAUGE,
	TXT_SCORE_PANEL,
	TXT_BONUS_SHIELD,
	TXT_SHIELD_JAUGE,
	TXT_TITLE_SCREEN,
	TXT_BONUS_HOMING,
	TXT_BONUS_POISON,
	TXT_BONUS_POTION,
	TXT_BONUS_GUIDED,
	TXT_HOMING_SMOKE,
	TXT_STRENGTH_JAUGE,
	TXT_BONUS_CROSS_HAIR,
	TXT_STRENGTH_SPRITES,
	TXT_ALPHA_FURY_JAUGE1,
	TXT_ALPHA_FURY_JAUGE2,
	TXT_CANNONBALL_AIR_EXPLOSION,
	TXT_CANNONBALL_HIT_EXPLOSION,
	TXT_CANNONBALL_GROUND_EXPLOSION,

	NUMBER_OF_TEXTURES // Utilis� comme condition d'arr�t des boucles
};

class ImageBank {
private:
	std::vector<GRRLIB_texImg*> allTextures;
public:
	ImageBank();
	virtual ~ImageBank();
	GRRLIB_texImg* get(ImageTexture textureName);
	void init();
};

}

#endif /*IMAGEBANK_H_*/
