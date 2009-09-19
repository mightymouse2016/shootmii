#ifndef BUTTON_H_
#define BUTTON_H_

#include "../ShootMii.h"

namespace shootmii {

const int BUTTON_1_WIDTH(196);
const int BUTTON_1_HEIGHT(52);
// App::imageBank->get(TXT_BUTTON_1)

class Button : public Rectangle{
private:
	string text;
public:
	Button(
		const int originX,
		const int originY,
		const int width,
		const int height,
		const string text,
		GRRLIB_texImg* image
	);
};

}

#endif /* BUTTON_H_ */
