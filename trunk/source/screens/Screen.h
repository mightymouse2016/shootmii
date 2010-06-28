#ifndef SCREEN_H_
#define SCREEN_H_

#include <map>
#include <list>
#include <string>
#include "../gui/Button.h"

namespace shootmii {

class App;
class Text;
class Dock;
class Pointer;

enum ScreenType{
	TITLE_SCREEN,
	GAME_SCREEN
};

class Screen {
    protected:
		App* app;
		Pointer** pointerPlayer;
		u32** eventsPlayer;
		std::map<ButtonType,Button*> buttons;
		std::map<ButtonType,Button*>::iterator selectedButton;
		bool selectionMode;
		std::list<Text*> texts;
		std::list<Dock*> docks;
    public:
		Screen(App* app,Pointer** pointerPlayer,unsigned int** eventsPlayer);
		virtual ~Screen();
		virtual void addToDrawManager();
		virtual void init();
		virtual void compute();
		void computePointer(Pointer* pointer);
		void computeButtons();
		void computeDocks();
		void addButton(const int originX, const int originY, const std::string text, const ButtonType type);
		void addText(Text* text);
		void addDock(Dock* dock);
		virtual void dealEvent();
};

}

#endif /*SCREEN_H_*/
