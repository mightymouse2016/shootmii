#ifndef COLOR_H_
#define COLOR_H_

#include "../FreeTypeGX/FreeTypeGX.h"

namespace shootmii {

class Color {
public:
	static const Color TRANSPARENT;
	static const Color BLACK;
	static const Color WHITE;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color YELLOW;
	static const Color BROWN;
	static const Color GREEN_GRASS;
	static const Color CONSOLE_COLOR;
	static const Color BLUE_SKY_1;
	static const Color BLUE_SKY_2;
protected:
	unsigned long hexa;
public:
	Color(const unsigned long hexa);
	Color(const Color& color1, const Color& color2, const float ratio);
	operator GXColor() const;
	operator unsigned long() const;
};

}

#endif /* COLOR_H_ */
