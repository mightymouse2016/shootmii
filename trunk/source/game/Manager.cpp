#include "../ShootMii.h"

namespace shootmii {

Manager::Manager(
		App* _app,
		string nick_p1,
		string nick_p2) :
	app(_app),
	world(new World),
	player1(
		new Player(
			nick_p1,
			BLUE,
			world->getWind(),
			NULL,
			true,
			0,
			ROTATION_RANGE,
			INIT_ANGLE,
			ROTATION_STEP)),
	player2(
		new Player(
			nick_p2,
			RED,
			world->getWind(),
			player1,
			false,
			ANGLE_OFFSET,
			ROTATION_RANGE,
			INIT_ANGLE + ANGLE_OFFSET,
			ROTATION_STEP)),
	ammosToDraw(new list<Ammo*>)
{
	player1->setOpponent(player2);
}

Manager::~Manager() {
	delete player1;
	delete player2;
	delete world;
	// Destroy Ammos that are still in the air
	ammosToDraw->clear();
	delete ammosToDraw;
}

void Manager::addAmmosToDraw(Ammo* ammo) const {
	ammosToDraw->push_back(ammo);
}

Player* Manager::getPlayer1() const {
	return player1;
}

Player* Manager::getPlayer2() const {
	return player2;
}

void Manager::compute() {
	world->compute();
	player1->getCannon()->decHeat();
	player2->getCannon()->decHeat();
	computeAmmosCollisions();
	computeVictory();
}

void Manager::draw() const {
	world->drawBackground();
	drawAmmos();
	player1->draw();
	player2->draw();
	world->drawForeground();
}

void Manager::drawAmmos() const {
	for (list<Ammo*>::iterator i=ammosToDraw->begin();i!=ammosToDraw->end();i++)
		if (!((*i)->isBeingDestroyed())) (*i)->draw();
}

void Manager::computeVictory() {
	Player* winner = NULL;

	if (player1->getLife() == 0) winner = player2;
	else if (player2->getLife() == 0) winner = player1;

	if (winner) {
		winner->incScore();
		if (winner->getScore() >= MANCHE) {
			player1->setScore(0);
			player2->setScore(0);
		}
		ammosToDraw->clear();
		world->init();
		initPlayers();
	}
}

void Manager::computeAmmosCollisions() {
	list<Ammo*>* newAmmosToDraw = new list<Ammo*> ;
	for (list<Ammo*>::iterator i = ammosToDraw->begin(); i
			!= ammosToDraw->end(); i++) {
		if ((*i)->isBeingDestroyed()) delete *i;
		else if ((*i)->isTooLow()) delete *i;
		else if (!world->getTerrain()->contains((*i)->getScreenX(),(*i)->getScreenY())) {
			newAmmosToDraw->push_back(*i);
			(*i)->compute();
		}
		else if ((*i)->hitTheGround(world->getTerrain())) (*i)->destruction();
		else if (Ammo * inFrontAmmo = (*i)->hitAnotherAmmo(ammosToDraw)) {
			(*i)->destruction();
			inFrontAmmo->destruction();
		} else if (Player * playerHit = (*i)->hitAPlayer(player1,player2)) {
			(*i)->destruction();
			playerHit->looseLife(25);
		} else {
			newAmmosToDraw->push_back(*i);
			(*i)->compute();
		}
	}
	delete ammosToDraw;
	ammosToDraw = newAmmosToDraw;
}

void Manager::init() const {
	ammosToDraw->clear();
	world->init();
	player1->init();
	player2->init();
	initPlayers();
}

void Manager::initPlayers() const {
	player1->initPosition(world->getTerrain(), PLAYER_OFFSET);
	player2->initPosition(world->getTerrain(), world->getTerrain()->getCols()*TERRAIN_CELL_WIDTH - PLAYER_OFFSET);
	player1->initGame();
	player2->initGame();
}

void Manager::dealEvent(const u32* player1Events, const u32* player2Events) {
	const u32 pad1Held = player1Events[HELD], pad2Held = player2Events[HELD];
	const u32 pad1Down = player1Events[DOWN], pad2Down = player2Events[DOWN];
	const u32 pad1Up = player1Events[UP], pad2Up = player2Events[UP];

	if (pad1Held & WPAD_BUTTON_LEFT) player1->moveLeft(world->getTerrain());
	if (pad1Held & WPAD_BUTTON_RIGHT) player1->moveRight(world->getTerrain());
	if (pad1Held & WPAD_BUTTON_UP) player1->getCannon()->rotateLeft();
	if (pad1Held & WPAD_BUTTON_DOWN) player1->getCannon()->rotateRight();

	if (pad2Held & WPAD_BUTTON_LEFT) player2->moveLeft(world->getTerrain());
	if (pad2Held & WPAD_BUTTON_RIGHT) player2->moveRight(world->getTerrain());
	if (pad2Held & WPAD_BUTTON_UP) player2->getCannon()->rotateRight();
	if (pad2Held & WPAD_BUTTON_DOWN) player2->getCannon()->rotateLeft();

	if (pad1Down & WPAD_BUTTON_A) WPAD_Rumble(WPAD_CHAN_0, 1);
	if (pad1Held & WPAD_BUTTON_A) {
		player1->getCannon()->incStrength(this);
		if (!player1->getCannon()->isLoaded()) WPAD_Rumble(WPAD_CHAN_0, 0);
	}
	if (pad1Up & WPAD_BUTTON_A) {
		player1->getCannon()->up();
		player1->getCannon()->shoot(this);
		WPAD_Rumble(WPAD_CHAN_0, 0);
	}

	if (pad2Down & WPAD_BUTTON_A) WPAD_Rumble(WPAD_CHAN_1, 1);
	if (pad2Held & WPAD_BUTTON_A) {
		player2->getCannon()->incStrength(this);
		if (!player2->getCannon()->isLoaded()) WPAD_Rumble(WPAD_CHAN_1, 0);
	}
	if (pad2Up & WPAD_BUTTON_A) {
		player2->getCannon()->up();
		player2->getCannon()->shoot(this);
		WPAD_Rumble(WPAD_CHAN_1, 0);
	}
}

}
