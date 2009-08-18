#include "../ShootMii.h"

namespace shootmii {

ScoreManager::ScoreManager(
		App* _app,
		Manager* _manager) :
	Rectangle(
		STATUS_BAR_LAYER,
		SCREEN_WIDTH,
		SCORE_PANEL_HEIGHT,
		SCREEN_WIDTH/2,
		SCREEN_HEIGHT-SCORE_PANEL_HEIGHT/2,
		0,0,0,0,
		App::imageBank->get(TXT_SCORE_PANEL)),
	app(_app),
	manager(_manager),
    tex_font(loadFont(font_score, 32, 48)), // 48 c'est pas la height, c'est l'indice dans la table ascii
    bonusPlayer1(manager->getPlayer1()->getPBonus()),
    bonusPlayer2(manager->getPlayer2()->getPBonus())
{
	children.reserve(SCOREMANAGER_CHILDREN_NUMBER);

	//	Jauge de puissance du canon
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getPlayer1()->getCannon()->getPStrength(),
				STRENGTH_JAUGE_WIDTH,
				STRENGTH_JAUGE_HEIGHT,
				-STRENGTH_JAUGE_X,
				STRENGTH_JAUGE_Y,
				App::imageBank->get(TXT_STRENGTH_JAUGE)));
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getPlayer2()->getCannon()->getPStrength(),
				STRENGTH_JAUGE_WIDTH,
				STRENGTH_JAUGE_HEIGHT,
				STRENGTH_JAUGE_X,
				STRENGTH_JAUGE_Y,
				App::imageBank->get(TXT_STRENGTH_JAUGE)));

	// Jauge d'échauffement du canon
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getPlayer1()->getCannon()->getPHeat(),
				HEAT_JAUGE_WIDTH,
				HEAT_JAUGE_HEIGHT,
				-HEAT_JAUGE_X,
				HEAT_JAUGE_Y,
				App::imageBank->get(TXT_HEAT_JAUGE)));
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getPlayer2()->getCannon()->getPHeat(),
				HEAT_JAUGE_WIDTH,
				HEAT_JAUGE_HEIGHT,
				HEAT_JAUGE_X,
				HEAT_JAUGE_Y,
				App::imageBank->get(TXT_HEAT_JAUGE)));

	// Jauge Vie
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getPlayer1()->getPLife(),
				LIFE_JAUGE_WIDTH,
				LIFE_JAUGE_HEIGHT,
				-LIFE_JAUGE_X,
				LIFE_JAUGE_Y,
				App::imageBank->get(TXT_LIFE_JAUGE)));
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getPlayer2()->getPLife(),
				LIFE_JAUGE_WIDTH,
				LIFE_JAUGE_HEIGHT,
				LIFE_JAUGE_X,
				LIFE_JAUGE_Y,
				App::imageBank->get(TXT_LIFE_JAUGE)));

	// Jauge de fury
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getPlayer1()->getPFury(),
				FURY_JAUGE_WIDTH,
				FURY_JAUGE_HEIGHT,
				-FURY_JAUGE_X,
				FURY_JAUGE_Y-1,
				App::imageBank->get(TXT_FURY_JAUGE1),
				NULL,
				PI));
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getPlayer2()->getPFury(),
				FURY_JAUGE_WIDTH,
				FURY_JAUGE_HEIGHT,
				FURY_JAUGE_X,
				FURY_JAUGE_Y,
				App::imageBank->get(TXT_FURY_JAUGE2)));
	// Couche alpha (pour le scintillement lors du mode fury)
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getPlayer1()->getPFury(),
				FURY_JAUGE_WIDTH,
				FURY_JAUGE_HEIGHT,
				-FURY_JAUGE_X,
				FURY_JAUGE_Y-1,
				App::imageBank->get(TXT_ALPHA_FURY_JAUGE1),
				manager->getPlayer1()->getPFuryMode(),
				PI));
		addChild(new Jauge(
				JAUGE_LAYER,
				manager->getPlayer2()->getPFury(),
				FURY_JAUGE_WIDTH,
				FURY_JAUGE_HEIGHT,
				FURY_JAUGE_X,
				FURY_JAUGE_Y,
				App::imageBank->get(TXT_ALPHA_FURY_JAUGE2),
				manager->getPlayer2()->getPFuryMode()));

	// Jauge de vent
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getWind()->getPWindSpeedLeft(),
				WIND_JAUGE_WIDTH,
				WIND_JAUGE_HEIGHT,
				-WIND_JAUGE_X,
				WIND_JAUGE_Y,
				App::imageBank->get(TXT_WIND_JAUGE),
				NULL,
				PI));
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getWind()->getPWindSpeedRight(),
				WIND_JAUGE_WIDTH,
				WIND_JAUGE_HEIGHT,
				WIND_JAUGE_X,
				WIND_JAUGE_Y,
				App::imageBank->get(TXT_WIND_JAUGE)));
}

void ScoreManager::compute(){
	for(int i=0;i<SCOREMANAGER_CHILDREN_NUMBER;i++){
		static_cast<Jauge*>(children[i])->compute();
	}
	if (*bonusPlayer1) (*bonusPlayer1)->compute();
	if (*bonusPlayer2) (*bonusPlayer2)->compute();
}

void ScoreManager::draw() const{
	Polygon::draw();
	if (*bonusPlayer1) (*bonusPlayer1)->draw();
	if (*bonusPlayer2) (*bonusPlayer2)->draw();
	drawScore();
}


void ScoreManager::drawScore() const {
    // Player 1
    GRRLIB_Printf(SCREEN_WIDTH/2 - 56, SCREEN_HEIGHT - 42, tex_font, WHITE, 1, "%d", manager->getPlayer1()->getScore());
    // Player 2
    GRRLIB_Printf(SCREEN_WIDTH/2 + 24, SCREEN_HEIGHT - 42, tex_font, WHITE, 1, "%d", manager->getPlayer2()->getScore());
}

}
