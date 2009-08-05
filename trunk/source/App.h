#ifndef __APP_H__
#define __APP_H__

#include "ShootMii.h"

namespace shootmii {

enum ScreenType {
	TITLE_SCREEN, GAME_SCREEN
};

enum EventType {
	DOWN, UP, HELD
};

class App {
private:
	u8 fps;
	u32 lastTime;
	u8 frameCount;
	bool running;
	int nbFrame;
	ScreenType screen;
	TitleScreen* titleScreen;
	GameScreen* gameScreen;
public:
	static Console* console;
	static ImageBank* imageBank;
	App();
	virtual ~App();
	u8 getFPS() const;
	u8 getFrameCount() const;
	bool isRunning() const;
	void run();
	void dealEvent();
	void computeFrameRate();
	void compute();
	void draw() const;
};

}

#endif // __APP_H__
