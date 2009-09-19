#include "../ShootMii.h"

namespace shootmii {

Button::Button(const int originX,
	const int originY,
	const int width,
	const int height,
	const string _text,
	GRRLIB_texImg* image) :
		Rectangle(BUTTON_LAYER,width,height,originX,originY,0,0,0,1,image),
		text(_text)
{
	// NOTHING TO DO
}

}
