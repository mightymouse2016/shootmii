#include "Color.h"

namespace shootmii {

const Color Color::TRANSPARENT(0xFFFFFF00);
const Color Color::BLACK(0x000000FF);
const Color Color::WHITE(0xFFFFFFFF);
const Color Color::RED(0xFF0000FF);
const Color Color::GREEN(0x00FF00FF);
const Color Color::BLUE(0x0000FFFF);
const Color Color::YELLOW(0xFFFF00FF);
const Color Color::BROWN(0x754716FF);
const Color Color::GREEN_GRASS(0x1D9517FF);
const Color Color::CONSOLE_COLOR(0xFF000099);
const Color Color::BLUE_SKY_1(0xA2FFF1FF);
const Color Color::BLUE_SKY_2(0x0C00FFFF);

Color::Color(const unsigned long _hexa) :
		hexa(_hexa)
{

}

Color::Color(const Color& color1, const Color& color2, const float ratio){
	unsigned long r = (color1 & 0xFF000000) * ratio + (color2 & 0xFF000000) * (1 - ratio);
	unsigned long g = (color1 & 0x00FF0000) * ratio + (color2 & 0x00FF0000) * (1 - ratio);
	unsigned long b = (color1 & 0x0000FF00) * ratio + (color2 & 0x0000FF00) * (1 - ratio);
	unsigned long a = (color1 & 0x000000FF) * ratio + (color2 & 0x000000FF) * (1 - ratio);
	hexa = (r & 0xFF000000) | (g & 0x00FF0000) | (b & 0x0000FF00) | (a & 0x000000FF);
}

Color::operator unsigned long() const{
	return hexa;
}

Color::operator GXColor() const{
	unsigned char r = (hexa >> 24) & 0x000000FF;
	unsigned char g = (hexa >> 16) & 0x000000FF;
	unsigned char b = (hexa >> 8 ) & 0x000000FF;
	unsigned char a =  hexa & 0x000000FF;
	return (GXColor) {r,g,b,a};
}

}
