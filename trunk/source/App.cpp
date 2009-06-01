#include "ShootMii.h"

namespace shootmii {

  App::App() {
    GRRLIB_Init();
    WPAD_Init();
    debug = false;
    running = true;
    nbFrame = 0;
    screen = TITLE_SCREEN;
    titleScreen = new TitleScreen(this);
    gameScreen = new GameScreen(this);
  }

  App::~App() {
    GRRLIB_Exit();
    delete titleScreen;
    delete gameScreen;
    exit(0);
  }

  void App::dealEvent() {
    WPAD_ScanPads();
    u32 pad1Down = WPAD_ButtonsDown(WPAD_CHAN_0);
    u32 pad1Up = WPAD_ButtonsUp(WPAD_CHAN_0);
    u32 pad1Held = WPAD_ButtonsHeld(WPAD_CHAN_0);
    u32 pad2Down = WPAD_ButtonsDown(WPAD_CHAN_1);
    u32 pad2Up = WPAD_ButtonsUp(WPAD_CHAN_1);
    u32 pad2Held = WPAD_ButtonsHeld(WPAD_CHAN_1);
    u32 player1Events[3] = {pad1Down, pad1Up, pad1Held};
    u32 player2Events[3] = {pad2Down, pad2Up, pad2Held};
    
    // Gestion du mode DEBUG
    if (player1Events[DOWN] & WPAD_BUTTON_MINUS) {
      debug = false;
      return;
    }
    
    switch (screen) {
      case TITLE_SCREEN:
        if ((player1Events[DOWN] | player2Events[DOWN]) & WPAD_BUTTON_HOME) {
          this->running = false;
        } else if ((player1Events[DOWN] | player2Events[DOWN]) & WPAD_BUTTON_A) {
          screen = GAME_SCREEN;
          gameScreen->show();
        } else {
          titleScreen->dealEvent(player1Events, player2Events);
        }
        break;
      case GAME_SCREEN:
        if ((player1Events[DOWN] | player2Events[DOWN]) & WPAD_BUTTON_HOME) {
          screen = TITLE_SCREEN;
        } else {
          gameScreen->dealEvent(player1Events, player2Events);
        }
        break;
    }
  }

  void App::run() {

    switch (screen) {
      case TITLE_SCREEN: {
        titleScreen->draw();
        break;
      }
      case GAME_SCREEN: {
        gameScreen->draw();
        break;
      }
      default:
        break;
    }

    GRRLIB_Render();
    countFrame();
  }

  bool App::isRunning() const {
    return running;
  }

  bool App::isDebug() const {
    return debug;
  }

  void App::countFrame() {
    nbFrame++;
    if (nbFrame >= 60) {
      nbFrame = 0;
    }
  }

  int App::getNbFrame() const {
    return nbFrame;
  }
}
