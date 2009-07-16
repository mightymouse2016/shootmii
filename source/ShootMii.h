#ifndef SHOOTMII_H_
#define SHOOTMII_H_

using namespace std;

namespace shootmii {
  class App;
  class Screen;
  class TitleScreen;
  class GameScreen;
  class ScoreManager;
  class Manager;
  class Player;
  class Polygon;
  class Cell;
  class TerrainCell;
  class Wind;
  class Cloud;
  class Terrain;
  class World;
  class Wheels;
  class Cannon;
  class Tank;
  class MovementHandler;
  class Ammo;
  class CannonBall;
  class Affine;
  class PolyDeg2;
  class Function;
  class Console;
  class Coordinates;
  class ImageBank;
}

// GRRLib
#include "../../../GRRLib4.0.0/GRRLIB/GRRLIB/GRRLIB.h"
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>
// Bibliothèques standard
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <list>
#include <time.h>
#include <math.h>

// Images
#include "gfx/ammo_1.h"
#include "gfx/ammo_2.h"
#include "gfx/crosshair_1.h"
#include "gfx/crosshair_2.h"
#include "gfx/cannon.h"
#include "gfx/tank.h"
#include "gfx/score_panel.h"
#include "gfx/title_screen.h"
#include "gfx/heat_jauge.h"
#include "gfx/life_jauge.h"
#include "gfx/strength_jauge.h"
#include "gfx/strength_sprites.h"
#include "gfx/background_cloud.h"
#include "gfx/foreground_cloud.h"
#include "gfx/tile_set.h"
#include "gfx/cannonball_hit_explosion.h"
#include "gfx/cannonball_air_explosion.h"
#include "gfx/cannonball_ground_explosion.h"

// Fontes
#include "gfx/font1.h"
#include "gfx/font2.h"
#include "gfx/font3.h"
#include "gfx/font4.h"
#include "gfx/font_console.h"
#include "gfx/font_fun.h"
#include "gfx/font_military.h"
#include "gfx/font_score.h"

// Maths
#include "tools/Coordinates.h"
#include "tools/Function.h"
#include "tools/Affine.h"
#include "tools/PolyDeg2.h"
#include "tools/Polygon.h"

// Tools
#include "tools/Colors.h"
#include "tools/Tools.h"
#include "tools/Console.h"
#include "tools/ImageBank.h"

// Terrain
#include "terrain/Cell.h"
#include "terrain/TerrainCell.h"
#include "terrain/Wind.h"
#include "terrain/Cloud.h"
#include "terrain/Terrain.h"
#include "terrain/World.h"

// Game
#include "game/Explosion.h"
#include "game/Cannon.h"
#include "game/Ammo.h"
#include "game/CannonBall.h"
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
