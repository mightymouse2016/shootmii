#include "../ShootMii.h"

namespace shootmii {

bool segmentIntersect(const float Ax, const float Ay, const float Bx, const float By, const float Cx, const float Cy, const float Dx, const float Dy){
	float r = ((Ay-Cy)*(Dx-Cx)-(Ax-Cx)*(Dy-Cy))/((Bx-Ax)*(Dy-Cy)-(By-Ay)*(Dx-Cx));
	float s = ((Ay-Cy)*(Bx-Ax)-(Ax-Cx)*(By-Ay))/((Bx-Ax)*(Dy-Cy)-(By-Ay)*(Dx-Cx));
	if (0 <= r && r <= 1 && 0 <= s && s <= 1) return true;
	return false;
}

GRRLIB_texImg* loadFont(const unsigned char font[], unsigned int size,unsigned int tilestart) {
	GRRLIB_texImg* texture_font = GRRLIB_LoadTexture(font);
	GRRLIB_InitTileSet(texture_font, size, size, tilestart);
	return texture_font;
}

void printXCentered(f32 ypos, GRRLIB_texImg* tex, u32 color, f32 zoom, const char *text) {
	f32 textLength = strlen(text)*tex->tilew;
	GRRLIB_Printf((SCREEN_WIDTH - textLength)/2, ypos, tex, color, zoom, text);
}

void printRight(f32 ypos, GRRLIB_texImg* tex, u32 color, f32 zoom,const char *text){
	f32 textLength = strlen(text)*tex->tilew;
	GRRLIB_Printf(SCREEN_WIDTH - textLength, ypos, tex, color, zoom, text);
}

void drawRectangle(f32 x, f32 y, f32 width, f32 height, u32 colors[4]) {
	f32 x2 = x+width;
	f32 y2 = y+height;
	Vector v[] = {{x,y,0.0f}, {x2,y,0.0f}, {x2,y2,0.0f}, {x,y2,0.0f}, {x,y,0.0f}};

	GX_Begin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);

	for(int i=0; i < 4; i++) {
		GX_Position3f32(v[i].x, v[i].y,  v[i].z);
		GX_Color1u32(colors[i]);
	}

	GX_End();
}

}
