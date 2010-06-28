#include "../tools/ImageBank.h"
#include "../tools/Colors.h"
#include "../tools/Tools.h"
#include "../gfx/font_military.h"
#include "../gui/Text.h"
#include "../App.h"
#include "TitleScreen.h"

namespace shootmii {

TitleScreen::TitleScreen(
		App* app,
		Pointer** _pointerPlayer,
		u32** _eventsPlayer) :
	Screen(app, _pointerPlayer, _eventsPlayer),
    tex_title_screen(App::imageBank->get(TXT_TITLE_SCREEN)),
    tex_font(loadFont(font_military, 32, 32))
{
	addButton(SCREEN_WIDTH/4, SCREEN_HEIGHT*3/4, "Exit", EXIT_BUTTON);
	addButton(SCREEN_WIDTH*3/4, SCREEN_HEIGHT*3/4, "Start Game", START_BUTTON);
	addText(new Text("ShootMii",ARMY_FONT,FONT_SIZE_15,WHITE,SCREEN_WIDTH/2,SCREEN_HEIGHT*2/5));
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

	if (buttons[EXIT_BUTTON]->isClicked()) app->exit();
	if (buttons[START_BUTTON]->isClicked()) app->setScreen(GAME_SCREEN);

	for (std::map<ButtonType,Button*>::iterator i=buttons.begin();i!=buttons.end();i++) i->second->unClick();
}


}
