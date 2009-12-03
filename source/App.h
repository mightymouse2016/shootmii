#ifndef __APP_H__
#define __APP_H__

#include "ShootMii.h"

namespace shootmii {

class App {
private:
	u8 fps;
	u32 lastTime;
	u8 frameCount;
	bool running;
	int nbFrame;
	Screen* currentScreen;
	map<ScreenType,Screen*> screens;
	u32* eventsPlayer[2];
	Pointer* pointerPlayer[2];
public:
	static Console* console;
	static ImageBank* imageBank;
	static SoundBank* soundBank;
	static DrawManager* drawManager;
	static FreeTypeGX* fontManager;
	App();
	virtual ~App();
	u8 getFPS() const;
	u8 getFrameCount() const;
	u32** getEventsPlayer();
	bool isRunning() const;
	void setScreen(ScreenType screen);
	void run();
	void exit();
	void dealEvent();

	void computeFrameRate();
	void compute();
	void draw();
};

}

#endif // __APP_H__
