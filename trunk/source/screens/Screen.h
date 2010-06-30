#ifndef SCREEN_H_
#define SCREEN_H_

#include <list>
#include <string>
#include "../gui/Button.h"

namespace shootmii {

class App;
class Text;
class Dock;
class Selector;
class Pointer;

enum ScreenType{
	TITLE_SCREEN,
	GAME_SCREEN,
	OPTION_SCREEN
};

class Screen {
    protected:
		App* app;
		Pointer** pointerPlayer;
		u32** eventsPlayer;
		std::list<Button*> buttons;
		std::list<Button*>::iterator selectedButton;
		bool selectionMode;
		std::list<Text*> texts;
		std::list<Dock*> docks;
		std::list<Selector*> selectors;
    public:
		Screen(App* app,Pointer** pointerPlayer,unsigned int** eventsPlayer);
		virtual ~Screen();
		virtual void addToDrawManager();
		virtual void init();
		virtual void compute();
		void computePointer(Pointer* pointer);
		void computeButtons();
		void computeDocks();
		void computeSelectors();
		void addButton(Button* button);
		void addText(Text* text);
		void addDock(Dock* dock);
		void addSelector(Selector* selector);
		virtual void dealEvent();
};

}

#endif /*SCREEN_H_*/
