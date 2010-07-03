#ifndef __GAME_SCREEN_H__
#define __GAME_SCREEN_H__

#include <wiiuse/wpad.h>
#include "GRRLIB.h"
#include "Screen.h"

namespace shootmii {

class Manager;
class Pointer;
class ScoreManager;

class GameScreen : public Screen {
private:
	Manager* manager;
	ScoreManager* score_manager;
	Button* exitButton;
	Button* resumeButton;
public:
	GameScreen(
			App* app,
			Pointer** pointerPlayer,
			u32** eventsPlayer);
	virtual ~GameScreen();
	Manager* getManager();
	void init();
	void dealEvent();
	void compute();
	void addToDrawManager();
};

}

#endif // __GAME_SCREEN_H__
