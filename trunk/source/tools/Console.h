#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "../ShootMii.h"

namespace shootmii {
  
  static const u8 MAX_HISTORY = 15;
  static const u8 CONSOLE_HEIGHT = 180;
  static const u8 CONSOLE_X_OFFSET = 15;
  static const u8 CONSOLE_TEXT_X_OFFSET = 25;
  static const u8 CONSOLE_TEXT_Y_OFFSET = 10;
  
  class Console {
    public:
      Console(App*, u8);
      ~Console();
      void draw();      
      void addDebug(string txt);
      
    private:
      App* app;
      u8 screenY;
      GRRLIB_texImg console_font;
      vector<string> history;
      void drawFPS();
  };
  
}

#endif /*CONSOLE_H_*/
