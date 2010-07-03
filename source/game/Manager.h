#ifndef MANAGER_H_
#define MANAGER_H_

#include <list>
#include "GRRLIB.h"

namespace shootmii {

class World;
class Ammo;
class Bonus;
class Player;
class Animation;
class Wind;
class App;
class JaugeManager;

const int PLAYER_OFFSET(100);

const int SHIELD_WIDTH(100);
const int SHIELD_HEIGHT(100);
const int SHIELD_DURATION(20);
const int SHIELD_SLOW(1);

const unsigned int DEFAULT_ROUND_COUNT(3);

class Manager {
private:
	bool pause;
	bool backFromPause;
	unsigned int roundCount;
	App* app;
	World* world;
	Player* player1;
	Player* player2;
	std::list<Ammo*>* ammos;
	std::list<Bonus*>* bonuses;
	std::list<Animation*>* animations;
public:
	static JaugeManager* jaugeManager;
	Manager(App* app);
	~Manager();
	void togglePause();
	bool isInPause() const;
	unsigned int getRoundCount() const;
	void setRoundCount(const unsigned int roundCount);
	Player* getPlayer1() const;
	Player* getPlayer2() const;
	Wind* getWind() const;
	void addAmmo(Ammo* ammo) const;
	void addBonus(Bonus* bonus) const;
	void addAnimation(Animation* animation) const;
	void initPlayers() const;
	void init();
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
