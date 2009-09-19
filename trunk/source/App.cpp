#include "ShootMii.h"

namespace shootmii {


Console* App::console = new Console;
ImageBank* App::imageBank = new ImageBank;
SoundBank* App::soundBank = new SoundBank;
DrawManager* App::drawManager = new DrawManager;

App::App():
	fps(0),
	lastTime(0),
	frameCount(0),
	running(true),
	nbFrame(0),
	screen(TITLE_SCREEN)
{
	PAD_Init();
	GRRLIB_Init();
	WPAD_Init();
	ASND_Init();
	MP3Player_Init();
	App::imageBank->init();
	App::soundBank->init();
	srand(time(NULL));
	titleScreen = new TitleScreen(this);
	gameScreen = new GameScreen(this);
}

App::~App() {
	delete titleScreen;
	delete gameScreen;
	delete console;
	delete imageBank;
	delete drawManager;
	GRRLIB_Exit();
}

bool App::isRunning() const {
	return running;
}

u8 App::getFPS() const {
	return fps;
}

u8 App::getFrameCount() const {
	return frameCount;
}

void App::run() {
	dealEvent();
	compute();
	draw();
}

void App::dealEvent() {
	WPAD_ScanPads();
	u32 pad1Down = WPAD_ButtonsDown(WPAD_CHAN_0);
	u32 pad1Up = WPAD_ButtonsUp(WPAD_CHAN_0);
	u32 pad1Held = WPAD_ButtonsHeld(WPAD_CHAN_0);
	u32 pad2Down = WPAD_ButtonsDown(WPAD_CHAN_1);
	u32 pad2Up = WPAD_ButtonsUp(WPAD_CHAN_1);
	u32 pad2Held = WPAD_ButtonsHeld(WPAD_CHAN_1);
	u32 player1Events[3] = {pad1Down, pad1Up, pad1Held};
	u32 player2Events[3] = {pad2Down, pad2Up, pad2Held};

	// Gestion du mode DEBUG
	if (player1Events[DOWN] & WPAD_BUTTON_MINUS) {
		console->toggleDebug();
		return;
	}

	// Passage moche mais qui marche (passage d'un screen à un autre)
	switch (screen) {
	case TITLE_SCREEN:
		if ((player1Events[DOWN] | player2Events[DOWN]) & WPAD_BUTTON_HOME) {
			this->running = false;
		}
		else if ((player1Events[DOWN] | player2Events[DOWN]) & WPAD_BUTTON_A) {
		  console->addDebug("gameScreen !!!");
		  screen = GAME_SCREEN;
		  gameScreen->init();
		}
		else {
			titleScreen->dealEvent(player1Events, player2Events);
		}
		break;
	case GAME_SCREEN:
		if ((player1Events[DOWN] | player2Events[DOWN]) & WPAD_BUTTON_HOME) {
			console->addDebug("titleScreen !!!");
			screen = TITLE_SCREEN;
		}
		else {
			gameScreen->dealEvent(player1Events, player2Events);
		}
		break;
	}
}

void App::computeFrameRate() {
	u32 currentTime = ticks_to_millisecs(gettime());
	frameCount++;
	if(currentTime - lastTime > 1000) {
		lastTime = currentTime;
		fps = frameCount;
		frameCount = 0;
		App::console->setFPS(fps);
	}
}

void App::compute(){
	switch (screen) {
	case TITLE_SCREEN:break;
	case GAME_SCREEN:gameScreen->compute();break;
	}
	computeFrameRate();
}

void App::draw() const{
	switch (screen) {
	case TITLE_SCREEN:titleScreen->draw();break;
	case GAME_SCREEN:gameScreen->addToDrawManager();break;
	}
	drawManager->draw();
	console->draw();
	GRRLIB_Render();

}

}
