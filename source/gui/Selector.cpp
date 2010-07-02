#include "Text.h"
#include "../tools/Colors.h"
#include "Selector.h"

namespace shootmii{

Selector::Selector(
		const std::string& _title,
		const float _originX,
		const float _originY) :
	Rectangle(TEXT_LAYER,0,0,_originX,_originY),
	title(new Text(_title,GUI_FONT,FONT_SIZE_10,WHITE,0,0)),
	selectedIndex(-1),
	startX(title->getWidth()/2 + SPACE_BETWEEN_OPTIONS)
{
	addChild(title);
}

Selector::~Selector() {
	// On ne supprime pas les Text, on a fait setFather donc c'est automatique
}

void Selector::addOption(const std::string& option){
	Text* text = new Text(option,GUI_FONT,FONT_SIZE_10,WHITE,startX,0,FTGX_ALIGN_MIDDLE | FTGX_JUSTIFY_LEFT);
	startX += text->getWidth() + SPACE_BETWEEN_OPTIONS;
	addChild(text);
	options.push_back(text);
}

void Selector::select(const unsigned int _index){
	selectedIndex = _index;
	for (unsigned int i=0;i<options.size();i++){
		options[i]->setColor(i == _index ? RED : WHITE);
	}
}

}
