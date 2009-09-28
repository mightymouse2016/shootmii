#ifndef TEXT_H_
#define TEXT_H_

#include "../ShootMii.h"

namespace shootmii{

enum fontName{
	GUI_FONT,
	ARMY_FONT
};

enum fontSize{
	FONT_SIZE_0 = 8,
	FONT_SIZE_1 = 9,
	FONT_SIZE_2 = 10,
	FONT_SIZE_3 = 11,
	FONT_SIZE_4 = 12,
	FONT_SIZE_5 = 14,
	FONT_SIZE_6 = 16,
	FONT_SIZE_7 = 18,
	FONT_SIZE_8 = 20,
	FONT_SIZE_9 = 22,
	FONT_SIZE_10 = 24,
	FONT_SIZE_11 = 26,
	FONT_SIZE_12 = 28,
	FONT_SIZE_13 = 36,
	FONT_SIZE_14 = 48,
	FONT_SIZE_15 = 72
};

/*
 * Ordre d'éxécution à respecter pour éviter les bugs :
 * setFontSize / setFontName
 * initFont
 * setText
 * update
 * setColor
 */

class Text : public Rectangle{
private:
	wchar_t* text;
	fontName name;
	fontSize size;
	GXColor color;
	FreeTypeGX* gxFont;
public:
	Text(string text, fontName name, fontSize size, u32 color, const float originX = 0, const float originY = 0);
	~Text();
	void initFont();
	void setText(string text);
	void setFontName(fontName name);
	void setFontSize(fontSize size);
	void setColor(u32 _color);
	void update();
	void draw() const;
};

}

#endif /* TEXT_H_ */
