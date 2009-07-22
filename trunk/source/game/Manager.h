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
	list<Explosion*>* explosionsToDraw;
	list<Animation*>* animationsToDraw;
	GRRLIB_texImg explosionTiles;
	void computeAmmos();
	void computeExplosions();
	void computeAnimations();
	void computeVictory();
public:
	Manager(App*);
	~Manager();
	Player* getPlayer1() const;
	Player* getPlayer2() const;
	Wind* getWind() const;
	void compute();
	void initPlayers() const;
	void draw() const;
	void drawAmmos() const;
	void drawExplosions() const;
	void drawAnimations() const;
	void init() const;
	void dealEvent(const u32*, const u32*);
	void addAmmosToDraw(Ammo*) const;
	void addExplosionsToDraw(Explosion*) const;
	void addAnimationsToDraw(Animation*) const;
};

}

#endif /*MANAGER_H_*/
