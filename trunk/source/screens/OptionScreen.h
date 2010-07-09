#ifndef __OPTION_SCREEN_H__
#define __OPTION_SCREEN_H__

#include "GRRLIB.h"
#include "Screen.h"
#include "../FreeTypeGX/FreeTypeGX.h"

namespace shootmii {

class App;
class Pointer;

class OptionScreen : public Screen {
private:
	GRRLIB_texImg* tex_font;
	Button* backButton;
	Button* startButton;
	Selector* roundSelector;
	Selector* player1Selector;
	Selector* player2Selector;
public:
	OptionScreen(
			App* app,
			Pointer** pointerPlayer,
			u32** eventsPlayer);
	void init();
	void dealEvent();
	void compute();
	void addToDrawManager();
	void setRoundCount(unsigned int roundCount);
	void setPlayer1IA(const bool ia);
	void setPlayer2IA(const bool ia);
};

}

#endif // __OPTION_SCREEN_H__
