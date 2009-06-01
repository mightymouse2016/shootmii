#ifndef __APP_H__
#define __APP_H__

#include "ShootMii.h"

namespace shootmii {

  enum ScreenType {
    TITLE_SCREEN,
    GAME_SCREEN
  };
  
  enum EventType {
    DOWN,
    UP,
    HELD
  };
  
  class App {
    public:
      App();
      virtual ~App();
      void run();
      void dealEvent();
      bool isRunning() const;
      bool isDebug() const;
      int getNbFrame() const;
      
    private:  
      bool debug;
      bool running;
      int nbFrame;
      ScreenType screen;      
      void countFrame();
      TitleScreen* titleScreen;
      GameScreen* gameScreen;
  };
}

#endif // __APP_H__
