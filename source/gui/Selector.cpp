#include "SelectorOption.h"
#include "Selector.h"
#include "../screens/Screen.h"

namespace shootmii{

Selector::Selector(
		Screen* _screen,
		const std::string& _title,
		const float _originX,
		const float _originY) :
	Rectangle(TEXT_LAYER,0,0,_originX,_originY),
	screen(_screen),
	title(new Text(_title,GUI_FONT,FONT_SIZE_10,Color::WHITE,0,0)),
	selectedIndex(-1),
	startX(title->getWidth()/2 + SPACE_BETWEEN_OPTIONS)
{
	addChild(title);
}

Selector::~Selector() {
	// On ne supprime pas les Text, on a fait setFather donc c'est automatique
}

void Selector::addOption(const std::string& _optionName){
	SelectorOption* _option = new SelectorOption(options.size(),startX,0,_optionName);
	startX += _option->getText()->getWidth() + SPACE_BETWEEN_OPTIONS;
	addChild(_option);
	options.push_back(_option);
	screen->getClickables().push_back(_option);
}

unsigned int Selector::getSelectedIndex() const{
	return selectedIndex;
}

void Selector::setSelectedIndex(const unsigned int _index){
	selectedIndex = _index;
	for (unsigned int i=0;i<options.size();i++){
		options[i]->getText()->setColor(i == _index ? Color::RED : Color::WHITE);
	}
	click();
}

bool Selector::isClicked() const{
	return clicked;
}

void Selector::click(){
	clicked = true;
}

void Selector::unClick(){
	clicked = false;
}

}
