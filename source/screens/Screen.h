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
    public:
		Screen(
			  App* app,
			  Pointer** pointerPlayer,
			  u32** eventsPlayer
			 );
		virtual ~Screen();
		virtual void addToDrawManager();
		virtual void init();
		virtual void compute();
		void computePointer(Pointer* pointer);
		void computeButtons();
		void addButton(const int originX, const int originY, const string text, const ButtonType type);
		virtual void dealEvent();
};

}

#endif /*SCREEN_H_*/
