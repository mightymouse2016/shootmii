#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>
#include "Clickable.h"

namespace shootmii {

const int BUTTON_1_WIDTH(196);
const int BUTTON_1_HEIGHT(52);

class Button : public Clickable{
public:
	Button(
		const int originX,
		const int originY,
		const int width,
		const int height,
		const std::string text,
		GRRLIB_texImg* image
	);
	void highLight();
	void unHighLight();
};

}

#endif /* BUTTON_H_ */
