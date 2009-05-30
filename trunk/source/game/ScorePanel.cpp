#include "../ShootMii.h"

namespace shootmii {

  ScorePanel::ScorePanel(App* _app, Manager* _manager) :
    app(_app),
    manager(_manager),
    tex_score_panel(GRRLIB_LoadTexture(score_panel)) {
  }

  ScorePanel::~ScorePanel() {
    free(tex_score_panel.data);
  }
  
  void ScorePanel::draw() const {
    drawBackGround();
  }

  void ScorePanel::drawBackGround() const {
    GRRLIB_DrawImg(0, SCREEN_HEIGHT-SCORE_PANEL_HEIGHT, tex_score_panel, 0, 1, 1, WHITE );
  }

  void ScorePanel::drawScore() const {
    // TODO
  }

  void ScorePanel::drawPlayer1() const {
    // TODO
  }

  void ScorePanel::drawPlayer2() const {
    // TODO
  }
}
