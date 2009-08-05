#include "../ShootMii.h"

namespace shootmii {

  GameScreen::GameScreen(App* _app) :
    Screen(_app),
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
	manager->compute();
}

void GameScreen::draw() {
	manager->draw();
	score_manager->draw();
}

void GameScreen::init() {
	manager->init();
}

void GameScreen::dealEvent(const u32* player1Events, const u32* player2Events) {
	manager->dealEvent(player1Events, player2Events);
}

}
