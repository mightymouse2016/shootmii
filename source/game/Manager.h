#ifndef MANAGER_H_
#define MANAGER_H_

#include "../ShootMii.h"

namespace shootmii {

const int PLAYER_OFFSET(5);

class Manager {
private:
	App* app;
	World* world;
	Player* player1;
	Player* player2;
	list<Ammo*>* ammosToDraw;
	void computeAmmosCollisions();
	void computeVictory();
	bool ammoIsOffScreen(const int screenX) const;
	bool ammoIsTooHigh(const int screenY) const;
	bool ammoIsTooLow(const int screenY) const;
	bool ammoHitTheGround(const int colIndex, const int rowIndex) const;
	Ammo* ammoHitAnotherAmmo(const Ammo*) const;
	Player* ammoHitAPlayer(const Ammo*) const;

public:
	Manager(App*, string nick_p1 = "Player 1", string nick_p2 = "Player 2");
	~Manager();
	// Accesseurs
	Player* getPlayer1() const;
	Player* getPlayer2() const;
	// Autres m�thodes
	void compute();
	Player* opponent(const Player*) const;
	void initPlayerPosition(Player* player, int offSet = 0) const;
	void initPlayers() const;
	void moveLeft(Player*) const;
	void moveRight(Player*) const;
	void draw() const;
	void drawAmmos() const;
	void init() const;
	void dealEvent(const u32*, const u32*);
	void addAmmosToDraw(Ammo*) const;
};

}

#endif /*MANAGER_H_*/
