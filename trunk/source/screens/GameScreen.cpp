#include "../ShootMii.h"

namespace shootmii {

  GameScreen::GameScreen(App* _app, string nick_p1, string nick_p2) :
    Screen(_app), manager(new Manager(nick_p1,nick_p2)), score_panel(new ScorePanel(_app,manager)), tex_screen(GRRLIB_LoadTexture(game_select_screen))

  {
    // NOTHING TO BE DONE
  }

  GameScreen::~GameScreen() {
    free(tex_screen.data);
    delete score_panel;
    delete manager;
  }

  void GameScreen::draw() {
    manager->draw();
    score_panel->draw();
  }

  void GameScreen::show() {
    manager->show();
  }

  void GameScreen::dealEvent(const u32 pad1Held, const u32 pad2Held) {
    manager->dealEvent(pad1Held, pad2Held);
  }

}
