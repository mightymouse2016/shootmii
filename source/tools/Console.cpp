#include "../ShootMii.h"

namespace shootmii {

  Console::Console(App* app, u8 screenY) {
    this->app = app;
    this->screenY = screenY;
    console_font = loadFont(font_console, 8, 0);
  }

  Console::~Console() {
    // NOTHING TO DO
  }

  void Console::addDebug(string txt) {
    if(app->isDebug()) {
      if (history.size() == MAX_HISTORY) {
        history.erase(history.begin());
      }
      history.push_back(txt);
    }
  }

  void Console::draw() {
    if (app->isDebug()) {
      
      drawFPS();
      
      // Affichage du BACKGROUND
      GRRLIB_Rectangle(CONSOLE_X_OFFSET, screenY, SCREEN_WIDTH - 2*CONSOLE_X_OFFSET, CONSOLE_HEIGHT, CONSOLE_COLOR, true);

      // Affichage des debug
      for (u8 i=0; i<history.size(); i++) {
        GRRLIB_Printf(CONSOLE_TEXT_X_OFFSET, screenY + (i+1)*CONSOLE_TEXT_Y_OFFSET, console_font, WHITE, 1, history[i].c_str());
      }
    }
  }
  
  void Console::drawFPS() {
    // Affichage du BACKGROUND
    GRRLIB_Rectangle(CONSOLE_X_OFFSET, CONSOLE_X_OFFSET, 75, 25, CONSOLE_COLOR, true);

    // Affichage des FPS
    GRRLIB_Printf(CONSOLE_X_OFFSET + 10, CONSOLE_X_OFFSET + 10, console_font, WHITE, 1, "FPS: %d", app->getFPS());
  }
}
