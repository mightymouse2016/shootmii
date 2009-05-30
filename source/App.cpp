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
    u32 pad1Held = WPAD_ButtonsHeld(WPAD_CHAN_0);
    u32 pad2Down = WPAD_ButtonsDown(WPAD_CHAN_1);
    u32 pad2Held = WPAD_ButtonsHeld(WPAD_CHAN_1);

    // Gestion du mode DEBUG
    if (pad1Down & WPAD_BUTTON_MINUS) {
      debug = false;
      return;
    }
    
    switch (screen) {
      case TITLE_SCREEN:
        if (pad1Down & WPAD_BUTTON_HOME) {
          this->running = false;
        } else if (pad1Down & WPAD_BUTTON_A) {
          screen = GAME_SCREEN;
          gameScreen->show();
        } else {
          titleScreen->dealEvent(pad1Down, pad2Down);
        }
        break;
      case GAME_SCREEN:
        if (pad1Down & WPAD_BUTTON_HOME) {
          screen = TITLE_SCREEN;
        } else {
          gameScreen->dealEvent(pad1Held, pad2Held);
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
