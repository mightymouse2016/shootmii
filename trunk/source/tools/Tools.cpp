#include "Tools.h"
#include "../math/Polygon.h"

namespace shootmii {

Interval::Interval() : empty(true)
{

}

Interval::Interval(
		const float x1,
		const float x2) :
		minimum(min(x1,x2)),
		maximum(max(x1,x2)),
		empty(false)
{

}

void Interval::set(const float x1, const float x2){
	minimum = min(x1,x2);
	maximum = max(x1,x2);
	empty = false;
}

float Interval::getMin() const{
	return minimum;
}

float Interval::getMax() const{
	return maximum;
}

bool Interval::intersect(Interval& i) const{
	if (minimum <= i.getMin() && i.getMin() <= maximum) return true;
	if (minimum <= i.getMax() && i.getMax() <= maximum) return true;
	if (i.getMin() <= minimum && minimum <= i.getMax()) return true;
	if (i.getMin() <= maximum && maximum <= i.getMax()) return true;
	return false;
}

void Interval::clear(){
	empty = true;
}

bool Interval::isEmpty() const{
	return empty;
}

bool segmentIntersect(const float Ax, const float Ay, const float Bx,
		const float By, const float Cx, const float Cy, const float Dx,
		const float Dy) {
	float r = ((Ay - Cy) * (Dx - Cx) - (Ax - Cx) * (Dy - Cy)) / ((Bx - Ax)
			* (Dy - Cy) - (By - Ay) * (Dx - Cx));
	float s = ((Ay - Cy) * (Bx - Ax) - (Ax - Cx) * (By - Ay)) / ((Bx - Ax)
			* (Dy - Cy) - (By - Ay) * (Dx - Cx));
	if (0 <= r && r <= 1 && 0 <= s && s <= 1)
		return true;
	return false;
}

GRRLIB_texImg* loadFont(const unsigned char font[], unsigned int size,
		unsigned int tilestart) {
	GRRLIB_texImg* texture_font = GRRLIB_LoadTexture(font);
	GRRLIB_InitTileSet(texture_font, size, size, tilestart);
	return texture_font;
}

void printXCentered(f32 ypos, GRRLIB_texImg* tex, u32 color, f32 zoom,
		const char *text) {
	f32 textLength = strlen(text) * tex->tilew;
	GRRLIB_Printf((SCREEN_WIDTH - textLength) / 2, ypos, tex, color, zoom, text);
}

void printRight(f32 ypos, GRRLIB_texImg* tex, u32 color, f32 zoom,
		const char *text) {
	f32 textLength = strlen(text) * tex->tilew;
	GRRLIB_Printf(SCREEN_WIDTH - textLength, ypos, tex, color, zoom, text);
}

void drawRectangle(f32 x, f32 y, f32 width, f32 height, u32 colors[4]) {
	f32 x2 = x + width;
	f32 y2 = y + height;
	guVector v[] = { { x, y, 0.0f }, { x2, y, 0.0f }, { x2, y2, 0.0f }, { x,
			y2, 0.0f }, { x, y, 0.0f } };

	GX_Begin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);
	for (int i = 0; i < 4; i++) {
		GX_Position3f32(v[i].x, v[i].y, v[i].z);
		GX_Color1u32(colors[i]);
	}

	GX_End();
}

u32 colorFadeOut(const u32 color1, const u32 color2, const float ratio) {
	u32 r = (color1 & 0xFF000000) * ratio + (color2 & 0xFF000000) * (1 - ratio);
	u32 g = (color1 & 0x00FF0000) * ratio + (color2 & 0x00FF0000) * (1 - ratio);
	u32 b = (color1 & 0x0000FF00) * ratio + (color2 & 0x0000FF00) * (1 - ratio);
	u32 a = (color1 & 0x000000FF) * ratio + (color2 & 0x000000FF) * (1 - ratio);
	return (r & 0xFF000000) | (g & 0x00FF0000) | (b & 0x0000FF00) | (a
			& 0x000000FF);
}

void swap(float* const a, float* const b){
	float tmp = *a;
	*a = *b;
	*b = tmp;
}

float min(const float a, const float b){
	return a<=b?a:b;
}

float max(const float a, const float b){
	return a>=b?a:b;
}


// Fournit un résultat entre 0 et 2PI
float angularModulo(const float angle){
	float modulo = fmod(angle,2*PI);
	if (modulo < 0) modulo += 2*PI;
	return modulo;
}

float fixAngle(const float angle){
	return angularModulo(angle-PI/2);
}

}
