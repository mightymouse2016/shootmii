#ifndef SCREEN_H_
#define SCREEN_H_

#include "../ShootMii.h"

namespace shootmii {

enum ScreenType{
	TITLE_SCREEN,
	GAME_SCREEN
};

class Screen {
    protected:
		App* app;
		Pointer** pointerPlayer;
		u32** eventsPlayer;
		map<ButtonType,Button*> buttons;
		map<ButtonType,Button*>::iterator selectedButton;
		bool selectionMode;
		list<Text*> texts;
		list<Dock*> docks;
    public:
		Screen(App* app,Pointer** pointerPlayer,u32** eventsPlayer);
		virtual ~Screen();
		virtual void addToDrawManager();
		virtual void init();
		virtual void compute();
		void computePointer(Pointer* pointer);
		void computeButtons();
		void computeDocks();
		void addButton(const int originX, const int originY, const string text, const ButtonType type);
		void addText(Text* text);
		void addDock(Dock* dock);
		virtual void dealEvent();
};

}

#endif /*SCREEN_H_*/
