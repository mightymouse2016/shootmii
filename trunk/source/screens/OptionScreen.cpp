#include "../tools/ImageBank.h"
#include "../tools/Colors.h"
#include "../tools/Tools.h"
#include "../game/Manager.h"
#include "../game/Player.h"
#include "../gfx/font_military.h"
#include "../gui/Selector.h"
#include "../gui/Text.h"
#include "../App.h"
#include "GameScreen.h"
#include "OptionScreen.h"

namespace shootmii {

OptionScreen::OptionScreen(
		App* app,
		Pointer** _pointerPlayer,
		u32** _eventsPlayer) :
	Screen(app, _pointerPlayer, _eventsPlayer),
    tex_font(loadFont(font_military, 32, 32)),
    backButton(new Button(SCREEN_WIDTH/4,SCREEN_HEIGHT*11/12,BUTTON_1_WIDTH,BUTTON_1_HEIGHT,"Back",App::imageBank->get(TXT_BUTTON_1))),
    startButton(new Button(SCREEN_WIDTH*3/4,SCREEN_HEIGHT*11/12,BUTTON_1_WIDTH,BUTTON_1_HEIGHT,"Start",App::imageBank->get(TXT_BUTTON_1))),
	roundSelector(new Selector(this,"Round ",SCREEN_WIDTH/4,SCREEN_HEIGHT*3/12)),
	player1Selector(new Selector(this,"Player 1 ",SCREEN_WIDTH/4,SCREEN_HEIGHT*5/12)),
	player2Selector(new Selector(this,"Player 2 ",SCREEN_WIDTH/4,SCREEN_HEIGHT*7/12))
{
	addText(new Text("Options",ARMY_FONT,FONT_SIZE_14,WHITE,SCREEN_WIDTH/2,SCREEN_HEIGHT/12));

	roundSelector->addOption(" 1 ");
	roundSelector->addOption(" 2 ");
	roundSelector->addOption(" 3 ");
	roundSelector->addOption(" 4 ");
	roundSelector->addOption(" 5 ");
	roundSelector->setSelectedIndex(2);
	addSelector(roundSelector);

	player1Selector->addOption(" Human ");
	player1Selector->addOption(" Computer ");
	player1Selector->setSelectedIndex(0);
	addSelector(player1Selector);

	player2Selector->addOption(" Human ");
	player2Selector->addOption(" Computer ");
	player2Selector->setSelectedIndex(1);
	addSelector(player2Selector);

	addButton(backButton);
	addButton(startButton);
}

void OptionScreen::compute(){
	Screen::compute();
	// Ajouter ici tout code supplémentaire
}

void OptionScreen::addToDrawManager(){
	Screen::addToDrawManager();
	// Ajouter ici tout code supplémentaire
}

void OptionScreen::init() {
	Screen::init();
	// Ajouter ici tout code supplémentaire
}

void OptionScreen::dealEvent(){
	Screen::dealEvent();

	if (backButton->isClicked()) app->setScreen(TITLE_SCREEN);
	if (startButton->isClicked()) app->setScreen(GAME_SCREEN);
	if (roundSelector->isClicked()) setRoundCount(roundSelector->getSelectedIndex()+1);
	if (player1Selector->isClicked()) setPlayer1IA(player1Selector->getSelectedIndex() == 1);
	if (player2Selector->isClicked()) setPlayer2IA(player2Selector->getSelectedIndex() == 1);

	for (std::list<Clickable*>::iterator i=clickables.begin();i!=clickables.end();i++) (*i)->unClick();
	for (std::list<Selector*>::iterator i=selectors.begin();i!=selectors.end();i++) (*i)->unClick();
}

void OptionScreen::setRoundCount(unsigned int roundCount){
	GameScreen* gameScreen = static_cast<GameScreen*>(app->getScreen(GAME_SCREEN));
	Manager* manager = gameScreen->getManager();
	manager->setRoundCount(roundCount);
}

void OptionScreen::setPlayer1IA(const bool ia){
	GameScreen* gameScreen = static_cast<GameScreen*>(app->getScreen(GAME_SCREEN));
	Manager* manager = gameScreen->getManager();
	manager->getPlayer1()->setIA(ia);
}

void OptionScreen::setPlayer2IA(const bool ia){
	GameScreen* gameScreen = static_cast<GameScreen*>(app->getScreen(GAME_SCREEN));
	Manager* manager = gameScreen->getManager();
	manager->getPlayer2()->setIA(ia);
}

}

