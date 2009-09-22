#include "../ShootMii.h"

namespace shootmii {

GameScreen::GameScreen(
		App* _app,
		Pointer** _pointerPlayer,
		u32** _eventsPlayer) :
    Screen(_app,_pointerPlayer,_eventsPlayer),
    manager(new Manager(_app)),
    score_manager(new ScoreManager(_app,manager))
{
    // NOTHING TO BE DONE
}

GameScreen::~GameScreen() {
	delete score_manager;
	delete manager;
}

void GameScreen::compute(){
	Screen::compute();
	manager->compute();
	score_manager->compute();
}

void GameScreen::addToDrawManager(){
	Screen::addToDrawManager();
	manager->addToDrawManager();
	score_manager->addToDrawManager();
}

void GameScreen::init() {
	Screen::init();
	manager->init();
}

void GameScreen::dealEvent() {
	Screen::dealEvent();
	manager->dealEvent(eventsPlayer[0], eventsPlayer[1]);
	if ((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_HOME) app->setScreen(TITLE_SCREEN);
}

}
