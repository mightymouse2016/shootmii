#ifndef __GAME_SCREEN_H__
#define __GAME_SCREEN_H__

#include "../ShootMii.h"

namespace shootmii {
  
  class GameScreen : public Screen {
    private:
      Manager* manager;
      ScoreManager* score_manager;
      GRRLIB_texImg tex_screen;
    public:
      GameScreen(App* _app, string nick_p1 = "Player 1", string nick_p2 = "Player 2");
      virtual ~GameScreen();
      void compute();
      void draw();
      void show();
      void dealEvent(const u32*, const u32*);
    };
}

#endif // __GAME_SCREEN_H__
