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
	list<Ammo*>* ammosToDraw;
	list<Bonus*>* bonusToDraw;
	list<Animation*>* smokletsToDraw;
	list<Animation*>* explosionsToDraw;
public:
	Manager(App*);
	~Manager();
	Player* getPlayer1() const;
	Player* getPlayer2() const;
	Wind* getWind() const;
	void addAmmosToDraw(Ammo*) const;
	void addBonusToDraw(Bonus* bonus) const;
	void addSmokletsToDraw(Animation*) const;
	void addExplosionsToDraw(Animation*) const;
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
