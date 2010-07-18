#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "GRRLIB.h"

namespace shootmii {

static const f32 SCREEN_WIDTH(640);
static const f32 SCREEN_HEIGHT(480);

enum EventType {
	DOWN, UP, HELD
};

GRRLIB_texImg* loadFont(const unsigned char font[], unsigned int size, unsigned int tilestart);
void printXCentered(f32 ypos, GRRLIB_texImg tex, u32 color, f32 zoom, const char *text);
void printRight(f32 ypos, GRRLIB_texImg* tex, u32 color, f32 zoom, const char *text);
void drawRectangle(f32 x, f32 y, f32 width, f32 height, u32 colors[4]);

float min(const float a, const float b);
float max(const float a, const float b);
float angularModulo(const float angle);
float fixAngle(const float angle);
}
#endif
