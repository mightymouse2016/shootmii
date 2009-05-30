#include "../ShootMii.h"

namespace shootmii {
  GRRLIB_texImg loadFont(const unsigned char font[], unsigned int size,
    unsigned int tilestart) {
    GRRLIB_texImg texture_font = GRRLIB_LoadTexture(font);
    GRRLIB_InitTileSet(&texture_font, size, size, tilestart);
    return texture_font;
  }

  void printXCentered(f32 ypos, GRRLIB_texImg tex, u32 color, f32 zoom,
    const char *text) {
    f32 textLength = strlen(text)*tex.tilew;
    GRRLIB_Printf((SCREEN_WIDTH - textLength)/2, ypos, tex, color, zoom, text);
  }

  void printRight(f32 ypos, GRRLIB_texImg tex, u32 color, f32 zoom,
    const char *text) {
    f32 textLength = strlen(text)*tex.tilew;
    GRRLIB_Printf(SCREEN_WIDTH - textLength, ypos, tex, color, zoom, text);
  }
}
