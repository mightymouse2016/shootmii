#ifndef SHOOTMII_H_
#define SHOOTMII_H_

using namespace std;

namespace shootmii {

const float PI(3.14159265358979323846264338327950288419716939937510);

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
class GuidedMissile;
class Jauge;
class Player;
class Manager;
class DrawManager;
class ScoreManager;
class JaugeManager;

// Screens
class Screen;
class GameScreen;
class TitleScreen;

// Main
class App;

}

#include "../../../grrlib/GRRLIB/GRRLIB/GRRLIB.h"
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>

// Bibliothèques standard
#include <set>
#include <list>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <utility> // Pour utiliser des pair<T1,T2>
#include <cstdlib>
#include <mp3player.h>
#include "asndlib.h"

// Images
#include "gfx/sun.h"
#include "gfx/tank.h"
#include "gfx/cannon.h"
#include "gfx/ammo_1.h"
#include "gfx/ammo_2.h"
#include "gfx/guided_1.h"
#include "gfx/guided_2.h"
#include "gfx/homing_1.h"
#include "gfx/homing_2.h"
#include "gfx/tile_set.h"
#include "gfx/bonus_life.h"
#include "gfx/heat_jauge.h"
#include "gfx/life_jauge.h"
#include "gfx/wind_jauge.h"
#include "gfx/crosshair_1.h"
#include "gfx/crosshair_2.h"
#include "gfx/score_panel.h"
#include "gfx/fury_jauge_1.h"
#include "gfx/fury_jauge_2.h"
#include "gfx/title_screen.h"
#include "gfx/bonus_homing.h"
#include "gfx/bonus_guided.h"
#include "gfx/bonus_poison.h"
#include "gfx/bonus_potion.h"
#include "gfx/smoke_sprites.h"
#include "gfx/strength_jauge.h"
#include "gfx/strength_sprites.h"
#include "gfx/background_cloud.h"
#include "gfx/foreground_cloud.h"
#include "gfx/alpha_fury_jauge_1.h"
#include "gfx/alpha_fury_jauge_2.h"
#include "gfx/homing_smoke_sprites.h"
#include "gfx/cannonball_hit_explosion.h"
#include "gfx/cannonball_air_explosion.h"
#include "gfx/cannonball_ground_explosion.h"

// Sons
//#include "snd/Artillaryexp.h"

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
#include "math/Timer.h"
#include "math/Coordinates.h"
#include "math/Function.h"
#include "math/Affine.h"
#include "math/Sinus.h"
#include "math/Cosinus.h"
#include "math/PolyDeg2.h"
#include "math/Polygon.h"
#include "math/Rectangle.h"

// Tools
#include "tools/Colors.h"
#include "tools/Tools.h"
#include "tools/Console.h"
#include "tools/ImageBank.h"
#include "tools/Animation.h"

// World
#include "world/World.h"
#include "world/TerrainCell.h"
#include "world/Wind.h"
#include "world/Cloud.h"
#include "world/Terrain.h"
#include "world/Sun.h"

// Game
#include "game/Bonus.h"
#include "game/Cannon.h"
#include "game/Ammo.h"
#include "game/CannonBall.h"
#include "game/HomingMissile.h"
#include "game/GuidedMissile.h"
#include "game/Player.h"
#include "game/Jauge.h"
#include "game/Manager.h"
#include "game/DrawManager.h"
#include "game/ScoreManager.h"
#include "game/JaugeManager.h"

// Screens
#include "screens/Screen.h"
#include "screens/GameScreen.h"
#include "screens/TitleScreen.h"

// Main
#include "App.h"

#endif /*SHOOTMII_H_*/
