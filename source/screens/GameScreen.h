#ifndef __GAME_SCREEN_H__
#define __GAME_SCREEN_H__

#include "../ShootMii.h"

namespace shootmii {

class GameScreen : public Screen {
private:
	Manager* manager;
	ScoreManager* score_manager;
public:
	GameScreen(
			App* app,
			Pointer** pointerPlayer,
			u32** eventsPlayer);
	virtual ~GameScreen();
	void init();
	void dealEvent();
	void compute();
	void addToDrawManager();
};

}

#endif // __GAME_SCREEN_H__
