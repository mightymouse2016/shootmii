#include "tools/Console.h"
#include "tools/ImageBank.h"
#include "tools/SoundBank.h"
#include "game/DrawManager.h"
#include "gui/Pointer.h"
#include "screens/Screen.h"
#include "screens/TitleScreen.h"
#include "screens/GameScreen.h"
#include "App.h"

namespace shootmii {

Console* App::console = new Console;
ImageBank* App::imageBank = new ImageBank;
SoundBank* App::soundBank = new SoundBank;
DrawManager* App::drawManager = new DrawManager;
FreeTypeGX* App::fontManager = new FreeTypeGX;

App::App():
	fps(0),
	lastTime(0),
	frameCount(0),
	running(true),
	nbFrame(0)
{
	PAD_Init();
	GRRLIB_Init();
	WPAD_Init();

	// Utilisation de l'infra-rouge
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
	WPAD_SetDataFormat(WPAD_CHAN_1, WPAD_FMT_BTNS_ACC_IR);

	ASND_Init();
	MP3Player_Init();
	App::imageBank->init();
	App::soundBank->init();
	pointerPlayer[0] = new Pointer(1,this);
	pointerPlayer[1] = new Pointer(2,this);
	screens[TITLE_SCREEN] = new TitleScreen(this,pointerPlayer,eventsPlayer);
	screens[GAME_SCREEN] = new GameScreen(this,pointerPlayer,eventsPlayer);
	currentScreen = screens[TITLE_SCREEN];
	srand(time(NULL));
}

App::~App() {
	screens.clear();
	delete console;
	delete imageBank;
	delete soundBank;
	delete drawManager;
	delete pointerPlayer[0];
	delete pointerPlayer[1];
	GRRLIB_Exit();
}

u8 App::getFPS() const {
	return fps;
}

u8 App::getFrameCount() const {
	return frameCount;
}

u32** App::getEventsPlayer(){
	return eventsPlayer;
}

bool App::isRunning() const {
	return running;
}

void App::setScreen(int screenType){
	currentScreen = screens[screenType];
	currentScreen->init();
}

void App::run() {
	dealEvent();
	compute();
	draw();
}

void App::exit() {
	running = false;
}

void App::dealEvent() {
	WPAD_ReadPending(WPAD_CHAN_ALL, NULL);
	currentScreen->dealEvent();
}

void App::compute(){
	currentScreen->compute();
	computeFrameRate();
}

void App::computeFrameRate() {
	unsigned int currentTime = ticks_to_millisecs(gettime());
	frameCount++;
	if(currentTime - lastTime > 1000) {
		lastTime = currentTime;
		fps = frameCount;
		frameCount = 0;
		App::console->setFPS(fps);
	}
}

void App::draw(){
	currentScreen->addToDrawManager();
	drawManager->draw();
	console->draw();
	GRRLIB_Render();
}

}
