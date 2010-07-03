#include "../tools/ImageBank.h"
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
    score_manager(new ScoreManager(_app,manager)),
    exitButton(new Button(-SCREEN_WIDTH/4,0,BUTTON_1_WIDTH,BUTTON_1_HEIGHT,"Exit",App::imageBank->get(TXT_BUTTON_1))),
    resumeButton(new Button(SCREEN_WIDTH/4,0,BUTTON_1_WIDTH,BUTTON_1_HEIGHT,"Resume",App::imageBank->get(TXT_BUTTON_1)))
{
	addButton(exitButton);
	addButton(resumeButton);

	// Top dock
	Dock* dock = new Dock(true);
	Text * pause_text = new Text("Pause",GUI_FONT,FONT_SIZE_14,WHITE,0,0);
	addText(pause_text);
	dock->addText(pause_text); // "Accroche" le texte au dock
	addDock(dock);

	// Bottom dock
	dock = new Dock(false);
	dock->addButton(exitButton);	// "Accroche" le boutton au dock
	dock->addButton(resumeButton); // "Accroche" le boutton au dock
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

	if (exitButton->isClicked()) app->setScreen(TITLE_SCREEN);
	
	if (resumeButton->isClicked() || ((eventsPlayer[0][DOWN] | eventsPlayer[1][DOWN]) & WPAD_BUTTON_HOME)) {
		for (std::list<Dock*>::iterator i=docks.begin();i!=docks.end();i++){
			(*i)->toggleHideShow();
		}
		manager->togglePause();
	}
	
	if (!manager->isInPause()) manager->dealEvent(eventsPlayer[0], eventsPlayer[1]);

	for (std::list<Clickable*>::iterator i=clickables.begin();i!=clickables.end();i++) (*i)->unClick();
}

}
