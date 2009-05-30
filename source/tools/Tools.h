#ifndef __TOOLS_H__
#define __TOOLS_H__

namespace shootmii {

  static const f32 SCREEN_WIDTH = 640;
  static const f32 SCREEN_HEIGHT = 480;

  GRRLIB_texImg loadFont(const unsigned char font[], unsigned int size,
    unsigned int tilestart);
  void printXCentered(f32 ypos, GRRLIB_texImg tex, u32 color, f32 zoom,
    const char *text);
  void printRight(f32 ypos, GRRLIB_texImg tex, u32 color, f32 zoom,
    const char *text);

}
#endif
