#ifndef SCOREPANEL_H_
#define SCOREPANEL_H_

#include "../ShootMii.h"

namespace shootmii{
 
  const int SCORE_PANEL_HEIGHT(64);
  
  class ScorePanel{
    private:
      App* app;
      Player* player1;
      Player* player2;
      GRRLIB_texImg tex_score_panel;
      GRRLIB_texImg tex_font_score;
      GRRLIB_texImg tex_font;
      GRRLIB_texImg tex_jauge_life;
      GRRLIB_texImg tex_jauge_strength;
      GRRLIB_texImg tex_jauge_heat;
      GRRLIB_texImg tex_jauge_fury;
      GRRLIB_texImg tex_jauge_bonus;
      
    public:
      ScorePanel(App* _app, Player* _player1, Player* _player2);
      virtual ~ScorePanel();
      void draw() const;
      void drawBackGround() const;
      void drawScore() const;
      void drawPlayer1() const;
      void drawPlayer2() const;
      // void drawJauge(int pourcentage, image, x ,y)
  };

}

#endif /*SCOREPANEL_H_*/
