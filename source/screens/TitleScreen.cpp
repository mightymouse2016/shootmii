#include "../ShootMii.h"

namespace shootmii {

  TitleScreen::TitleScreen(App* app) : Screen(app) {
    tex_title_screen = GRRLIB_LoadTexture(title_screen);
    tex_font = loadFont(font_military, 32, 32);
  }

  TitleScreen::~TitleScreen() {
    free(tex_title_screen.data);
  }

  void TitleScreen::draw() {
    GRRLIB_FillScreen(BLACK);
    GRRLIB_DrawImg(0, 0, tex_title_screen, 0, 1, 1, WHITE);

    if (this->app->getFrameCount() > 25) {
      printRight(440, tex_font, WHITE, 1, "press start");
    }
  }
  
  void TitleScreen::dealEvent(const u32*, const u32*){
    
  }
}
