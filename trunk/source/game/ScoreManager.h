#ifndef SCOREMANAGER_H_
#define SCOREMANAGER_H_

#include "../ShootMii.h"

namespace shootmii {

  const int SCORE_PANEL_HEIGHT(64);
  
  const int MANCHE(3);

  class ScoreManager {
    private:
      App* app;
      Manager* manager;
      GRRLIB_texImg tex_score_panel;
      GRRLIB_texImg tex_font_score;
      GRRLIB_texImg tex_font;
      GRRLIB_texImg tex_jauge_life;
      GRRLIB_texImg tex_jauge_strength;
      GRRLIB_texImg tex_jauge_heat;
      GRRLIB_texImg tex_jauge_fury; // TODO
      GRRLIB_texImg tex_jauge_bonus; // TODO

    public:
      ScoreManager(App*, Manager*);
      virtual ~ScoreManager();
      void draw() const;
      void drawBackGround() const;
      void drawScore() const;
      void drawPlayer(const Player* player) const;
      void drawJauge(const int screenX, const int screenY, const int width,
        const int height, const int percentage, const GRRLIB_texImg image) const;
  };

}

#endif /*SCOREMANAGER_H_*/
