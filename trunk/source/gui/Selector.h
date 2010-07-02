#ifndef SELECTOR_H_
#define SELECTOR_H_

#include <vector>
#include <string>
#include "../math/Rectangle.h"

namespace shootmii{

class Text;

const int SPACE_BETWEEN_OPTIONS(20);

class Selector : public Rectangle{
private:
	Text* title;
	std::vector<Text*> options;
	int selectedIndex;
	float startX;
public:
	Selector(const std::string& title, const float _originX, const float _originY);
	~Selector();
	void addOption(const std::string& option);
	void select(const unsigned int index);
};

}

#endif /* SELECTOR_H_ */
