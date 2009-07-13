#include "../ShootMii.h"

namespace shootmii {

  ScoreManager::ScoreManager(App* _app, Manager* _manager) :
    app(_app), manager(_manager)   
    {
    tex_font = loadFont(font_score, 48, 48);// 48 c pas la height, c l'indice dans la table ascii
    tex_score_panel = App::imageBank->get(TXT_SCORE_PANEL);
    tex_jauge_life = App::imageBank->get(TXT_LIFE_JAUGE);
    tex_jauge_strength = App::imageBank->get(TXT_STRENGTH_JAUGE);
    tex_jauge_heat = App::imageBank->get(TXT_HEAT_JAUGE); 
  }

  ScoreManager::~ScoreManager() {
    // NOTHING TO DO
  }

  void ScoreManager::draw() const {
    drawBackGround();
    drawScore();
    drawPlayer(manager->getPlayer1());
    drawPlayer(manager->getPlayer2());
  }

  void ScoreManager::drawJauge(const int screenX, const int screenY,
    const int width, const int height, const int percentage,
    const GRRLIB_texImg* image) const {

    // On affiche la jauge entière
    GRRLIB_DrawImg(screenX, screenY, *image, 0, 1, 1, WHITE);

    // On affiche un cache noir
    GRRLIB_Rectangle(
        screenX + (width*percentage)/100,
        screenY,
        (width*(100 - percentage))/100,
        height,
        BLACK,
        1
    );

  }

  void ScoreManager::drawBackGround() const {
    GRRLIB_DrawImg(0, SCREEN_HEIGHT-SCORE_PANEL_HEIGHT, *tex_score_panel, 0, 1,
        1, WHITE);
  }

  void ScoreManager::drawScore() const {
    // Player 1
    char score[1];
    sprintf(score,"%d",manager->getPlayer1()->getScore());
    GRRLIB_Printf(SCREEN_WIDTH/2 - 70, SCREEN_HEIGHT - 55, tex_font, WHITE, 1, score);
    // Player 2
    sprintf(score,"%d",manager->getPlayer2()->getScore());
    GRRLIB_Printf(SCREEN_WIDTH/2 + 18, SCREEN_HEIGHT - 55, tex_font, WHITE, 1, score);
  }

  void ScoreManager::drawPlayer(const Player* player) const {
    Cannon* cannon = player->getCannon();
    
    int screenX;
    if (player == manager->getPlayer1()) screenX = 68;
    else screenX = 504;
    
    // On dessine les jauges
    drawJauge(screenX, 480-29-13*2, 68, 8, 100/*player->getCannon()->getStrength()*/, tex_jauge_strength);
    drawJauge(screenX, 480-29-13, 68, 8, player->getCannon()->getHeat(), tex_jauge_heat);
    drawJauge(screenX, 480-29, 68, 8, player->getLife(), tex_jauge_life);
    // en cas de surchauffe, rectangle rouge clignotant
    if (cannon->getHeat() == 100 && ticks_to_millisecs(gettime())%FLICKERING_TIME < FLICKERING_TIME/2)
      GRRLIB_Rectangle(screenX,480-42,68,8,RED,1);
    
  }
}
