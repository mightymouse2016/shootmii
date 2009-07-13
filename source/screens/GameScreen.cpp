#include "../ShootMii.h"

namespace shootmii {

  GameScreen::GameScreen(
		  App* _app,
		  string nick_p1,
		  string nick_p2) :
    Screen(_app),
    manager(new Manager(_app, nick_p1,nick_p2)),
    score_manager(new ScoreManager(_app,manager))
{
    // NOTHING TO BE DONE
}

GameScreen::~GameScreen() {
	delete score_manager;
	delete manager;
}

void GameScreen::compute(){
	manager->compute();
}

void GameScreen::draw() {
	manager->draw();
	score_manager->draw();
}

void GameScreen::show() {
	manager->init();
}

void GameScreen::dealEvent(const u32* player1Events, const u32* player2Events) {
	manager->dealEvent(player1Events, player2Events);
}

}
