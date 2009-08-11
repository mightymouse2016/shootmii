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
	manager(_manager)
    //tex_font(loadFont(font_score, 48, 48)), // 48 c'est pas la height, c'est l'indice dans la table ascii
{
	children.reserve(SCOREMANAGER_CHILDREN_NUMBER);
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
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getPlayer1()->getPFury(),
				FURY_JAUGE_WIDTH,
				FURY_JAUGE_HEIGHT,
				-FURY_JAUGE_X,
				FURY_JAUGE_Y-1,
				App::imageBank->get(TXT_FURY_JAUGE1),
				PI));
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getPlayer2()->getPFury(),
				FURY_JAUGE_WIDTH,
				FURY_JAUGE_HEIGHT,
				FURY_JAUGE_X,
				FURY_JAUGE_Y,
				App::imageBank->get(TXT_FURY_JAUGE2)));
	addChild(new Jauge(
				JAUGE_LAYER,
				manager->getWind()->getPWindSpeedLeft(),
				WIND_JAUGE_WIDTH,
				WIND_JAUGE_HEIGHT,
				-WIND_JAUGE_X,
				WIND_JAUGE_Y,
				App::imageBank->get(TXT_WIND_JAUGE),
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
}

 /*
  void ScoreManager::drawScore() const {
    // Player 1
    char score[1];
    sprintf(score,"%d",manager->getPlayer1()->getScore());
    GRRLIB_Printf(SCREEN_WIDTH/2 - 70, SCREEN_HEIGHT - 55, tex_font, WHITE, 1, score);
    // Player 2
    sprintf(score,"%d",manager->getPlayer2()->getScore());
    GRRLIB_Printf(SCREEN_WIDTH/2 + 18, SCREEN_HEIGHT - 55, tex_font, WHITE, 1, score);
  }
 */
}
