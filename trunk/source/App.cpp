#include "ShootMii.h"

namespace shootmii {

App::App() :
  fps(0),
  lastTime(0),
  frameCount(0),
  debug(false),
  running(true),
  nbFrame(0),
  screen(TITLE_SCREEN),
  titleScreen(new TitleScreen(this)),
  gameScreen(new GameScreen(this)),
  console(new Console(this, 225))
{
	srand(time(NULL));
	GRRLIB_Init();
	WPAD_Init();
}

App::~App() {
	GRRLIB_Exit();
	delete titleScreen;
	delete gameScreen;
	delete console;
	exit(0);
}

void App::run() {
	dealEvent();
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
		debug = !debug;
		console->addDebug("passage en mode debug !!!");
		return;
	}

	switch (screen) {
	case TITLE_SCREEN:
		if ((player1Events[DOWN] | player2Events[DOWN]) & WPAD_BUTTON_HOME) this->running = false;
		else if ((player1Events[DOWN] | player2Events[DOWN]) & WPAD_BUTTON_A) {
		  console->addDebug("gameScreen !!!");
		  screen = GAME_SCREEN;
		  gameScreen->show();
		}
		else titleScreen->dealEvent(player1Events, player2Events);
		break;
	case GAME_SCREEN:
		if ((player1Events[DOWN] | player2Events[DOWN]) & WPAD_BUTTON_HOME) {
		  console->addDebug("titleScreen !!!");
		  screen = TITLE_SCREEN;
		}
		else gameScreen->dealEvent(player1Events, player2Events);
		break;
	}
}

void App::draw() {
	switch (screen) {
	case TITLE_SCREEN:
		titleScreen->draw();
		break;
	case GAME_SCREEN:
		gameScreen->compute();
		gameScreen->draw();
		break;
	}

	console->draw();

	GRRLIB_Render();
	calculateFrameRate();
}

bool App::isRunning() const {
	return running;
}

bool App::isDebug() const {
	return debug;
}

Console* App::getConsole() const {
	return console;
}

u8 App::getFPS() const {
	return fps;
}

u8 App::getFrameCount() const {
	return frameCount;
}

void App::calculateFrameRate() {
	u32 currentTime = ticks_to_millisecs(gettime());
	frameCount++;
	if(currentTime - lastTime > 1000) {
		lastTime = currentTime;
		fps = frameCount;
		frameCount = 0;
	}
}

}
