#ifndef CLICKABLE_H_
#define CLICKABLE_H_

#include "../math/Rectangle.h"
#include "../tools/Color.h"
#include "Text.h"

namespace shootmii{

class Text;

const float BUTTON_GROWTH(1.05); // 5% de grossissement
const float GROW_PACE(0.005);
const float SHRINK_PACE(0.005);

class Clickable : public Rectangle{
private:
	bool stuck;
	bool pointed;
	bool clicked;
public:
	Clickable(
		const int originX,
		const int originY,
		const int width,
		const int height,
		const std::string text = "",
		const Color& textColor = Color::BLACK,
		const fontSize textSize = FONT_SIZE_6,
		const u16 textFlags = FTGX_JUSTIFY_CENTER | FTGX_ALIGN_MIDDLE,
		GRRLIB_texImg* image = NULL
	);
	void init();
	virtual void click();
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
	virtual void highLight();
	virtual void unHighLight();
	virtual void grow();
	virtual void shrink();
	virtual void compute();
};

}

#endif /* CLICKABLE_H_ */
