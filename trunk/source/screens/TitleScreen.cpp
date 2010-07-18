#include "../tools/ImageBank.h"
#include "../tools/Tools.h"
#include "../gfx/font_military.h"
#include "../gui/Selector.h"
#include "../gui/Text.h"
#include "../App.h"
#include "TitleScreen.h"

namespace shootmii {

TitleScreen::TitleScreen(
		App* app,
		Pointer** _pointerPlayer,
		u32** _eventsPlayer) :
	Screen(app, _pointerPlayer, _eventsPlayer),
    tex_font(loadFont(font_military, 32, 32)),
    exitButton(new Button(SCREEN_WIDTH/4,SCREEN_HEIGHT*3/4,BUTTON_1_WIDTH,BUTTON_1_HEIGHT,"Exit",App::imageBank->get(TXT_BUTTON_1))),
    newGameButton(new Button(SCREEN_WIDTH*3/4,SCREEN_HEIGHT*3/4,BUTTON_1_WIDTH,BUTTON_1_HEIGHT,"New Game",App::imageBank->get(TXT_BUTTON_1)))
{
	addButton(exitButton);
	addButton(newGameButton);
	addText(new Text("ShootMii",ARMY_FONT,FONT_SIZE_15,Color::WHITE,SCREEN_WIDTH/2,SCREEN_HEIGHT*2/5));
}

void TitleScreen::compute(){
	Screen::compute();
	// Ajouter ici tout code supplémentaire
}

void TitleScreen::addToDrawManager(){
	Screen::addToDrawManager();
	// Ajouter ici tout code supplémentaire
}

void TitleScreen::init() {
	Screen::init();
	// Ajouter ici tout code supplémentaire
}

void TitleScreen::dealEvent(){
	Screen::dealEvent();

	if (exitButton->isClicked()) app->exit();
	if (newGameButton->isClicked()) app->setScreen(OPTION_SCREEN);

	for (std::list<Clickable*>::iterator i=clickables.begin();i!=clickables.end();i++) (*i)->unClick();
	for (std::list<Selector*>::iterator i=selectors.begin();i!=selectors.end();i++) (*i)->unClick();
}


}
