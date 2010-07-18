#ifndef TEXT_H_
#define TEXT_H_

#include <string>
#include "../FreeTypeGX/FreeTypeGX.h"
#include "../math/Rectangle.h"
#include "../tools/Color.h"

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
 */

class Text : public Rectangle{
private:
	wchar_t* text;
	fontName name;
	fontSize size;
	Color color;
	FreeTypeGX* gxFont;
	/*
	 * FTGX_JUSTIFY_LEFT
	 * FTGX_JUSTIFY_CENTER
     * FTGX_JUSTIFY_RIGHT
     * FTGX_ALIGN_TOP
     * FTGX_ALIGN_MIDDLE
     * FTGX_ALIGN_BOTTOM
     * FTGX_STYLE_UNDERLINE
     * FTGX_STYLE_STRIKE
	 */
	u16 flags;
public:
	Text(std::string text,
			fontName name,
			fontSize size,
			const Color& color,
			const float originX = 0,
			const float originY = 0,
			const u16 flags = FTGX_ALIGN_MIDDLE | FTGX_JUSTIFY_CENTER);
	~Text();
	void initFont();
	void setText(std::string text);
	void setFontName(fontName name);
	void setFontSize(fontSize size);
	void setColor(const Color& _color);
	void setUnderline(const bool underline);
	void update();
	void draw();
};

}

#endif /* TEXT_H_ */
