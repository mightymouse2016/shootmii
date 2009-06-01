#ifndef SHOOTMII_H_
#define SHOOTMII_H_

using namespace std;

namespace shootmii {
  class App;
  class Screen;
  class TitleScreen;
  class GameScreen;
  class ScorePanel;
  class Manager;
  class Player;
  class Cell;
  class TerrainCell;
  class Terrain;
  class Wheels;
  class Cannon;
  class Tank;
  class MovementHandler;
  class Ammo;
  class CannonBall;
  class Affine;
  class PolyDeg2;
  class Function;
}

// GRRLib
#include "../../../GRRLib4.0.0/GRRLIB/GRRLIB/GRRLIB.h"
#include <wiiuse/wpad.h>
// Bibliothèques standard
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <list>
#include <time.h>
#include <math.h>
// Images
#include "gfx/console.h"
#include "gfx/score_panel.h"
#include "gfx/title_screen.h"
#include "gfx/game_select_screen.h"
// Fontes
#include "gfx/font1.h"
#include "gfx/font2.h"
#include "gfx/font3.h"
#include "gfx/font4.h"
#include "gfx/font_fun.h"
#include "gfx/font_military.h"
// Tools
#include "tools/Colors.h"
#include "tools/Tools.h"
// Terrain
#include "terrain/Cell.h"
#include "terrain/TerrainCell.h"
#include "terrain/Terrain.h"
// Game
#include "game/Curves.h"
#include "game/Cannon.h"
#include "game/Ammo.h"
#include "game/Player.h"
#include "game/Manager.h"
#include "game/ScorePanel.h"
// Screens
#include "screens/Screen.h"
#include "screens/GameScreen.h"
#include "screens/TitleScreen.h"
// Main
#include "App.h"

#endif /*SHOOTMII_H_*/
