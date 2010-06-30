#include "../gfx/sun.h"
#include "../gfx/dock.h"
#include "../gfx/tank.h"
#include "../gfx/popup.h"
#include "../gfx/cannon.h"
#include "../gfx/ammo_1.h"
#include "../gfx/ammo_2.h"
#include "../gfx/shield.h"
#include "../gfx/ghost_1.h"
#include "../gfx/ghost_2.h"
#include "../gfx/guided_1.h"
#include "../gfx/guided_2.h"
#include "../gfx/homing_1.h"
#include "../gfx/homing_2.h"
#include "../gfx/button_1.h"
#include "../gfx/tile_set.h"
#include "../gfx/pointer_1.h"
#include "../gfx/pointer_2.h"
#include "../gfx/pointer_3.h"
#include "../gfx/pointer_4.h"
#include "../gfx/bonus_life.h"
#include "../gfx/heat_jauge.h"
#include "../gfx/life_jauge.h"
#include "../gfx/wind_jauge.h"
#include "../gfx/crosshair_1.h"
#include "../gfx/crosshair_2.h"
#include "../gfx/score_panel.h"
#include "../gfx/laser_jauge.h"
#include "../gfx/bonus_shield.h"
#include "../gfx/shield_jauge.h"
#include "../gfx/fury_jauge_1.h"
#include "../gfx/fury_jauge_2.h"
#include "../gfx/title_screen.h"
#include "../gfx/bonus_homing.h"
#include "../gfx/bonus_guided.h"
#include "../gfx/bonus_poison.h"
#include "../gfx/bonus_potion.h"
#include "../gfx/smoke_sprites.h"
#include "../gfx/strength_jauge.h"
#include "../gfx/bonus_cross_hair.h"
#include "../gfx/strength_sprites.h"
#include "../gfx/background_cloud.h"
#include "../gfx/foreground_cloud.h"
#include "../gfx/alpha_fury_jauge_1.h"
#include "../gfx/alpha_fury_jauge_2.h"
#include "../gfx/homing_smoke_sprites.h"
#include "../gfx/cannonball_hit_explosion.h"
#include "../gfx/cannonball_air_explosion.h"
#include "../gfx/cannonball_ground_explosion.h"

#include "ImageBank.h"

namespace shootmii {

ImageBank::ImageBank() {

}

ImageBank::~ImageBank() {
	for(int i=0;i<NUMBER_OF_TEXTURES;i++) GRRLIB_FreeTexture(allTextures[i]);
}

void ImageBank::init() {
	allTextures.reserve(NUMBER_OF_TEXTURES);
	allTextures[TXT_SUN] = GRRLIB_LoadTexture(sun);
	allTextures[TXT_DOCK] = GRRLIB_LoadTexture(dock);
	allTextures[TXT_TANK] = GRRLIB_LoadTexture(tank);
	allTextures[TXT_POPUP] = GRRLIB_LoadTexture(popup);
	allTextures[TXT_AMMO1] = GRRLIB_LoadTexture(ammo_1);
	allTextures[TXT_AMMO2] = GRRLIB_LoadTexture(ammo_2);
	allTextures[TXT_SHIELD] = GRRLIB_LoadTexture(shield);
	allTextures[TXT_CANNON] = GRRLIB_LoadTexture(cannon);
	allTextures[TXT_GHOST1] = GRRLIB_LoadTexture(ghost_1);
	allTextures[TXT_GHOST2] = GRRLIB_LoadTexture(ghost_2);
	allTextures[TXT_HOMING1] = GRRLIB_LoadTexture(homing_1);
	allTextures[TXT_HOMING2] = GRRLIB_LoadTexture(homing_2);
	allTextures[TXT_GUIDED1] = GRRLIB_LoadTexture(guided_1);
	allTextures[TXT_GUIDED2] = GRRLIB_LoadTexture(guided_2);
	allTextures[TXT_TERRAIN] = GRRLIB_LoadTexture(tile_set);
	allTextures[TXT_BUTTON_1] = GRRLIB_LoadTexture(button_1);
	allTextures[TXT_POINTER_1] = GRRLIB_LoadTexture(pointer_1);
	allTextures[TXT_POINTER_2] = GRRLIB_LoadTexture(pointer_2);
	allTextures[TXT_POINTER_3] = GRRLIB_LoadTexture(pointer_3);
	allTextures[TXT_POINTER_4] = GRRLIB_LoadTexture(pointer_4);
	allTextures[TXT_SMOKE] = GRRLIB_LoadTexture(smoke_sprites);
	allTextures[TXT_BONUS_LIFE] = GRRLIB_LoadTexture(bonus_life);
	allTextures[TXT_LIFE_JAUGE] = GRRLIB_LoadTexture(life_jauge);
	allTextures[TXT_HEAT_JAUGE] = GRRLIB_LoadTexture(heat_jauge);
	allTextures[TXT_WIND_JAUGE] = GRRLIB_LoadTexture(wind_jauge);
	allTextures[TXT_CROSSHAIR1] = GRRLIB_LoadTexture(crosshair_1);
	allTextures[TXT_CROSSHAIR2] = GRRLIB_LoadTexture(crosshair_2);
	allTextures[TXT_SCORE_PANEL] = GRRLIB_LoadTexture(score_panel);
	allTextures[TXT_LASER_JAUGE] = GRRLIB_LoadTexture(laser_jauge);
	allTextures[TXT_FURY_JAUGE1] = GRRLIB_LoadTexture(fury_jauge_1);
	allTextures[TXT_FURY_JAUGE2] = GRRLIB_LoadTexture(fury_jauge_2);
	allTextures[TXT_SHIELD_JAUGE] = GRRLIB_LoadTexture(shield_jauge);
	allTextures[TXT_BONUS_HOMING] = GRRLIB_LoadTexture(bonus_homing);
	allTextures[TXT_BONUS_POISON] = GRRLIB_LoadTexture(bonus_poison);
	allTextures[TXT_BONUS_GUIDED] = GRRLIB_LoadTexture(bonus_guided);
	allTextures[TXT_BONUS_POTION] = GRRLIB_LoadTexture(bonus_potion);
	allTextures[TXT_TITLE_SCREEN] = GRRLIB_LoadTexture(title_screen);
	allTextures[TXT_BG_CLOUD] = GRRLIB_LoadTexture(background_cloud);
	allTextures[TXT_FG_CLOUD] = GRRLIB_LoadTexture(foreground_cloud);
	allTextures[TXT_BONUS_SHIELD] = GRRLIB_LoadTexture(bonus_shield);
	allTextures[TXT_STRENGTH_JAUGE] = GRRLIB_LoadTexture(strength_jauge);
	allTextures[TXT_HOMING_SMOKE] = GRRLIB_LoadTexture(homing_smoke_sprites);
	allTextures[TXT_BONUS_CROSS_HAIR] = GRRLIB_LoadTexture(bonus_cross_hair);
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
