#ifndef SELECTOROPTION_H_
#define SELECTOROPTION_H_

#include <string>
#include "Clickable.h"

namespace shootmii {

class Text;

class SelectorOption : public Clickable{
protected:
	bool highLighted;
public:
	SelectorOption(
		const int originX,
		const int originY,
		const std::string text
	);
	void grow();
	void shrink();
	void draw();
	void highLight();
	void unHighLight();
};

}

#endif /* SELECTOROPTION_H_ */
