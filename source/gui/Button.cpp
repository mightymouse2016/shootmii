#include "Button.h"

namespace shootmii {

Button::Button(
		const int _originX,
		const int _originY,
		const int _width,
		const int _height,
		const std::string _text,
		GRRLIB_texImg* _image) :
		Clickable(
				_originX,
				_originY,
				_width,
				_height,
				_text,
				BLACK,
				FONT_SIZE_6,
				FTGX_ALIGN_MIDDLE | FTGX_JUSTIFY_CENTER,
				_image)
{

}

void Button::highLight(){
	setSprite(1);
}

void Button::unHighLight(){
	setSprite(0);
}

}
