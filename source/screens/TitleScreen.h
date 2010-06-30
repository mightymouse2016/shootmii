#ifndef __TITLE_SCREEN_H__
#define __TITLE_SCREEN_H__

#include "GRRLIB.h"
#include "Screen.h"
#include "../FreeTypeGX/FreeTypeGX.h"

namespace shootmii {

class App;
class Pointer;

class TitleScreen : public Screen {
private:
	GRRLIB_texImg* tex_font;
	Button* exitButton;
	Button* newGameButton;
public:
	TitleScreen(
			App* app,
			Pointer** pointerPlayer,
			u32** eventsPlayer);
	void init();
	void dealEvent();
	void compute();
	void addToDrawManager();
};

}

#endif // __TITLE_SCREEN_H__
