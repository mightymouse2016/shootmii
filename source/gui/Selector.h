#ifndef SELECTOR_H_
#define SELECTOR_H_

#include <vector>
#include <string>
#include "../math/Rectangle.h"

namespace shootmii{

class Text;
class Screen;
class SelectorOption;

const int SPACE_BETWEEN_OPTIONS(20);

class Selector : public Rectangle{
private:
	Screen* screen;
	Text* title;
	std::vector<SelectorOption*> options;
	int selectedIndex;
	float startX;
public:
	Selector(Screen* screen, const std::string& title, const float _originX, const float _originY);
	~Selector();
	void addOption(const std::string& option);
	void select(const unsigned int index);
};

}

#endif /* SELECTOR_H_ */
