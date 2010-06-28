#ifndef DOCK_H_
#define DOCK_H_

#include <list>
#include "../math/Rectangle.h"
#include "../tools/Tools.h"

namespace shootmii{

class Button;
class Text;

const int DOCK_WIDTH(SCREEN_WIDTH);
const int DOCK_HEIGHT(80);
const float HIDE_PACE(2);
const float SHOW_PACE(3);

class Dock : public Rectangle{
private:
	bool position; // false : bottom	true : top
	bool hiddenOutOfScreen;
	std::list<Button*> buttons;
	std::list<Text*> texts;
public:
	Dock(bool position);
	void addButton(Button* button);
	void addText(Text* text);
	void toggleHideShow();
	void compute();
	void init();
};

}

#endif /* DOCK_H_ */
