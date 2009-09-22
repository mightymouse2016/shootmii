#include "../ShootMii.h"

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
}



void TitleScreen::compute(){
	Screen::compute();

}

void TitleScreen::addToDrawManager(){
	Screen::addToDrawManager();

}

void TitleScreen::init() {
	Screen::init();

}

void TitleScreen::dealEvent(){
	Screen::dealEvent();

	if (buttons[START_BUTTON]->isClicked()){
		app->setScreen(GAME_SCREEN);
		buttons[START_BUTTON]->unClick();
	}

	if (buttons[EXIT_BUTTON]->isClicked()){
		app->exit();
		buttons[EXIT_BUTTON]->unClick();
	}
}


}
