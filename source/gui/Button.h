#ifndef BUTTON_H_
#define BUTTON_H_

#include "../ShootMii.h"

namespace shootmii {

const float BUTTON_GROWTH(1.05); // 5% de grossissement
const float GROW_PACE(0.005);
const float SHRINK_PACE(0.005);
const int BUTTON_1_WIDTH(196);
const int BUTTON_1_HEIGHT(52);

enum ButtonType{
	EXIT_BUTTON,
	START_BUTTON,
	RESUME_BUTTON
};

class Button : public Rectangle{
private:
	bool stuck;
	bool pointed;
	bool clicked;
public:
	Button(
		const int originX,
		const int originY,
		const int width,
		const int height,
		const string text,
		GRRLIB_texImg* image
	);
	void click();
	void unClick();
	bool isClicked() const;
	void stuckIt();
	void unStuckIt();
	void toggleStuck();
	bool isStuck() const;
	void pointOn();
	void pointOver();
	bool isPointed() const;
	Text* getText();
	Text* getText() const;
	void grow();
	void shrink();
};

}

#endif /* BUTTON_H_ */