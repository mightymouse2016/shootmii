#ifndef SCOREMANAGER_H_
#define SCOREMANAGER_H_

#include "../ShootMii.h"

namespace shootmii {

const int MANCHE(3);

enum ScoreManagerChild{
	CHILD_STRENGTH_JAUGE_1,
	CHILD_STRENGTH_JAUGE_2,
	CHILD_HEAT_JAUGE_1,
	CHILD_HEAT_JAUGE_2,
	CHILD_LIFE_JAUGE_1,
	CHILD_LIFE_JAUGE_2,
	CHILD_FURY_JAUGE_1,
	CHILD_FURY_JAUGE_2,
	CHILD_ALPHA_FURY_JAUGE_1,
	CHILD_ALPHA_FURY_JAUGE_2,
	CHILD_WIND_JAUGE_LEFT,
	CHILD_WIND_JAUGE_RIGHT,
	SCOREMANAGER_CHILDREN_NUMBER
};

class ScoreManager : public Rectangle {
private:
	App* app;
	Manager* manager;
	GRRLIB_texImg* tex_font;
	Bonus** bonusPlayer1;	// ptr sur le ptr de bonus du player (comme ça pas de mise à jour à faire)
	Bonus** bonusPlayer2;
public:
	ScoreManager(App*, Manager*);
	void compute();
	void draw() const;
	void drawScore() const;
};

}

#endif /*SCOREMANAGER_H_*/
