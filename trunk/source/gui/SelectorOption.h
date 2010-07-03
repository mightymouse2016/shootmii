#ifndef SELECTOROPTION_H_
#define SELECTOROPTION_H_

#include <string>
#include "Clickable.h"

namespace shootmii {

class Text;

const int HIGHLIGHT_FRAME_MARGIN(2);
const int HIGHLIGHT_FRAME_BORDER(2);

class SelectorOption : public Clickable{
protected:
	const int index;
	bool highLighted;
public:
	SelectorOption(
		const int index,
		const int originX,
		const int originY,
		const std::string text
	);
	void click();
	void grow();
	void shrink();
	void draw();
	void highLight();
	void unHighLight();
};

}

#endif /* SELECTOROPTION_H_ */
