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
	list<Ammo*>* ammos;
	list<Bonus*>* bonuses;
	list<Animation*>* animations;
public:
	Manager(App*);
	~Manager();
	Player* getPlayer1() const;
	Player* getPlayer2() const;
	Wind* getWind() const;
	void addAmmo(Ammo* ammo) const;
	void addBonus(Bonus* bonus) const;
	void addAnimation(Animation* animation) const;
	void initPlayers() const;
	void init() const;
	void dealEvent(const u32*, const u32*);
	void computeAnimations();
	void computeVictory();
	void computeBonuses();
	void computeAmmos();
	void compute();
	void addToDrawManager() const;
};

}

#endif /*MANAGER_H_*/
