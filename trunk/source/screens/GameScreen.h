#ifndef __GAME_SCREEN_H__
#define __GAME_SCREEN_H__

#include "../ShootMii.h"

namespace shootmii {

  const int N_ROWS(52);
  const int N_COLS(80);
  const int PLAYER_OFFSET(5);
  
  class GameScreen : public Screen {
    private:
      Player* player1;
      Player* player2;
      Terrain* terrain;
      ScorePanel* score_panel;
      GRRLIB_texImg tex_screen;
    public:
      GameScreen(App* _app, string nick_p1 = "Player 1", string nick_p2 = "Player 2");
      virtual ~GameScreen();
      void draw();
      void show();
      void dealEvent(const u32, const u32);
      void initPlayerPosition(Player* player, int offSet = 0) const;
      void moveLeft(Player*);
      void moveRight(Player*);
    };
}

#endif // __GAME_SCREEN_H__
