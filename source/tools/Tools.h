#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "GRRLIB.h"

namespace shootmii {

static const f32 SCREEN_WIDTH(640);
static const f32 SCREEN_HEIGHT(480);

enum EventType {
	DOWN, UP, HELD
};

class Interval{
protected:
	float minimum;
	float maximum;
	bool empty;
public:
	Interval();
	Interval(const float x1, const float x2);
	void set(const float x1, const float x2);
	float getMin() const;
	float getMax() const;
	bool intersect(Interval& i) const;
	void clear();
	bool isEmpty() const;
};

bool segmentIntersect(const float Ax, const float Ay, const float Bx, const float By,
		const float Cx, const float Cy, const float Dx, const float Dy);
GRRLIB_texImg* loadFont(const unsigned char font[], unsigned int size, unsigned int tilestart);
void printXCentered(f32 ypos, GRRLIB_texImg tex, u32 color, f32 zoom, const char *text);
void printRight(f32 ypos, GRRLIB_texImg* tex, u32 color, f32 zoom, const char *text);
void drawRectangle(f32 x, f32 y, f32 width, f32 height, u32 colors[4]);
u32 colorFadeOut(const u32 color1, const u32 color2, const float ratio);
void swap(float* const a, float* const b);
float min(const float a, const float b);
float max(const float a, const float b);
float angleDiff(const float angle1, const float angle2);
float angularModulo(const float angle);
bool areDisjointIntervals(const float alphaA1, const float alphaA2, const float alphaB1, const float alphaB2);
bool doesIntervalContain(const float a, const float a1, const float a2);
float fixAngle(const float angle);
}
#endif
