#ifndef __APP_H__
#define __APP_H__

#include "FreeTypeGX/FreeTypeGX.h"
#include <ogc/lwp_watchdog.h>
#include <wiiuse/wpad.h>
#include <mp3player.h>
#include "asndlib.h"
#include "GRRLIB.h"
#include <ctime>
#include <map>

namespace shootmii {

class Console;
class ImageBank;
class SoundBank;
class DrawManager;
class Pointer;
class Screen;
class TitleScreen;
class GameScreen;

enum ScreenType{
	TITLE_SCREEN,
	GAME_SCREEN,
	OPTION_SCREEN
};

class App {
private:
	unsigned char fps;
	unsigned int lastTime;
	unsigned char frameCount;
	bool running;
	int nbFrame;
	Screen* currentScreen;
	std::map<ScreenType,Screen*> screens;
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
	void setScreen(ScreenType screenType);
	Screen* getScreen(ScreenType screenType);
	void run();
	void exit();
	void dealEvent();

	void computeFrameRate();
	void compute();
	void draw();
};

}

#endif // __APP_H__
