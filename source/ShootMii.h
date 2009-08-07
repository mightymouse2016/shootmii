#ifndef SHOOTMII_H_
#define SHOOTMII_H_

using namespace std;

namespace shootmii {

// Math
class Timer;
class Coordinates;
class Function;
class Affine;
class Sinus;
class Cosinus;
class PolyDeg2;
class Polygon;
class Rectangle;

// Tools
class Console;
class ImageBank;
class Animation;

// World
class TerrainCell;
class Wind;
class Cloud;
class Sun;
class Terrain;
class World;

// Game
class Bonus;
class Cannon;
class Ammo;
class CannonBall;
class HomingMissile;
class Player;
class Manager;
class ScoreManager;

// Screens
class Screen;
class GameScreen;
class TitleScreen;

// Main
class App;

}

// GRRLib
#include "../../../GRRLib4.0.0/GRRLIB/GRRLIB/GRRLIB.h"
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>

// Bibliothèques standard
#include <pair>
#include <list>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>

// Images
#include "gfx/sun.h"
#include "gfx/tank.h"
#include "gfx/cannon.h"
#include "gfx/ammo_1.h"
#include "gfx/ammo_2.h"
#include "gfx/homing_1.h"
#include "gfx/homing_2.h"
#include "gfx/tile_set.h"
#include "gfx/bonus_life.h"
#include "gfx/heat_jauge.h"
#include "gfx/life_jauge.h"
#include "gfx/crosshair_1.h"
#include "gfx/crosshair_2.h"
#include "gfx/score_panel.h"
#include "gfx/title_screen.h"
#include "gfx/bonus_homing.h"
#include "gfx/smoke_sprites.h"
#include "gfx/strength_jauge.h"
#include "gfx/strength_sprites.h"
#include "gfx/background_cloud.h"
#include "gfx/foreground_cloud.h"
#include "gfx/homing_smoke_sprites.h"
#include "gfx/cannonball_hit_explosion.h"
#include "gfx/cannonball_air_explosion.h"
#include "gfx/cannonball_ground_explosion.h"


// Fonts
#include "gfx/font1.h"
#include "gfx/font2.h"
#include "gfx/font3.h"
#include "gfx/font4.h"
#include "gfx/font_fun.h"
#include "gfx/font_score.h"
#include "gfx/font_console.h"
#include "gfx/font_military.h"


// Math
#include "tools/Timer.h"
#include "tools/Coordinates.h"
#include "tools/Function.h"
#include "tools/Affine.h"
#include "tools/Sinus.h"
#include "tools/Cosinus.h"
#include "tools/PolyDeg2.h"
#include "tools/Polygon.h"
#include "tools/Rectangle.h"

// Tools
#include "tools/Colors.h"
#include "tools/Tools.h"
#include "tools/Console.h"
#include "tools/ImageBank.h"
#include "tools/Animation.h"

// World
#include "terrain/World.h"
#include "terrain/TerrainCell.h"
#include "terrain/Wind.h"
#include "terrain/Cloud.h"
#include "terrain/Terrain.h"
#include "terrain/Sun.h"

// Game
#include "game/Bonus.h"
#include "game/Cannon.h"
#include "game/Ammo.h"
#include "game/CannonBall.h"
#include "game/HomingMissile.h"
#include "game/Player.h"
#include "game/Manager.h"
#include "game/ScoreManager.h"

// Screens
#include "screens/Screen.h"
#include "screens/GameScreen.h"
#include "screens/TitleScreen.h"

// Main
#include "App.h"

#endif /*SHOOTMII_H_*/
