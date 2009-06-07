#include "../ShootMii.h"

namespace shootmii {

  ScoreManager::ScoreManager(App* _app, Manager* _manager) :
    app(_app), manager(_manager),
        tex_score_panel(GRRLIB_LoadTexture(score_panel)) {
    tex_jauge_strength = GRRLIB_LoadTexture(power_jauge);
  }

  ScoreManager::~ScoreManager() {
    free(tex_score_panel.data);
  }

  void ScoreManager::draw() const {
    drawBackGround();
    drawScore();
    drawPlayer(manager->getPlayer1());
    drawPlayer(manager->getPlayer2());
  }

  void ScoreManager::drawJauge(const int screenX, const int screenY,
    const int width, const int height, const int percentage,
    const GRRLIB_texImg image) const {

    // On affiche la jauge entière
    GRRLIB_DrawImg(screenX, screenY, image, 0, 1, 1, WHITE);

    // On affiche un cache noir
    GRRLIB_Rectangle(
        screenX + (width*percentage)/100,
        screenY,
        (width*(100 - percentage))/100,
        height,
        RED,
        1
    );

  }

  void ScoreManager::drawBackGround() const {
    GRRLIB_DrawImg(0, SCREEN_HEIGHT-SCORE_PANEL_HEIGHT, tex_score_panel, 0, 1,
        1, WHITE);
  }

  void ScoreManager::drawScore() const {
    // TODO
  }

  void ScoreManager::drawPlayer(const Player* player) const {
    int screenX;
    if (player == manager->getPlayer1()) {
      screenX = 69;
    } else {
      screenX = 502;
    }
    drawJauge(screenX, 480-43, 68, 8, player->getStrength(), tex_jauge_strength);
    drawJauge(screenX, 480-43+14, 68, 8, player->getLife(), tex_jauge_strength);
  }
}
