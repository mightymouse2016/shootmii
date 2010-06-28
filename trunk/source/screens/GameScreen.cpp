#include "../tools/Tools.h"
#include "../tools/Colors.h"
#include "../game/Manager.h"
#include "../game/ScoreManager.h"
#include "../gui/Button.h"
#include "../gui/Dock.h"
#include "../gui/Text.h"
#include "../App.h"
#include "GameScreen.h"

namespace shootmii {

GameScreen::GameScreen(
		App* _app,
		Pointer** _pointerPlayer,
		u32** _eventsPlayer) :
    Screen(_app,_pointerPlayer,_eventsPlayer),
    manager(new Manager(_app)),
    score_manager(new ScoreManager(_app,manager))
{
	// Top dock
	Dock* dock = new Dock(true);
	Text * pause_text = new Text("Pause",GUI_FONT,FONT_SIZE_14,WHITE,0,0);
	addText(pause_text);
	dock->addText(pause_text); // "Accroche" le texte au dock
	addDock(dock);

	// Bottom dock
	dock = new Dock(false);
	addButton(-SCREEN_WIDTH/4, 0, "Exit", EXIT_BUTTON);
	dock->addButton(buttons[EXIT_BUTTON]);	// "Accroche" le boutton au dock
	addButton(SCREEN_WIDTH/4, 0, "Resume", RESUME_BUTTON);
	dock->addButton(buttons[RESUME_BUTTON]); // "Accroche" le boutton au dock
	addDock(dock);
}

GameScreen::~GameScreen() {
	delete score_manager;
	delete manager;
}

void GameScreen::compute(){
	Screen::compute();
	if (manager->isInPause()) return;
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

	if (buttons[EXIT_BUTTON]->isClicked()) app->setScreen(TITLE_SCREEN);
	
	if (buttons[RESUME_BUTTON]->isClicked() || ((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_HOME)) {
		for (std::list<Dock*>::iterator i=docks.begin();i!=docks.end();i++){
			(*i)->toggleHideShow();
		}
		manager->togglePause();
	}
	
	if (!manager->isInPause()) manager->dealEvent(eventsPlayer[0], eventsPlayer[1]);

	for (std::map<ButtonType,Button*>::iterator i=buttons.begin();i!=buttons.end();i++){
		i->second->unClick();
	}
}

}
