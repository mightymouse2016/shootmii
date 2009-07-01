#include "../ShootMii.h"

namespace shootmii {

Manager::Manager(App* _app, string nick_p1, string nick_p2) :
	app(_app), world(new World), player1(new Player(nick_p1, BLUE,
			world->getWind(), 0, ROTATION_RANGE, INIT_ANGLE, ROTATION_STEP)),
			player2(new Player(nick_p2, RED, world->getWind(), ANGLE_OFFSET,
					ROTATION_RANGE, INIT_ANGLE + ANGLE_OFFSET, ROTATION_STEP)),
			ammosToDraw(new list<Ammo*> ) {

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

Player* Manager::opponent(const Player* player) const {
	if (player == player1)
		return player2;
	else
		return player1;
}

void Manager::initPlayerPosition(Player* player, int colIndex) const {
	for (int rowIndex = 0; rowIndex < N_ROWS; rowIndex++)
		if (world->getTerrain()->getCellType(rowIndex, colIndex) == GRASS) {
			player->setIndexCoords(colIndex, rowIndex);
			break;
		}
}

void Manager::moveLeft(Player* player) const {
	// On vérifie que l'on n'est pas à coté du bord
	if (player->getCol() - 1 == 0)
		return;
	// On vérifie que l'on n'est pas à coté d'un ennemi
	if (player->getScreenX() - player->getWidth()
			== opponent(player)->getScreenX())
		return;
	initPlayerPosition(player, player->getCol() - 1);
}

void Manager::moveRight(Player* player) const {
	if (player->getCol() + player->getWidth() / TERRAIN_CELL_WIDTH == N_COLS)
		return;
	if (player->getScreenX() + player->getWidth()
			== opponent(player)->getScreenX())
		return;
	initPlayerPosition(player, player->getCol() + 1);
}

bool Manager::ammoIsOffScreen(const int screenX) const {
	return (screenX > SCREEN_WIDTH || screenX < -TERRAIN_CELL_WIDTH);
}

bool Manager::ammoIsTooHigh(const int screenY) const {
	return (screenY < 0);
}

bool Manager::ammoIsTooLow(const int screenY) const {
	return (screenY > SCREEN_HEIGHT);
}

bool Manager::ammoHitTheGround(const int colIndex, const int rowIndex) const {
	if (world->getTerrain()->getCellType(rowIndex, colIndex) == SKY)
		return false;
	return true;
}

Ammo* Manager::ammoHitAnotherAmmo(const Ammo* ammo) const {
	list<Ammo*>::iterator it;
	for (it = ammosToDraw->begin(); it != ammosToDraw->end(); it++)
		if (ammo != *it && ammo->cellIntersect(*it))
			return *it;
	return NULL;
}

Player* Manager::ammoHitAPlayer(const Ammo* ammo) const {
	if (!ammo->isOutOfCannon())
		return NULL;
	if (ammo->cellIntersect(player1))
		return player1;
	if (ammo->cellIntersect(player2))
		return player2;
	return NULL;
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
	for (list<Ammo*>::iterator i = ammosToDraw->begin(); i
			!= ammosToDraw->end(); i++)
		if (!((*i)->isBeingDestroyed()))
			(*i)->draw();
}

void Manager::computeVictory() {
	Player* winner = NULL;

	if (player1->getLife() == 0)
		winner = player2;
	else if (player2->getLife() == 0)
		winner = player1;

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
		if ((*i)->isBeingDestroyed())
			delete *i;
		else if (ammoIsTooLow((*i)->getScreenY()))
			delete *i;
		else if (!world->getTerrain()->contains((*i)->getScreenX(),
				(*i)->getScreenY())) {
			newAmmosToDraw->push_back(*i);
			(*i)->compute();
		} else if (ammoHitTheGround((*i)->getCol(), (*i)->getRow()))
			(*i)->destruction();
		else if (Ammo * inFrontAmmo = ammoHitAnotherAmmo(*i)) {
			(*i)->destruction();
			inFrontAmmo->destruction();
		} else if (Player * playerHit = ammoHitAPlayer(*i)) {
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
	initPlayerPosition(player1, PLAYER_OFFSET);
	initPlayerPosition(player2, N_COLS - PLAYER_OFFSET);
	player1->initGame();
	player2->initGame();
}

void Manager::dealEvent(const u32* player1Events, const u32* player2Events) {
	const u32 pad1Held = player1Events[HELD], pad2Held = player2Events[HELD];
	const u32 pad1Down = player1Events[DOWN], pad2Down = player2Events[DOWN];

	if (pad1Held & WPAD_BUTTON_LEFT) moveLeft(player1);
	if (pad1Held & WPAD_BUTTON_RIGHT) moveRight(player1);
	if (pad1Held & WPAD_BUTTON_UP) player1->getCannon()->rotateLeft();
	if (pad1Held & WPAD_BUTTON_DOWN) player1->getCannon()->rotateRight();

	if (pad2Held & WPAD_BUTTON_LEFT) moveLeft(player2);
	if (pad2Held & WPAD_BUTTON_RIGHT) moveRight(player2);
	if (pad2Held & WPAD_BUTTON_UP) player2->getCannon()->rotateRight();
	if (pad2Held & WPAD_BUTTON_DOWN) player2->getCannon()->rotateLeft();

	if (pad1Down & WPAD_BUTTON_A) {
		player1->getCannon()->shoot(this);
		WPAD_Rumble(WPAD_CHAN_0, 1);
		WPAD_Rumble(WPAD_CHAN_0, 0);
	}

	if (pad2Down & WPAD_BUTTON_A) {
		player2->getCannon()->shoot(this);
		WPAD_Rumble(WPAD_CHAN_1, 1);
		WPAD_Rumble(WPAD_CHAN_1, 0);
	}

}

}
