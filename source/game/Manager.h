#ifndef MANAGER_H_
#define MANAGER_H_

#include "../ShootMii.h"

namespace shootmii {

const int PLAYER_OFFSET(100);

class Manager {
private:
	App* app;
	World* world;
	Player* player1;
	Player* player2;
	list<Polygon*>* draws;
	list<Ammo*>* ammos;
	list<Bonus*>* bonuses;
	list<Animation*>* smoklets;
	list<Animation*>* explosions;
public:
	Manager(App*);
	~Manager();
	Player* getPlayer1() const;
	Player* getPlayer2() const;
	Wind* getWind() const;
	void addAmmo(Ammo* ammo) const;
	void addBonus(Bonus* bonus) const;
	void addDraw(Polygon* polygon) const;
	void addSmoklet(Animation* animation) const;
	void addExplosion(Animation* animation) const;
	void initPlayers() const;
	void init() const;
	void dealEvent(const u32*, const u32*);
	void computeAnimations();
	void computeVictory();
	void computeBonus();
	void computeAmmos();
	void compute();

	void drawExplosions() const;
	void drawSmoklets() const;
	void drawBonus() const;
	void drawAmmos() const;
	void draw() const;
};

}

#endif /*MANAGER_H_*/
