#include "../ShootMii.h"

namespace shootmii {

ImageBank::ImageBank() {

}

ImageBank::~ImageBank() {
	for(int i=0;i<NUMBER_OF_TEXTURES;i++) GRRLIB_FreeTexture(allTextures[i]);
}

void ImageBank::init() {
	allTextures.reserve(NUMBER_OF_TEXTURES);
	allTextures[TXT_SUN] = GRRLIB_LoadTexture(sun);
	allTextures[TXT_TANK] = GRRLIB_LoadTexture(tank);
	allTextures[TXT_AMMO1] = GRRLIB_LoadTexture(ammo_1);
	allTextures[TXT_AMMO2] = GRRLIB_LoadTexture(ammo_2);
	allTextures[TXT_CANNON] = GRRLIB_LoadTexture(cannon);
	allTextures[TXT_GHOST1] = GRRLIB_LoadTexture(ghost_1);
	allTextures[TXT_GHOST2] = GRRLIB_LoadTexture(ghost_2);
	allTextures[TXT_HOMING1] = GRRLIB_LoadTexture(homing_1);
	allTextures[TXT_HOMING2] = GRRLIB_LoadTexture(homing_2);
	allTextures[TXT_GUIDED1] = GRRLIB_LoadTexture(guided_1);
	allTextures[TXT_GUIDED2] = GRRLIB_LoadTexture(guided_2);
	allTextures[TXT_TERRAIN] = GRRLIB_LoadTexture(tile_set);
	allTextures[TXT_BUTTON_1] = GRRLIB_LoadTexture(button_1);
	allTextures[TXT_SMOKE] = GRRLIB_LoadTexture(smoke_sprites);
	allTextures[TXT_BONUS_LIFE] = GRRLIB_LoadTexture(bonus_life);
	allTextures[TXT_LIFE_JAUGE] = GRRLIB_LoadTexture(life_jauge);
	allTextures[TXT_HEAT_JAUGE] = GRRLIB_LoadTexture(heat_jauge);
	allTextures[TXT_WIND_JAUGE] = GRRLIB_LoadTexture(wind_jauge);
	allTextures[TXT_CROSSHAIR1] = GRRLIB_LoadTexture(crosshair_1);
	allTextures[TXT_CROSSHAIR2] = GRRLIB_LoadTexture(crosshair_2);
	allTextures[TXT_FURY_JAUGE1] = GRRLIB_LoadTexture(fury_jauge_1);
	allTextures[TXT_FURY_JAUGE2] = GRRLIB_LoadTexture(fury_jauge_2);
	allTextures[TXT_SCORE_PANEL] = GRRLIB_LoadTexture(score_panel);
	allTextures[TXT_BONUS_HOMING] = GRRLIB_LoadTexture(bonus_homing);
	allTextures[TXT_BONUS_POISON] = GRRLIB_LoadTexture(bonus_poison);
	allTextures[TXT_BONUS_GUIDED] = GRRLIB_LoadTexture(bonus_guided);
	allTextures[TXT_BONUS_POTION] = GRRLIB_LoadTexture(bonus_potion);
	allTextures[TXT_TITLE_SCREEN] = GRRLIB_LoadTexture(title_screen);
	allTextures[TXT_BG_CLOUD] = GRRLIB_LoadTexture(background_cloud);
	allTextures[TXT_FG_CLOUD] = GRRLIB_LoadTexture(foreground_cloud);
	allTextures[TXT_STRENGTH_JAUGE] = GRRLIB_LoadTexture(strength_jauge);
	allTextures[TXT_HOMING_SMOKE] = GRRLIB_LoadTexture(homing_smoke_sprites);
	allTextures[TXT_STRENGTH_SPRITES] = GRRLIB_LoadTexture(strength_sprites);
	allTextures[TXT_ALPHA_FURY_JAUGE1] = GRRLIB_LoadTexture(alpha_fury_jauge_1);
	allTextures[TXT_ALPHA_FURY_JAUGE2] = GRRLIB_LoadTexture(alpha_fury_jauge_2);
	allTextures[TXT_CANNONBALL_AIR_EXPLOSION] = GRRLIB_LoadTexture(cannonball_air_explosion);
	allTextures[TXT_CANNONBALL_HIT_EXPLOSION] = GRRLIB_LoadTexture(cannonball_hit_explosion);
	allTextures[TXT_CANNONBALL_GROUND_EXPLOSION] = GRRLIB_LoadTexture(cannonball_ground_explosion);
}

GRRLIB_texImg* ImageBank::get(ImageTexture textureName) {
	return allTextures[textureName];
}

}
