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
	unsigned int selectedIndex;
	float startX;
	bool clicked;
public:
	Selector(Screen* screen, const std::string& title, const float _originX, const float _originY);
	~Selector();
	void addOption(const std::string& option);
	unsigned int getSelectedIndex() const;
	void setSelectedIndex(const unsigned int index);
	bool isClicked() const;
	void click();
	void unClick();
};

}

#endif /* SELECTOR_H_ */
